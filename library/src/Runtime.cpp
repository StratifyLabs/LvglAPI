#if __StratifyOS__
#include <sos/sos.h>
#endif

#include <chrono/ClockTimer.hpp>

#if defined __link
#include <window/Clipboard.hpp>
#include <window/Event.hpp>

#include "lvgl/Event.hpp"
#include "lvgl/Generic.hpp"
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
  while (!is_stopped()) {
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

  timer.stop();
  const auto elapsed = timer.micro_time();
  if (period() > timer) {
    const auto remaining = period() - elapsed;
    chrono::wait(remaining);
  }

  api()->timer_handler();
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

  window::Window::enable_drop_file();

  if (flags & window::Window::Flags::highdpi) {
    m_dpi_scale = 2.0f;
    m_window.set_size(size.get_half());
  }

  for (auto &task : m_task_list) {
    task = {};
  }

  m_texture.set_blend_mode(window::BlendMode::blend);

  initialize_display();
  initialize_devices();
}

void Runtime::initialize_display() {
  lv_init();

  const auto pixel_count = m_display_size.width() * m_display_size.height();
  allocate_frames(m_display_size);

#if LV_USE_GPU_SDL
  lv_disp_draw_buf_init(
    &m_display_buffer, m_texture.native_value(), nullptr, pixel_count);
#else
  lv_disp_draw_buf_init(
    &m_display_buffer, m_display_frame0.data(), m_display_frame1.data(), pixel_count);
  m_active_frame_buffer = m_display_frame0.data();
#endif

  lv_disp_drv_init(&m_display_driver_container.display_driver);

  m_display_driver_container.display_driver.hor_res = m_display_size.width();
  m_display_driver_container.display_driver.ver_res = m_display_size.height();
  m_display_driver_container.display_driver.draw_buf = &m_display_buffer;
  m_display_driver_container.display_driver.flush_cb = flush_callback;
#if LV_USE_GPU_SDL
  m_sdl_gpu_driver_parameters.renderer = m_renderer.native_value();
  m_sdl_gpu_driver_parameters.user_data = nullptr;
  m_display_driver_container.display_driver.user_data = &m_sdl_gpu_driver_parameters;
#else
  m_display_driver_container.display_driver.user_data = nullptr;
#endif
  m_display_driver_container.display_driver.full_refresh = !LV_USE_GPU_SDL;
  m_display_driver_container.display_driver.antialiasing = 1;

  m_display = lv_disp_drv_register(&m_display_driver_container.display_driver);
  m_display_driver_container.self = this;
}

void Runtime::initialize_devices() {
  lv_indev_drv_init(&m_keyboard_driver);
  m_keyboard_driver.type = LV_INDEV_TYPE_KEYPAD;
  m_keyboard_driver.user_data = this;
  m_keyboard_driver.read_cb = read_keyboard_callback;
  m_keyboard_device = lv_indev_drv_register(&m_keyboard_driver);

  m_group = lvgl::Group::create();

  // make this the default group
  m_group.set_default();
  lv_indev_set_group(m_keyboard_device, m_group.group());

  lv_indev_drv_init(&m_mouse_driver);
  m_mouse_driver.type = LV_INDEV_TYPE_POINTER;
  m_mouse_driver.user_data = this;
  m_mouse_driver.read_cb = read_mouse_callback;
  m_mouse_driver.scroll_throw = 1;
  m_mouse_driver.long_press_time = 800;
  m_mouse_device = lv_indev_drv_register(&m_mouse_driver);
}

void Runtime::update_window() {

  auto update_transparency = [&]() {
#if LV_COLOR_SCREEN_TRANSP
    m_renderer
      .set_draw_color(window::RgbaColor().set_red(0xff).set_alpha(0xff))
        m_renderer.set_draw_color(window::RgbaColor().set_red(0xff).set_alpha(0xff))
      .draw_rectanle(window::Rectangle(
        window::Point(0, 0),
        window::Size(m_display_size.width(), m_display_size.height())));
#endif
  };

#if LV_USE_GPU_SDL
  m_renderer.clear_target().clear();
  update_transparency();
  m_texture.set_blend_mode(window::BlendMode::blend);
  m_renderer.clear_clip_rectangle().copy(m_texture).present().set_target(m_texture);
#else
  m_texture.update(m_active_frame_buffer, m_display_size.width() * sizeof(u32));
  m_renderer.clear();
  update_transparency();
  m_renderer.copy(m_texture).present();
#endif
}

void Runtime::update_events() {

  bool has_events = true;
  while (has_events) {
    const auto event = window::Event::poll();
    if (event.is_valid()) {
      handle_keyboard_event(event);
      handle_mouse_event(event);
      handle_window_event(event);
      handle_drop_event(event);
      handle_window_event_callback(event);

      if (event.type() == window::EventType::window) {
        const auto is_update =
          event.get_window().window_type() == window::WindowEvent::WindowType::exposed
          || event.get_window().window_type()
               == window::WindowEvent::WindowType::take_focus;
        if (is_update) {
          update_window();
        }
      }

      if (event.type() == window::EventType::quit) {
        set_stopped();
      }
    }
    has_events = event.is_valid();
  }

  if (m_mouse_wheel_timer.milliseconds() > period().milliseconds() * 4) {
    m_mouse_wheel_timer.reset();
    m_mouse_event_queue.push({m_mouse_position, IsPressed::no});
    m_mouse_state = window::Event::State::released;
    m_mouse_position = m_mouse_restore_position;
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

void Runtime::handle_drop_event(const window::Event &event) {
  if (window::DropEvent::is_valid(event.type())) {
    const auto drop = event.get_drop();
    const auto event_code = [&]() {
      if (drop.is_valid()) {
        switch (drop.type()) {
        case window::EventType::drop_file:
          return EventCode::drop_file;
        case window::EventType::drop_complete:
          return EventCode::drop_complete;
        case window::EventType::drop_begin:
          return EventCode::drop_begin;
        case window::EventType::drop_text:
          return EventCode::drop_text;
        default:
          break;
        }
      }
      return EventCode::cancel;
    }();
    if (event_code != EventCode::cancel) {
      auto object = screen().find(get_point_from_mouse_position());
      if (event_code == EventCode::drop_file) {
        Event::send(object, event_code, new var::PathString(drop.path()));
      } else if (event_code == EventCode::drop_text) {
        //Event::send(object, event_code, new var::PathString(drop.path()));
      } else {
        Event::send(object, event_code);
      }
    }
  }
}

void Runtime::handle_window_event_callback(const window::Event &event) {
  if (window_event_callback()) {
    window_event_callback()(event, get_point_from_mouse_position());
  }
}

void Runtime::handle_mouse_event(const window::Event &event) {
  switch (event.type()) {
  case window::EventType::mouse_button_up:
  case window::EventType::mouse_button_down:
    m_mouse_event_queue.push(
      {event.get_mouse_button().point(),
       event.type() == window::EventType::mouse_button_up ? IsPressed::no
                                                          : IsPressed::yes});

    m_mouse_position = event.get_mouse_button().point();
    m_mouse_state = event.type() == window::EventType::mouse_button_up
                      ? window::Event::State::released
                      : window::Event::State::pressed;
    break;
  case window::EventType::mouse_motion:
    // may need to scale this
    if (m_mouse_wheel_timer.is_running() == false) {
      m_mouse_position = event.get_mouse_motion().point();
    }
    m_mouse_restore_position = event.get_mouse_motion().point();
    break;
  case window::EventType::mouse_wheel: {

    const auto is_scrollable = [&]() {
      auto object = screen().find(get_point_from_mouse_position());
      while (object.object()) {
        if (!object.has_flag(Flags::scrollable)) {
          if (object.has_flag(Flags::scroll_chain)) {
            object = object.get_parent();
          } else {
            object = Object();
          }
          continue;
        }

        const auto direction = object.get_scroll_direction();

        const auto scroll_top = object.get_scroll_top();
        const auto scroll_bottom = object.get_scroll_bottom();
        const auto scroll_left = object.get_scroll_left();
        const auto scroll_right = object.get_scroll_right();
        const auto scroll_x = object.get_scroll_x();
        const auto scroll_y = object.get_scroll_y();

        if (scroll_x > 0 && direction & Direction::horizontal) {
          return true;
        }

        if (scroll_y > 0 && direction & Direction::vertical) {
          return true;
        }

        if (scroll_top > 0 && direction & Direction::top) {
          return true;
        }

        if (scroll_bottom > 0 && direction & Direction::bottom) {
          return true;
        }

        if (scroll_left > 0 && direction & Direction::left) {
          return true;
        }

        if (scroll_right > 0 && direction & Direction::right) {
          return true;
        }

        object = object.get_parent();
      }

      return false;
    }();

    // m_mouse_wheel_event_queue.push({event, m_mouse_position});
    if (is_scrollable) {
      const auto delta_point = window::Point(
        event.get_mouse_wheel().point().x() * -1 * scroll_wheel_multiplier(),
        event.get_mouse_wheel().point().y() * scroll_wheel_multiplier());

      if (!m_mouse_wheel_timer.is_running()) {
        m_mouse_event_queue.push({m_mouse_position, IsPressed::yes});
        m_mouse_state = window::Event::State::pressed;
      }
      m_mouse_position += delta_point;
      m_mouse_wheel_timer.restart();
    }
  } break;
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

extern "C" void _lv_indev_scroll_throw_handler(_lv_indev_proc_t *proc);

void Runtime::update_wheel_event() {
  WheelEvent wheel_event;
  do {
    wheel_event = get_wheel_event();
    if (wheel_event.type != WheelEvent::Type::null) {

      auto object = screen().find(wheel_event.mouse);
#if 0

      // look for the first scrollable parent
      for (Object current = object; current.is_valid(); current = current.get_parent()) {
        if (current.get_scroll_bottom() != 0 || current.get_scroll_y() != 0) {
          const auto scroll_y = current.get_scroll_y();

          //scroll_by() is a lower level call
          //but using it causes the window to jump past the end
          //without bouncing back

          current.get<lvgl::Generic>().scroll_to_y(
            scroll_y + -1 * wheel_event.delta.y() * scroll_wheel_multiplier(),
            IsAnimate::yes);
          break;
        }
      }
#endif
    }
  } while (wheel_event.type != WheelEvent::Type::null);
}

void Runtime::resize_display(const window::Size &size) {
  const auto pixel_count = size.width() * size.height();

#if !LV_USE_GPU_SDL
  auto &inactive_frame = m_active_frame_buffer == m_display_frame0.data()
                           ? m_display_frame1
                           : m_display_frame0;
  auto &active_frame = m_active_frame_buffer == m_display_frame0.data()
                         ? m_display_frame0
                         : m_display_frame0;

  inactive_frame.resize(pixel_count);
  m_active_frame_buffer = inactive_frame.data();
#endif

  m_display_size = size;
  m_display_driver_container.display_driver.hor_res = size.width();
  m_display_driver_container.display_driver.ver_res = size.height();

  m_texture = window::Texture(
    m_renderer, window::PixelFormat::argb8888, window::Texture::Access::target, size);

#if !LV_USE_GPU_SDL
  active_frame.resize(pixel_count).fill(lv_color_white());
#endif

#if LV_USE_GPU_SDL
  lv_disp_draw_buf_init(
    &m_display_buffer, m_texture.native_value(), nullptr, pixel_count);
#else
  lv_disp_draw_buf_init(
    &m_display_buffer, m_display_frame0.data(), m_display_frame1.data(), pixel_count);
#endif

  lv_disp_drv_update(m_display, &m_display_driver_container.display_driver);
}

void Runtime::allocate_frames(const window::Size &size) {
#if !LV_USE_GPU_SDL
  const auto pixel_count = size.width() * size.height();
  m_display_frame0.resize(pixel_count);
  m_display_frame1.resize(pixel_count);
#endif
}

void Runtime::flush(
  lv_disp_drv_t *display_driver,
  const lv_area_t *area,
  lv_color_t *colors) noexcept {

  const lv_coord_t hres = display_driver->hor_res;
  const lv_coord_t vres = display_driver->ver_res;

  /*Return if the area is out the screen*/
  if (area->x2 < 0 || area->y2 < 0 || area->x1 > hres - 1 || area->y1 > vres - 1) {
    lv_disp_flush_ready(display_driver);
    return;
  }

#if !LV_USE_GPU_SDL
  m_active_frame_buffer = colors;
#endif

  /* TYPICALLY YOU DO NOT NEED THIS
   * If it was the last part to refresh update the texture of the window.*/
  if (lv_disp_flush_is_last(display_driver)) {
    update_window();
  }

  /*IMPORTANT! It must be called to tell the system the flush is ready*/
  lv_disp_flush_ready(display_driver);
}

void Runtime::flush_callback(
  lv_disp_drv_t *display_driver,
  const lv_area_t *area,
  lv_color_t *colors) {

  auto *runtime = reinterpret_cast<display_driver_container_t *>(display_driver)->self;
  runtime->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

void Runtime::read_mouse_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  auto *self = reinterpret_cast<Runtime *>(indev_drv->user_data);
  auto &events = self->m_mouse_event_queue;

  if (events.count()) {
    const auto &event = events.front();
    const auto point = self->get_point_from_window_point(event.point);
    data->point.x = point.x();
    data->point.y = point.y();
    data->state = (event.is_pressed == IsPressed::yes) ? LV_INDEV_STATE_PRESSED
                                                       : LV_INDEV_STATE_RELEASED;
    events.pop();
  } else {
    const auto mouse_point = self->get_point_from_mouse_position();
    data->point.x = mouse_point.x();
    data->point.y = mouse_point.y();
    data->state = self->m_mouse_state == window::Event::State::pressed
                    ? LV_INDEV_STATE_PRESSED
                    : LV_INDEV_STATE_RELEASED;
  }
  data->continue_reading = 0;
}

lvgl::Point Runtime::get_point_from_window_point(const window::Point &point) const {
  return Point(point.x() * m_dpi_scale, point.y() * m_dpi_scale);
}

lvgl::Point Runtime::get_point_from_mouse_position() const {
  return get_point_from_window_point(m_mouse_position);
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
    WheelEvent::Type::pixel, get_point_from_window_point(wheel_event.point()),
    get_point_from_window_point(event.position)};

  events.pop();

  return result;
}

#endif
