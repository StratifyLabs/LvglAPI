#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Object.hpp"

namespace lv {

class List : public ObjectAccess<List>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  List(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_LIST_HPP
