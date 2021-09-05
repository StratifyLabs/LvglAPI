#ifndef LVGLAPI_LVGL_LINEMETER_HPP
#define LVGLAPI_LVGL_LINEMETER_HPP


#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class LineMeter : public ObjectAccess<LineMeter>
{
public:
  explicit LineMeter(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit LineMeter(lv_obj_t * object){ m_object = object; }
  LineMeter(Object parent, const LineMeter &);

};
}

#endif // LVGLAPI_LVGL_LINEMETER_HPP
