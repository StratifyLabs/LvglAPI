#if __StratifyOS__
#include <sos/sos.h>
#endif

#include "lvgl_api.h"

#include "lvgl/Style.hpp"
#include "lvgl/Runtime.hpp"

using namespace lvgl;

Runtime& Runtime::setup(){
#if __StratifyOS__
  kernel_request(LVGL_REQUEST_START, nullptr);
#endif
  return *this;
}

void Runtime::loop(){
  while( is_stopped() == false ){
    chrono::wait(period());
    api()->tick_inc(period().milliseconds());
    api()->timer_handler();
  }

#if __StratifyOS__
  kernel_request(LVGL_REQUEST_STOP, nullptr);
#endif
}

