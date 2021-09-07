#ifndef LVGLAPI_LVGL_RUNTIME_HPP
#define LVGLAPI_LVGL_RUNTIME_HPP

#include <chrono/MicroTime.hpp>

#include "Style.hpp"

namespace lvgl {

class Runtime : public Api {
public:
  Runtime();

  Runtime(const Runtime &) = delete;
  Runtime(Runtime &&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  Runtime& operator=(Runtime&&) = delete;

  static void *thread_loop(void *args) {
    reinterpret_cast<Runtime *>(args)->loop();
    return nullptr;
  }

  Runtime& loop();

  Runtime& refresh();



private:
  API_AF(Runtime, chrono::MicroTime, period, 5_milliseconds);
  API_AF(Runtime, float, increment_scale, 1.0f);
  API_AB(Runtime, stopped, false);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_RUNTIME_HPP
