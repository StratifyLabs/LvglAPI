#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinner : public ObjectAccess<Spinner>
{
public:

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  private:
    API_AF(Create, u32, time, 1000);
    API_AF(Create, u32, arc_length, 60);
  };

  explicit Spinner(const char * name) : ObjectAccess(name){}


private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinner(lv_obj_t * object){ m_object = object; }
  Spinner(Object parent, const Spinner & options);
  Spinner(Object parent, const Create & options);

  API_AF(Spinner, u32, time, 1000);
  API_AF(Spinner, u32, arc_length, 60);

};

}

#endif // LVGLAPI_LVGL_SPINNER_HPP
