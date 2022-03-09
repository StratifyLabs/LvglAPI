#include "lvgl/PeriodicTimer.hpp"

using namespace lvgl;

PeriodicTimer::PeriodicTimer(lv_timer_t * timer) : m_timer(timer){}


PeriodicTimer::PeriodicTimer(
  const char *name,
  const chrono::MicroTime &period,
  Callback callback, void * user_data) : m_needs_free(true) {
  m_timer = api()->timer_create(callback, period.milliseconds(), (void *)name);
  set_user_data(user_data);
}

PeriodicTimer::~PeriodicTimer() {
  if (m_timer && m_needs_free) {
    api()->timer_del(m_timer);
  }
}

