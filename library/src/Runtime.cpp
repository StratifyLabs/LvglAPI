#if __StratifyOS__
#include <sos/sos.h>
#endif

#include "lvgl_api.h"

#include "lvgl/Style.hpp"
#include "lvgl/Runtime.hpp"

using namespace lvgl;

Runtime::Runtime(){
#if __StratifyOS__
  kernel_request(LVGL_REQUEST_START, nullptr);
#endif
}

Runtime& Runtime::loop(){
  while( is_stopped() == false ){
    refresh();
  }

#if __StratifyOS__
  kernel_request(LVGL_REQUEST_STOP, nullptr);
#endif
  return *this;
}

Runtime& Runtime::refresh(){
  chrono::wait(period());
  api()->tick_inc(period().milliseconds() * increment_scale());
  api()->timer_handler();
  return *this;
}


