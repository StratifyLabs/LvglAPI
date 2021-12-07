#if __StratifyOS__
#include <sos/sos.h>
#endif

#include <chrono/ClockTimer.hpp>

#if defined __link
#include "lvgl/Generic.hpp"
#include <window/Clipboard.hpp>
#include <window/Event.hpp>
#endif

#include "lvgl_api.h"

#include "lvgl/Runtime.hpp"
#include "lvgl/Style.hpp"

using namespace lvgl;

#if __StratifyOS__
Runtime::Runtime() {
  kernel_request(LVGL_REQUEST_START, nullptr);

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  m_task_mutex =
    thread::Mutex(thread::Mutex::Attributes().set_type(thread::Mutex::Type::recursive));
#if LVGL_RUNTIME_TASK_ARRAY_SIZE == 0
  m_task_list.reserve(32);
#else
  for (auto &task : m_task_list) {
    task = {nullptr, nullptr};
  }
#endif
#endif

#if defined __link

#endif
}
#endif

Runtime &Runtime::loop() {
  while (is_stopped() == false) {
    refresh();
  }

#if __StratifyOS__
  kernel_request(LVGL_REQUEST_STOP, nullptr);
#endif
  return *this;
}

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
Runtime &Runtime::push(TaskCallback callback, void *context) {
  thread::Mutex::Scope ms(m_task_mutex);
#if LVGL_RUNTIME_TASK_ARRAY_SIZE == 0
  m_task_list.push_back(task);
#else
  for (auto &entry : m_task_list) {
    if (entry.callback == nullptr) {
      entry = {callback, context};
      break;
    }
  }
#endif
  return *this;
}
#endif

Runtime &Runtime::refresh() {
  chrono::ClockTimer timer(chrono::ClockTimer::IsRunning::yes);
#if defined __link
  update_events();
#endif

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  {
    thread::Mutex::Scope ms(m_task_mutex);
#if LVGL_RUNTIME_TASK_ARRAY_SIZE == 0
    m_task_list.push_back(task);
    while (m_task_list.count()) {
      auto &task = m_task_list.back();
      task.callback(task.context);
      m_task_list.pop_back();
    }
#else
    for (auto &task : m_task_list) {
      if (task.callback != nullptr) {
        task.callback(task.context);
        task.callback = nullptr;
      }
    }
#endif
  }
#endif

  api()->timer_handler();
  timer.stop();
  const auto elapsed = timer.micro_time();
  if (period() > timer) {
    const auto remaining = period() - elapsed;
    chrono::wait(remaining);
  }
  api()->tick_inc(
    elapsed > period() ? elapsed.milliseconds()
                       : period().milliseconds() * increment_scale());
  return *this;
}

#if defined __link

Runtime::Runtime(
  const char *title,
  const window::Point &location,
  const window::Size &size,
  window::Window::Flags flags)
  : m_window(title, location, size, flags),
    m_renderer(m_window, -1, window::Renderer::Flags::accelerated),
    m_texture(
      m_renderer,
      window::PixelFormat::argb8888,
      window::Texture::Access::target,
      size),
    m_display_size(size) {

  if (flags & window::Window::Flags::highdpi) {
    m_dpi_scale = 2.0f;
    m_window.set_size(size.get_half());
  }

  for (auto &task : m_task_list) {
    task = {};
  }

  m_texture.set_blend_mode(window::BlendMode::blend)
    .update(m_active_frame_buffer, m_display_size.width() * sizeof(u32));

  initialize_display();
  initialize_devices();
}

void Runtime::initialize_display() {
  lv_init();

  const auto pixel_count = m_display_size.width() * m_display_size.height();
  allocate_frames(m_display_size);

  lv_disp_draw_buf_init(
    &m_display_buffer, m_display_frame0.data(), m_display_frame1.data(), pixel_count);

  m_active_frame_buffer = m_display_frame0.data();

  lv_disp_drv_init(&m_display_driver);

  m_display_driver.hor_res = m_display_size.width();
  m_display_driver.ver_res = m_display_size.height();
  m_display_driver.draw_buf = &m_display_buffer;
  m_display_driver.flush_cb = flush_callback;
  m_display_driver.user_data = this;
  m_display_driver.full_refresh = 1;

  m_display = lv_disp_drv_register(&m_display_driver);
}

void Runtime::initialize_devices() {
  lv_indev_drv_init(&m_keyboard_driver);
  m_keyboard_driver.type = LV_INDEV_TYPE_KEYPAD;
  m_keyboard_driver.user_data = this;
  m_keyboard_driver.read_cb = read_keyboard_callback;
  m_keyboard_device = lv_indev_drv_register(&m_keyboard_driver);

  m_group = lvgl::Group::create();
  lv_indev_set_group(m_keyboard_device, m_group.group());

  lv_indev_drv_init(&m_mouse_driver);
  m_mouse_driver.type = LV_INDEV_TYPE_POINTER;
  m_mouse_driver.user_data = this;
  m_mouse_driver.read_cb = read_mouse_callback;
  m_mouse_device = lv_indev_drv_register(&m_mouse_driver);
}

void Runtime::update_window() {

  m_texture.update(m_active_frame_buffer, m_display_size.width() * sizeof(u32));
  m_renderer.clear();

#if LV_COLOR_SCREEN_TRANSP
  m_renderer.set_draw_color(window::RgbaColor().set_red(0xff).set_alpha(0xff))
    .draw_rectanle(
      window::Rectangle(window::Point(0, 0), window::Size(SDL_HOR_RES, SDL_VER_RES)));
#endif

  m_renderer.copy(m_texture).present();
}

void Runtime::update_events() {

  bool has_events = true;
  while (has_events) {
    const auto event = window::Event::poll();
    if (event.is_valid()) {
      handle_keyboard_event(event);
      handle_mouse_event(event);
      handle_window_event(event);

      if (event.type() == window::EventType::quit) {
        set_stopped();
      }
    }
    has_events = event.is_valid();
  }

  update_wheel_event();
}

void Runtime::handle_window_event(const window::Event &event) {
  if (event.type() == window::EventType::window) {
    const auto window_event = event.get_window();
    switch (window_event.window_type()) {
    case window::WindowEvent::WindowType::resized: {
      const auto size = window_event.data_size();
      resize_display(
        window::Size(size.width() * m_dpi_scale, size.height() * m_dpi_scale));
    } break;
    case window::WindowEvent::WindowType::size_changed:
      break;
    default:
      break;
    }
  }
}

void Runtime::handle_mouse_event(const window::Event &event) {
  switch (event.type()) {
  case window::EventType::mouse_button_up:
  case window::EventType::mouse_button_down:
    m_mouse_event_queue.push(event);
    m_mouse_state = event.type() == window::EventType::mouse_button_up
                      ? window::Event::State::released
                      : window::Event::State::pressed;
    break;
  case window::EventType::mouse_motion:
    // may need to scale this
    m_mouse_position = event.get_mouse_motion().point();
    break;
  case window::EventType::mouse_wheel:
    m_mouse_wheel_event_queue.push({event, m_mouse_position});
    break;
  default:
    break;
  }
}

void Runtime::handle_keyboard_event(const window::Event &event) {
  const auto type = event.type();
  if ((type != window::EventType::key_down) && (type != window::EventType::key_up)) {
    return;
  }

  const auto key_event = event.get_keyboard();
  switch (event.type()) {
  case window::EventType::key_down:
    m_keyboard_event_queue.push(
      {window::Event::State::pressed, key_event.modifiers(), key_event.scan_code(),
       key_event.key_code(), IsClipboard::no});
    break;
  case window::EventType::key_up:
    m_keyboard_event_queue.push(
      {window::Event::State::released, key_event.modifiers(), key_event.scan_code(),
       key_event.key_code(), IsClipboard::no});
    break;
  default:
    break;
  }
}

void Runtime::update_wheel_event() {
  WheelEvent wheel_event;
  do {
    wheel_event = get_wheel_event();
    if (wheel_event.type != WheelEvent::Type::null) {

      // advance the scroll on the current object?
      auto object = screen().find(wheel_event.mouse);

      // look for the first scrollable parent
      for (Object current = object; current.is_valid(); current = current.get_parent()) {
        if (current.get_scroll_bottom() != 0 || current.get_scroll_y() != 0) {
          const auto scroll_y = current.get_scroll_y();
          current.get<lvgl::Generic>().scroll_to_y(
            scroll_y + -1 * wheel_event.delta.y() * scroll_wheel_multiplier(),
            IsAnimate::yes);
          break;
        }
      }
    }
  } while (wheel_event.type != WheelEvent::Type::null);
}

void Runtime::resize_display(const window::Size &size) {

  auto &inactive_frame = m_active_frame_buffer == m_display_frame0.data()
                           ? m_display_frame1
                           : m_display_frame0;
  auto &active_frame = m_active_frame_buffer == m_display_frame0.data()
                         ? m_display_frame0
                         : m_display_frame0;
  const auto pixel_count = size.width() * size.height();

  inactive_frame.resize(pixel_count);
  m_display_size = size;
  m_active_frame_buffer = inactive_frame.data();

  m_display_driver.hor_res = size.width();
  m_display_driver.ver_res = size.height();

  m_texture = window::Texture(
    m_renderer, window::PixelFormat::argb8888, window::Texture::Access::target, size);

  // update_window();
  active_frame.resize(pixel_count);

  lv_disp_draw_buf_init(
    &m_display_buffer, m_display_frame0.data(), m_display_frame1.data(), pixel_count);
  lv_disp_drv_update(m_display, &m_display_driver);
}

void Runtime::allocate_frames(const window::Size &size) {
  const auto pixel_count = size.width() * size.height();
  m_display_frame0.resize(pixel_count);
  m_display_frame1.resize(pixel_count);
}

void Runtime::flush(
  lv_disp_drv_t *display_driver,
  const lv_area_t *area,
  lv_color_t *colors) noexcept {

  const lv_coord_t hres = display_driver->hor_res;
  const lv_coord_t vres = display_driver->ver_res;
  auto *self = reinterpret_cast<Runtime *>(display_driver->user_data);

  /*Return if the area is out the screen*/
  if (area->x2 < 0 || area->y2 < 0 || area->x1 > hres - 1 || area->y1 > vres - 1) {
    lv_disp_flush_ready(display_driver);
    return;
  }
  self->m_active_frame_buffer = colors;

  // monitor.sdl_refr_qry = true;

  /* TYPICALLY YOU DO NOT NEED THIS
   * If it was the last part to refresh update the texture of the window.*/
  if (lv_disp_flush_is_last(display_driver)) {
    // monitor_sdl_refr(NULL);
  }

  /*IMPORTANT! It must be called to tell the system the flush is ready*/
  lv_disp_flush_ready(display_driver);

  update_window();
}

void Runtime::flush_callback(
  lv_disp_drv_t *display_driver,
  const lv_area_t *area,
  lv_color_t *colors) {
  auto *runtime = reinterpret_cast<Runtime *>(display_driver->user_data);
  runtime->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

void Runtime::read_mouse_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  auto *self = reinterpret_cast<Runtime *>(indev_drv->user_data);
  auto &events = self->m_mouse_event_queue;

  if (events.count()) {
    const auto &event = events.front().get_mouse_button();
    const auto point = event.point();
    data->point.x = point.x() * self->m_dpi_scale;
    data->point.y = point.y() * self->m_dpi_scale;
    data->state = (event.type() == window::EventType::mouse_button_down)
                    ? LV_INDEV_STATE_PRESSED
                    : LV_INDEV_STATE_RELEASED;
    events.pop();
  } else {
    const auto mouse_point = self->m_mouse_position;
    data->point.x = mouse_point.x() * self->m_dpi_scale;
    data->point.y = mouse_point.y() * self->m_dpi_scale;
    data->state = self->m_mouse_state == window::Event::State::pressed
                    ? LV_INDEV_STATE_PRESSED
                    : LV_INDEV_STATE_RELEASED;
  }
  data->continue_reading = 0;
}

void Runtime::read_keyboard_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  auto *self = reinterpret_cast<Runtime *>(indev_drv->user_data);

  auto &keys = self->m_keyboard_event_queue;

  *data = lv_indev_data_t{};

  if (keys.count()) {
    const auto &key_event = keys.front();
    data->state = (key_event.state == window::Event::State::pressed)
                    ? LV_INDEV_STATE_PRESSED
                    : LV_INDEV_STATE_RELEASED;

    data->key = [&]() -> u32 {
      const auto scan_code = key_event.scan_code;

      if (scan_code == window::ScanCode::page_up) {
        return LV_KEY_NEXT;
      }
      if (scan_code == window::ScanCode::tab) {
        if (key_event.modifier & window::KeyModifier::shift) {
          return LV_KEY_PREV;
        }
        return LV_KEY_NEXT;
      }
      if (scan_code == window::ScanCode::page_down) {
        return LV_KEY_PREV;
      }
      if (scan_code == window::ScanCode::return_) {
        return LV_KEY_ENTER;
      }
      if (scan_code == window::ScanCode::keypad_enter) {
        return LV_KEY_ENTER;
      }
      if (scan_code == window::ScanCode::up) {
        return LV_KEY_UP;
      }
      if (scan_code == window::ScanCode::down) {
        return LV_KEY_DOWN;
      }
      if (scan_code == window::ScanCode::right) {
        if (key_event.modifier & window::KeyModifier::control) {
          return LV_KEY_END;
        }
        return LV_KEY_RIGHT;
      }
      if (scan_code == window::ScanCode::left) {
        if (key_event.modifier & window::KeyModifier::control) {
          return LV_KEY_HOME;
        }
        return LV_KEY_LEFT;
      }
      if (scan_code == window::ScanCode::escape) {
        return LV_KEY_ESC;
      }
      if (scan_code == window::ScanCode::delete_) {
        return LV_KEY_DEL;
      }
      if (scan_code == window::ScanCode::backspace) {
        return LV_KEY_BACKSPACE;
      }
      if (scan_code == window::ScanCode::home) {
        return LV_KEY_HOME;
      }
      if (scan_code == window::ScanCode::end) {
        return LV_KEY_END;
      }

      if (
        (scan_code == window::ScanCode::left_shift)
        || (scan_code == window::ScanCode::right_shift)
        || (scan_code == window::ScanCode::left_control)
        || (scan_code == window::ScanCode::right_control)
        || (scan_code == window::ScanCode::left_alt)
        || (scan_code == window::ScanCode::right_alt)
        || (scan_code == window::ScanCode::left_meta)
        || (scan_code == window::ScanCode::right_meta)) {
        return 0;
      }

      if (
        (scan_code == window::ScanCode::v)
        && (key_event.modifier & window::KeyModifier::control)
        && (key_event.state == window::EventState::pressed)) {
        if (window::Clipboard::has_text()) {
          window::Clipboard clipboard;
          const var::StringView text = clipboard.get_text();

          // for some reason the first character from the clipboard gets dropped
          // adding this 0 key before the clipboard fixes it
          keys
            .push(
              {window::Event::State::pressed, window::KeyModifier::none,
               window::ScanCode::unknown, u32(0), IsClipboard::yes})
            .push(
              {window::Event::State::released, window::KeyModifier::none,
               window::ScanCode::unknown, u32(0), IsClipboard::yes});

          for (const auto value : text) {
            keys
              .push(
                {window::Event::State::pressed, window::KeyModifier::none,
                 window::ScanCode::unknown, u32(value), IsClipboard::yes})
              .push(
                {window::Event::State::released, window::KeyModifier::none,
                 window::ScanCode::unknown, u32(value), IsClipboard::yes});
          }
        }
        return 0;
      }

      if (
        (key_event.modifier & window::KeyModifier::shift)
        && (key_event.is_clipboard == IsClipboard::no)) {

        if (
          (key_event.key_code >= 'a') && (key_event.key_code <= 'z')
          && (key_event.is_clipboard == IsClipboard::no)) {
          return key_event.key_code - 'a' + 'A';
        }

        static constexpr auto default_case = "`1234567890-=[]\\;',./";
        static constexpr auto shift_case = "~!@#$%^&*()_+{}|:\"<>?";

        const auto position = var::StringView(default_case).find(key_event.key_code);
        if (position != var::StringView::npos) {
          return shift_case[position];
        }
      }
      return key_event.key_code;
    }();

    keys.pop();
  }
  data->continue_reading = data->key && keys.count() > 0;
}

WheelEvent Runtime::get_wheel_event() {
  auto &events = m_mouse_wheel_event_queue;

  if (events.count() == 0) {
    return lvgl::WheelEvent{lvgl::WheelEvent::Type::null};
  }

  const auto &event = events.front();
  const auto wheel_event = event.event.get_mouse_wheel();

  WheelEvent result{
    WheelEvent::Type::pixel,
    lvgl::Point(
      wheel_event.point().x() * m_dpi_scale, wheel_event.point().y() * m_dpi_scale),
    lvgl::Point(event.position.x() * m_dpi_scale, event.position.y() * m_dpi_scale)};

  events.pop();

  return result;
}

#endif
