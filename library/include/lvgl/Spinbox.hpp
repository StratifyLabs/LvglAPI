#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class SpinBox : public ObjectAccess<SpinBox>
{
public:
  explicit SpinBox(const char * name) : ObjectAccess(name){}


private:
  OBJECT_ACCESS_FRIENDS();
  explicit SpinBox(lv_obj_t * object){ m_object = object; }
  SpinBox(Object parent, const SpinBox &);

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
