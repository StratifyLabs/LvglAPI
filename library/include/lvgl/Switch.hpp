#ifndef LVGLAPI_LVGL_SWITCH_HPP
#define LVGLAPI_LVGL_SWITCH_HPP


#include "ObjectAccess.hpp"

namespace lvgl {

class Switch : public ObjectAccess<Switch>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Switch(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_SWITCH_HPP
