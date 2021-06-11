#ifndef LVGLAPI_LVGL_DROPDOWNLIST_HPP
#define LVGLAPI_LVGL_DROPDOWNLIST_HPP

#include "Object.hpp"

namespace lv {

class DropDownList : public ObjectAccess<DropDownList>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  DropDownList(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_DROPDOWNLIST_HPP
