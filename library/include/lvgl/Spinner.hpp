#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

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


  Spinner(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_SPINNER_HPP
