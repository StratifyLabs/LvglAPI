#ifndef LVGLAPI_LVGL_PERIODICTIMER_HPP
#define LVGLAPI_LVGL_PERIODICTIMER_HPP

#include <chrono/MicroTime.hpp>

#include "Types.hpp"

namespace lvgl {

class PeriodicTimer : public Api{
public:

  using Callback = void (*)(lv_timer_t *);

  PeriodicTimer();
  PeriodicTimer(const chrono::MicroTime & period, Callback callback);

  PeriodicTimer(const PeriodicTimer & a) = delete;
  PeriodicTimer& operator=(const PeriodicTimer & a) = delete;

  PeriodicTimer(PeriodicTimer && a){
    std::swap(m_timer, a.m_timer);
  }

  PeriodicTimer& operator=(PeriodicTimer && a){
    std::swap(m_timer, a.m_timer);
    return *this;
  };

  ~PeriodicTimer();

  PeriodicTimer& set_period(const chrono::MicroTime & period){
    API_ASSERT(m_timer != nullptr);
    api()->timer_set_period(m_timer, period.milliseconds());
    return *this;
  }

  PeriodicTimer& set_callback(Callback callback){
    API_ASSERT(m_timer != nullptr);
    api()->timer_set_cb(m_timer, callback);
    return *this;
  }

  PeriodicTimer& pause(){
    API_ASSERT(m_timer != nullptr);
    api()->timer_pause(m_timer);
    return *this;
  }

  PeriodicTimer& resume(){
    API_ASSERT(m_timer != nullptr);
    api()->timer_resume(m_timer);
    return *this;
  }

  PeriodicTimer& set_repeat_count(s32 count){
    API_ASSERT(m_timer != nullptr);
    api()->timer_set_repeat_count(m_timer, count);
    return *this;
  }

private:
  lv_timer_t * m_timer;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_PERIODICTIMER_HPP
