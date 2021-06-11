#ifndef LVGLAPI_LVGL_ROLLER_HPP
#define LVGLAPI_LVGL_ROLLER_HPP

#include "Object.hpp"

namespace lv {

class Roller : public ObjectAccess<Roller>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Roller(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_ROLLER_HPP
