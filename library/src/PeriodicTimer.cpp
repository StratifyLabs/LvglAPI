#include "lvgl/PeriodicTimer.hpp"

using namespace lvgl;

PeriodicTimer::PeriodicTimer(){}


PeriodicTimer::PeriodicTimer(const chrono::MicroTime & period, Callback callback){

}


PeriodicTimer::~PeriodicTimer(){
  if( m_timer != nullptr ){
    api()->timer_del(m_timer);
  }
}
