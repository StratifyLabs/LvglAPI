#ifndef LVGLAPI_LVGL_LINE_HPP
#define LVGLAPI_LVGL_LINE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class Line : public ObjectAccess<Line> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Line(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_LINE_HPP
