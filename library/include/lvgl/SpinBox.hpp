#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class SpinBox : public ObjectAccess<SpinBox>
{
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(SpinBox);

  static const lv_obj_class_t * get_class(){
    return api()->spinbox_class;
  }

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
