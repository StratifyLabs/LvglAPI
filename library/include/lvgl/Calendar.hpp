#ifndef LVGLAPI_LVGL_CALENDAR_HPP
#define LVGLAPI_LVGL_CALENDAR_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class Calendar : public ObjectAccess<Calendar> {
public:

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Calendar(Object parent, const Create& options);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CALENDAR_HPP
