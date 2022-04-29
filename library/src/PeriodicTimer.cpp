#include "lvgl/PeriodicTimer.hpp"
#include "lvgl/UserData.hpp"

using namespace lvgl;

PeriodicTimer::PeriodicTimer(lv_timer_t *timer)
  : m_resource({.needs_free = false, .timer = timer}) {}

PeriodicTimer::PeriodicTimer(
  const Object & associated_object,
  const chrono::MicroTime &period,
  Callback callback)
  : m_resource(
    {.needs_free = true,
     .timer = api()->timer_create(callback, period.milliseconds(), nullptr)},
    &deleter) {
  m_resource.pointer_to_value()->timer->user_data = associated_object.object();
}

void PeriodicTimer::deleter(PeriodicTimer::Context *context) {
  auto *timer = context->timer;
  if (timer && context->needs_free) {
    api()->timer_del(timer);
  }
}

