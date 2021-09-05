#ifndef LVGLAPI_LVGL_MASK_HPP
#define LVGLAPI_LVGL_MASK_HPP


#include "ObjectAccess.hpp"

namespace lvgl {

OBJECT_ACCESS_FORWARD_FRIENDS();

class Mask : public ObjectAccess<Mask>
{
public:
  Mask(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Mask(lv_obj_t * object){ m_object = object; }
  Mask(Object parent, const Mask &);

};

}

#endif // LVGLAPI_LVGL_MASK_HPP
