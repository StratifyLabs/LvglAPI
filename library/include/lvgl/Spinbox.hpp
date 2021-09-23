#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinbox : public ObjectAccess<Spinbox>
{
public:
  explicit Spinbox(const char * name) : ObjectAccess(name){}
  explicit Spinbox(const Context & context) : ObjectAccess(context.cast_as_name()){}


private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinbox(lv_obj_t * object){ m_object = object; }
  Spinbox(Object parent, const Spinbox &);

};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
