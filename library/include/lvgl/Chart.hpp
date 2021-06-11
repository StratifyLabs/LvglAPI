#ifndef LVGLAPI_LVGL_CHART_HPP
#define LVGLAPI_LVGL_CHART_HPP

#include "Object.hpp"

namespace lv {

class Chart : public ObjectAccess<Chart>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Chart(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_CHART_HPP
