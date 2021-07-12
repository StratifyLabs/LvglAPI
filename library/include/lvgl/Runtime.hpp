#ifndef LVGLAPI_LVGL_RUNTIME_HPP
#define LVGLAPI_LVGL_RUNTIME_HPP

#include <chrono/MicroTime.hpp>

#include "Style.hpp"

namespace lvgl {

class Runtime : public Api
{
public:
  void setup();

  static void * thread_loop(void * args){
    reinterpret_cast<Runtime*>(args)->loop();
    return nullptr;
  }

  void loop();

private:
  API_AF(Runtime, chrono::MicroTime, period, 5_milliseconds);
  API_AB(Runtime, stopped, false);

};

}

#endif // LVGLAPI_LVGL_RUNTIME_HPP
