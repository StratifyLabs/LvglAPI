#if __StratifyOS__
#include <sos/sos.h>
#endif

#include <chrono/ClockTimer.hpp>

#include "lvgl_api.h"

#include "lvgl/Runtime.hpp"
#include "lvgl/Style.hpp"

using namespace lvgl;

Runtime::Runtime() {
#if __StratifyOS__
  kernel_request(LVGL_REQUEST_START, nullptr);
#endif

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
}

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
