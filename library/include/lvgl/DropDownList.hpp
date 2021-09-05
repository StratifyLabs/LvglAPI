#ifndef LVGLAPI_LVGL_DROPDOWNLIST_HPP
#define LVGLAPI_LVGL_DROPDOWNLIST_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class DropDownList : public ObjectAccess<DropDownList>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  explicit DropDownList(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit DropDownList(lv_obj_t * object){ m_object = object; }
  DropDownList(Object parent, const DropDownList & options);
  DropDownList(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_DROPDOWNLIST_HPP
