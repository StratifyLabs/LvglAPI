#ifndef LVGLAPI_LVGL_MASK_HPP
#define LVGLAPI_LVGL_MASK_HPP


#include "ObjectAccess.hpp"

namespace lvgl {

class Mask : public ObjectAccess<Mask>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Mask(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_MASK_HPP
