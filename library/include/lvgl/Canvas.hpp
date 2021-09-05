#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Canvas : public ObjectAccess<Canvas> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  explicit Canvas(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Canvas(lv_obj_t * object){ m_object = object; }
  Canvas(Object parent, const Canvas &);
  Canvas(Object parent, const Create & options);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
