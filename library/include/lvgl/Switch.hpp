#ifndef LVGLAPI_LVGL_SWITCH_HPP
#define LVGLAPI_LVGL_SWITCH_HPP


#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Switch : public ObjectAccess<Switch>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  explicit Switch(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Switch(lv_obj_t * object){ m_object = object; }
  Switch(Object parent, const Switch &);
  Switch(Object parent, const Create & options);

};

}

#endif // LVGLAPI_LVGL_SWITCH_HPP
