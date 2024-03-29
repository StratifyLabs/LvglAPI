#ifndef LVGLAPI_LVGL_RUNTIME_HPP
#define LVGLAPI_LVGL_RUNTIME_HPP

#include <chrono/MicroTime.hpp>
#include <thread/Mutex.hpp>
#include <var/Array.hpp>
#include <var/Vector.hpp>

#if defined __link
#include <var/Queue.hpp>
#include <chrono/ClockTimer.hpp>
#include <window/Texture.hpp>
#include <window/Event.hpp>
#endif

#include "Style.hpp"
#include "Group.hpp"

namespace lvgl {

class Runtime : public Api {
public:
  using TaskCallback = api::Function<void(void)>;

#if defined __StratifyOS__
  Runtime();
#endif

  Runtime(const Runtime &) = delete;
  Runtime(Runtime &&) = delete;
  Runtime &operator=(const Runtime &) = delete;
  Runtime &operator=(Runtime &&) = delete;

  Runtime &loop();
  Runtime &refresh();

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  Runtime &push(TaskCallback callback, chrono::MicroTime deferred = chrono::MicroTime());
  Runtime &push(chrono::MicroTime deferred, TaskCallback callback){
    return push(callback, deferred);
  }
#endif

#if defined __link
  using WindowEventCallback = void (*)(const window::Event & event, const Point & mouse_location);

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

  lv_disp_t * display();

  const lv_disp_t * display() const;

private:
  API_AF(Runtime, chrono::MicroTime, period, 20_milliseconds);
  API_AF(Runtime, float, increment_scale, 1.0f);
  API_AB(Runtime, stopped, false);

  struct Task {
    TaskCallback callback;
    chrono::ClockTime wait_until;
  };

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
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

  enum class IsPressed {
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

  struct MouseButtonEvent {
    window::Point point;
    IsPressed is_pressed;
  };

  float m_dpi_scale = 1.0f;
  window::Size m_display_size;
  window::Window m_window;
  window::Renderer m_renderer;
  window::Texture m_texture;
  var::Queue<MouseButtonEvent> m_mouse_event_queue;
  var::Queue<KeyEvent> m_keyboard_event_queue;
  var::Queue<MouseWheelEvent> m_mouse_wheel_event_queue;
  window::Point m_mouse_position;
  window::Point m_mouse_restore_position;
  window::EventState m_mouse_state;
  lv_indev_drv_t m_keyboard_driver{};
  lv_indev_drv_t m_mouse_driver{};
  lv_indev_t *m_keyboard_device = nullptr;
  lv_indev_t *m_mouse_device = nullptr;
  lvgl::Group m_group;
  chrono::ClockTimer m_mouse_wheel_timer;

  API_AF(Runtime, WindowEventCallback, window_event_callback, nullptr);

  lv_disp_t * m_display = nullptr;
  lv_disp_draw_buf_t m_display_buffer{};

  typedef struct {
    lv_disp_drv_t display_driver;
    Runtime * self;
  } display_driver_container_t;

  display_driver_container_t m_display_driver_container{};
#if !LV_USE_GPU_SDL
  var::Vector<lv_color_t> m_display_frame0;
  var::Vector<lv_color_t> m_display_frame1;
  lv_color_t *m_active_frame_buffer = nullptr;
#else
  typedef struct {
    void * renderer;
    void * user_data;
  } lv_draw_sdl_drv_param_t;
  lv_draw_sdl_drv_param_t m_sdl_gpu_driver_parameters{};
#endif

  API_AF(Runtime,u32,scroll_wheel_multiplier,5);

  void initialize_display();
  void initialize_devices();
  void update_window();
  void update_events();
  void update_wheel_event();

  void handle_mouse_event(const window::Event &event);
  void handle_keyboard_event(const window::Event &event);
  void handle_touch_finger_event(const window::Event &event);
  void handle_window_event(const window::Event &event);
  void handle_drop_event(const window::Event &event);
  void handle_window_event_callback(const window::Event &event);
  void resize_display(const window::Size & size);
  void allocate_frames(const window::Size & size);

  lvgl::WheelEvent get_wheel_event();
  lvgl::Point get_point_from_window_point(const window::Point & point) const;
  lvgl::Point get_point_from_mouse_position() const;

  void flush(
    lv_disp_drv_t *display_driver,
    const lv_area_t *area,
    lv_color_t *colors) noexcept;

  static void flush_callback(
    lv_disp_drv_t *display_driver,
    const lv_area_t *area,
    lv_color_t *colors);

  static void read_mouse_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
  static void read_keyboard_callback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

#endif
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_RUNTIME_HPP
