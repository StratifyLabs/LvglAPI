#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Canvas : public ObjectAccess<Canvas> {
public:

  explicit Canvas(const char * name) : ObjectAccess(name){}
  explicit Canvas(const Context & context) : ObjectAccess(context.cast_as_name()){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Canvas(lv_obj_t * object){ m_object = object; }
  Canvas(Object parent, const Canvas &);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
