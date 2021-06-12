#ifndef LVGLAPI_LVGL_ARC_HPP
#define LVGLAPI_LVGL_ARC_HPP

#include "Object.hpp"

namespace lv {

class Arc : public ObjectAccess<Arc> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Arc(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_ARC_HPP
