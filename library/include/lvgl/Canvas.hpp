#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class Canvas : public ObjectAccess<Canvas> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Canvas(Object parent, const Create & options);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
