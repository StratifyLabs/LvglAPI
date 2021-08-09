#include "lvgl/PeriodicTimer.hpp"

using namespace lvgl;

PeriodicTimer::PeriodicTimer() {
  API_PRINTF_TRACE_LINE();

}

PeriodicTimer::PeriodicTimer(lv_timer_t * timer) : m_timer(timer){
  API_PRINTF_TRACE_LINE();

}


PeriodicTimer::PeriodicTimer(
  const char *name,
  const chrono::MicroTime &period,
  Callback callback) : m_needs_free(true) {
  API_PRINTF_TRACE_LINE();
  m_timer = api()->timer_create(callback, period.milliseconds(), (void *)name);
  API_PRINTF_TRACE_LINE();
}

PeriodicTimer::~PeriodicTimer() {
  if (m_timer && m_needs_free) {
    api()->timer_del(m_timer);
  }
}
