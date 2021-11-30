#ifndef LVGLAPI_LVGL_RUNTIME_HPP
#define LVGLAPI_LVGL_RUNTIME_HPP

#include <chrono/MicroTime.hpp>
#include <thread/Mutex.hpp>
#include <var/Array.hpp>
#include <var/Vector.hpp>

#if defined __link
#include <var/Queue.hpp>
#include <window/Texture.hpp>
#include <window/Event.hpp>
#endif

#include "Style.hpp"
#include "Group.hpp"

namespace lvgl {

class Runtime : public Api {
public:
  using TaskCallback = void (*)(void *);

#if defined __StratifyOS__
  Runtime();
#endif

  Runtime(const Runtime &) = delete;
  Runtime(Runtime &&) = delete;
  Runtime &operator=(const Runtime &) = delete;
  Runtime &operator=(Runtime &&) = delete;

  static void *thread_loop(void *args) {
    reinterpret_cast<Runtime *>(args)->loop();
    return nullptr;
  }

  Runtime &loop();
  Runtime &refresh();

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  Runtime &push(TaskCallback callback, void *context = nullptr);
  Runtime &push(void *context, TaskCallback callback){
    return push(callback, context);
  }
#endif

#if defined __link
  Runtime(
    const char *title,
    const window::Point &location,
    const window::Size &size,
    window::Window::Flags flags);

  window::Window & window(){
    return m_window;
  }

  const window::Window & window() const {
    return m_window;
  }

  Group & keyboard_group(){
    return m_group;
  }

  static lvgl::WheelEvent get_wheel_event_callback(void * context){
    return reinterpret_cast<Runtime*>(context)->get_wheel_event();
  }
#endif

private:
  API_AF(Runtime, chrono::MicroTime, period, 5_milliseconds);
  API_AF(Runtime, float, increment_scale, 1.0f);
  API_AB(Runtime, stopped, false);

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  struct Task {
    TaskCallback callback;
    void *context;
  };
  thread::Mutex m_task_mutex;
#if LVGL_RUNTIME_TASK_ARRAY_SIZE == 0
  var::Vector<Task> m_task_list;
#else
  var::Array<Task, LVGL_RUNTIME_TASK_ARRAY_SIZE> m_task_list;
#endif
#endif

#if defined __link

  enum class IsClipboard {
    no, yes
  };

  struct KeyEvent {
    window::Event::State state;
    window::KeyModifier modifier;
    window::ScanCode scan_code;
    u32 key_code;
    IsClipboard is_clipboard;
  };

  struct MouseWheelEvent {
    window::Event event;
    window::Point position;
  };

  window::Window m_window;
  window::Renderer m_renderer;
  window::Texture m_texture;
  var::Queue<window::Event> m_mouse_event_queue;
  var::Queue<KeyEvent> m_keyboard_event_queue;
  var::Queue<MouseWheelEvent> m_mouse_wheel_event_queue;
  window::Point m_mouse_position;
  window::EventState m_mouse_state;
  lv_indev_drv_t m_keyboard_driver{};
  lv_indev_drv_t m_mouse_driver{};
  lv_indev_t *m_keyboard_device = nullptr;
  lv_indev_t *m_mouse_device = nullptr;
  lvgl::Group m_group;

  lv_disp_t * m_display;
  lv_disp_draw_buf_t m_display_buffer{};
  lv_disp_drv_t m_display_driver{};
  var::Vector<lv_color_t> m_display_frame0;
  var::Vector<lv_color_t> m_display_frame1;
  lv_color_t *m_active_frame_buffer = nullptr;
  window::Size m_display_size;
  float m_dpi_scale = 1.0f;

  API_AF(Runtime,u32,scroll_wheel_multiplier,20);

  void initialize_display();
  void initialize_devices();
  void update_window();
  void update_events();
  void update_wheel_event();

  void handle_mouse_event(const window::Event &event);
  void handle_keyboard_event(const window::Event &event);
  void handle_window_event(const window::Event &event);
  void resize_display(const window::Size & size);
  void allocate_frames(const window::Size & size);

  lvgl::WheelEvent get_wheel_event();

  static void flush_callback(
    lv_disp_drv_t *display_driver,
    const lv_area_t *area,
    lv_color_t *colors);

  void flush(
    lv_disp_drv_t *display_driver,
    const lv_area_t *area,
    lv_color_t *colors) noexcept;

  static void read_mouse_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
  static void read_keyboard_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

#endif
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_RUNTIME_HPP
