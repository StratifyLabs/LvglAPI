#ifndef LVGLAPI_LVGL_CALENDAR_HPP
#define LVGLAPI_LVGL_CALENDAR_HPP

#include "Object.hpp"

namespace lv {

class Calendar : public ObjectAccess<Calendar> {
public:

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Calendar(Object parent, const Create& options);
};

} // namespace lv

#endif // LVGLAPI_LVGL_CALENDAR_HPP
