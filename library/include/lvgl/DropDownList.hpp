#ifndef LVGLAPI_LVGL_DROPDOWNLIST_HPP
#define LVGLAPI_LVGL_DROPDOWNLIST_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class DropDownList : public ObjectAccess<DropDownList>
{
public:
  explicit DropDownList(const char * name) : ObjectAccess(name){}
  explicit DropDownList(const Context & context) : ObjectAccess(context.cast_as_name()){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit DropDownList(lv_obj_t * object){ m_object = object; }
  DropDownList(Object parent, const DropDownList & options);
};

}

#endif // LVGLAPI_LVGL_DROPDOWNLIST_HPP
