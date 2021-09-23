#ifndef LVGLAPI_LVGL_SWITCH_HPP
#define LVGLAPI_LVGL_SWITCH_HPP


#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Switch : public ObjectAccess<Switch>
{
public:
  explicit Switch(const char * name) : ObjectAccess(name){}
  explicit Switch(const Context & context) : ObjectAccess(context.cast_as_name()){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Switch(lv_obj_t * object){ m_object = object; }
  Switch(Object parent, const Switch &);

};

}

#endif // LVGLAPI_LVGL_SWITCH_HPP
