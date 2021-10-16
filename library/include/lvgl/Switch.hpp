#ifndef LVGLAPI_LVGL_SWITCH_HPP
#define LVGLAPI_LVGL_SWITCH_HPP


#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Switch : public ObjectAccess<Switch>
{
public:
  explicit Switch(const char * name);

  static const lv_obj_class_t * get_class(){
    return api()->switch_class;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Switch(lv_obj_t * object){ m_object = object; }

};

}

#endif // LVGLAPI_LVGL_SWITCH_HPP
