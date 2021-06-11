#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "Object.hpp"

namespace lv {

class Canvas : public ObjectAccess<Canvas> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Canvas(Object parent, const Create & options);
};

} // namespace lv

#endif // LVGLAPI_LVGL_CANVAS_HPP
