#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Spinbox : public ObjectAccess<Spinbox>
{
public:
  explicit Spinbox(const char * name);
  explicit Spinbox(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->spinbox_class;
  }

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
