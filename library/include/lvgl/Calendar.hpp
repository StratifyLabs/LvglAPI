#ifndef LVGLAPI_LVGL_CALENDAR_HPP
#define LVGLAPI_LVGL_CALENDAR_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Calendar : public ObjectAccess<Calendar> {
public:


  explicit Calendar(const char * name) : ObjectAccess(name){}
  explicit Calendar(const UserData & context) : ObjectAccess(context.cast_as_name()){}

  static const lv_obj_class_t * get_class(){
    return api()->calendar_class;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Calendar(lv_obj_t * object){ m_object = object; }
  Calendar(Object parent, const Calendar &);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CALENDAR_HPP
