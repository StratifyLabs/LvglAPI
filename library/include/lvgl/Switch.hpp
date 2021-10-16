#ifndef LVGLAPI_LVGL_SWITCH_HPP
#define LVGLAPI_LVGL_SWITCH_HPP


#include "ObjectAccess.hpp"

namespace lvgl {


class Switch : public ObjectAccess<Switch>
{
public:
  explicit Switch(const char * name = "");
  explicit Switch(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->switch_class;
  }

};

}

#endif // LVGLAPI_LVGL_SWITCH_HPP
