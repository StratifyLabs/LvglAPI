#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Object.hpp"

namespace lv {

class Window : public ObjectAccess<Window> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  private:
    API_AF(Create, lv_coord_t, height, 15_percent);
  };
  Window(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_WINDOW_HPP
