#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class SpinBox : public ObjectAccess<SpinBox>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  explicit SpinBox(const char * name) : ObjectAccess(name){}


private:
  OBJECT_ACCESS_FRIENDS();
  explicit SpinBox(lv_obj_t * object){ m_object = object; }
  SpinBox(Object parent, const SpinBox &);
  SpinBox(Object parent, const Create & options);

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
