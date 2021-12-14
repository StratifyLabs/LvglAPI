#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Canvas : public ObjectAccess<Canvas> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Canvas);

  static const lv_obj_class_t * get_class(){
    return api()->canvas_class;
  }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
