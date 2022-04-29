#ifndef LVGLAPI_LVGL_PERIODICTIMER_HPP
#define LVGLAPI_LVGL_PERIODICTIMER_HPP

#include <chrono/MicroTime.hpp>

#include "Object.hpp"

namespace lvgl {

class PeriodicTimer : public Api {
public:
  using Callback = void (*)(lv_timer_t *);

  PeriodicTimer() = default;
  explicit PeriodicTimer(lv_timer_t *timer);

  PeriodicTimer(
    const Object & associated_object,
    const chrono::MicroTime &period,
    Callback callback);

  PeriodicTimer &set_period(const chrono::MicroTime &period) {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_set_period(m_resource.pointer_to_value()->timer, period.milliseconds());
    return *this;
  }

  PeriodicTimer &set_callback(Callback callback) {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_set_cb(m_resource.pointer_to_value()->timer, callback);
    return *this;
  }

  PeriodicTimer &reset() {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_reset(m_resource.pointer_to_value()->timer);
    return *this;
  }

  PeriodicTimer &make_ready() {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_ready(m_resource.pointer_to_value()->timer);
    return *this;
  }

  PeriodicTimer &pause() {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_pause(m_resource.pointer_to_value()->timer);
    return *this;
  }

  PeriodicTimer &resume() {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_resume(m_resource.pointer_to_value()->timer);
    return *this;
  }

  PeriodicTimer &set_repeat_count(s32 count) {
    API_ASSERT(m_resource.pointer_to_value()->timer != nullptr);
    api()->timer_set_repeat_count(m_resource.pointer_to_value()->timer, count);
    return *this;
  }

  PeriodicTimer &set_repeat_infinite() { return set_repeat_count(-1); }

  template <class Type> Type get_associated_object() const {
    return Type(
      reinterpret_cast<lv_obj_t *>(m_resource.pointer_to_value()->timer->user_data));
  }

private:
  struct Context {
    bool needs_free = false;
    lv_timer_t *timer = nullptr;
  };

  static void deleter(Context *context);
  using Resource = api::SystemResource<Context, decltype(&deleter)>;

  Resource m_resource;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_PERIODICTIMER_HPP
