#ifndef LVGLAPI_LVGL_PERIODICTIMER_HPP
#define LVGLAPI_LVGL_PERIODICTIMER_HPP

#include <chrono/MicroTime.hpp>

#include "Types.hpp"

namespace lvgl {

class PeriodicTimer : public Api{
public:

  using Callback = void (*)(lv_timer_t *);

  PeriodicTimer();
  PeriodicTimer(lv_timer_t * timer);

  PeriodicTimer(const char* name, const chrono::MicroTime & period, Callback callback);

  PeriodicTimer(const PeriodicTimer & a) = delete;
  PeriodicTimer& operator=(const PeriodicTimer & a) = delete;

  PeriodicTimer(PeriodicTimer && a){
    std::swap(m_timer, a.m_timer);
    std::swap(m_needs_free, a.m_needs_free);
  }

  PeriodicTimer& operator=(PeriodicTimer && a){
    std::swap(m_timer, a.m_timer);
    std::swap(m_needs_free, a.m_needs_free);
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

  PeriodicTimer& reset(){
    API_ASSERT(m_timer != nullptr);
    api()->timer_reset(m_timer);
    return *this;
  }

  PeriodicTimer& make_ready(){
    API_ASSERT(m_timer != nullptr);
    api()->timer_ready(m_timer);
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

  PeriodicTimer& set_repeat_infinite(){
    return set_repeat_count(-1);
  }

  const char * name() const {
    return reinterpret_cast<char*>(m_timer->user_data);
  }

private:
  lv_timer_t * m_timer = nullptr;
  bool m_needs_free = false;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_PERIODICTIMER_HPP
