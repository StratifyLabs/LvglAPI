#ifndef LVGLAPI_LVGL_GAUGE_HPP
#define LVGLAPI_LVGL_GAUGE_HPP


#include "Object.hpp"

namespace lv {
class Gauge : public ObjectAccess<Gauge>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Gauge(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_GAUGE_HPP
