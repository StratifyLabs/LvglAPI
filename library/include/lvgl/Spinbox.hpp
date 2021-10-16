#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinbox : public ObjectAccess<Spinbox>
{
public:
  explicit Spinbox(const char * name);

  static const lv_obj_class_t * get_class(){
    return api()->spinbox_class;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinbox(lv_obj_t * object){ m_object = object; }

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
