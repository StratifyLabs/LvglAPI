#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Canvas : public ObjectAccess<Canvas> {
public:

  explicit Canvas(const char * name) : ObjectAccess(name){}
  explicit Canvas(const UserData & context) : ObjectAccess(context.cast_as_name()){}
  static const lv_obj_class_t * get_class(){
    return api()->canvas_class;
  }
private:
  OBJECT_ACCESS_FRIENDS();
  explicit Canvas(lv_obj_t * object){ m_object = object; }
  Canvas(Object parent, const Canvas &);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
