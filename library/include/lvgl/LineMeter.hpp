#ifndef LVGLAPI_LVGL_LINEMETER_HPP
#define LVGLAPI_LVGL_LINEMETER_HPP


#include "Object.hpp"

namespace lv {

class LineMeter : public ObjectAccess<LineMeter>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  LineMeter(Object parent, const Create & options);
};
}

#endif // LVGLAPI_LVGL_LINEMETER_HPP
