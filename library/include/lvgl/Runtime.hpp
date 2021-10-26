#ifndef LVGLAPI_LVGL_RUNTIME_HPP
#define LVGLAPI_LVGL_RUNTIME_HPP

#include <chrono/MicroTime.hpp>
#include <var/Array.hpp>
#include <var/Vector.hpp>
#include <thread/Mutex.hpp>

#include "Style.hpp"

namespace lvgl {

class Runtime : public Api {
public:
  using TaskCallback = void (*)(void*);

  Runtime();

  Runtime(const Runtime &) = delete;
  Runtime(Runtime &&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  Runtime& operator=(Runtime&&) = delete;

  static void *thread_loop(void *args) {
    reinterpret_cast<Runtime *>(args)->loop();
    return nullptr;
  }

  Runtime& loop();
  Runtime& refresh();

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  Runtime& push(TaskCallback callback, void * context = nullptr);
#endif


private:
  API_AF(Runtime, chrono::MicroTime, period, 5_milliseconds);
  API_AF(Runtime, float, increment_scale, 1.0f);
  API_AB(Runtime, stopped, false);

#if defined LVGL_RUNTIME_TASK_ARRAY_SIZE
  struct Task {
    TaskCallback callback;
    void * context;
  };
  thread::Mutex m_task_mutex;
#if LVGL_RUNTIME_TASK_ARRAY_SIZE == 0
  var::Vector<Task> m_task_list;
#else
  var::Array<Task,LVGL_RUNTIME_TASK_ARRAY_SIZE> m_task_list;
#endif
#endif


};

} // namespace lvgl

#endif // LVGLAPI_LVGL_RUNTIME_HPP
