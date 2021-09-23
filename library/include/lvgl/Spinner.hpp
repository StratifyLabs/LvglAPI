#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinner : public ObjectAccess<Spinner>
{
public:

  explicit Spinner(const char * name) : ObjectAccess(name){}
  explicit Spinner(const Context & context) : ObjectAccess(context.cast_as_name()){}


private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinner(lv_obj_t * object){ m_object = object; }
  Spinner(Object parent, const Spinner & options);

  API_AF(Spinner, u32, initial_time, 1000);
  API_AF(Spinner, u32, initial_arc_length, 60);

};

}

#endif // LVGLAPI_LVGL_SPINNER_HPP
