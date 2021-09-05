#ifndef LVGLAPI_LVGL_GAUGE_HPP
#define LVGLAPI_LVGL_GAUGE_HPP


#include "ObjectAccess.hpp"
OBJECT_ACCESS_FORWARD_FRIENDS();

namespace lvgl {
class Gauge : public ObjectAccess<Gauge>
{
public:
  explicit Gauge(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Gauge(lv_obj_t * object){ m_object = object; }
  Gauge(Object parent, const Gauge &);
};

}

#endif // LVGLAPI_LVGL_GAUGE_HPP
