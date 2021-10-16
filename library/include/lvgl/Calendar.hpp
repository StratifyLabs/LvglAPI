#ifndef LVGLAPI_LVGL_CALENDAR_HPP
#define LVGLAPI_LVGL_CALENDAR_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Calendar : public ObjectAccess<Calendar> {
public:
  explicit Calendar(const char * name);
  explicit Calendar(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->calendar_class;
  }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CALENDAR_HPP
