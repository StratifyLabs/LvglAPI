#ifndef LVGLAPI_LVGL_CALENDAR_HPP
#define LVGLAPI_LVGL_CALENDAR_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Calendar : public ObjectAccess<Calendar> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Calendar);
  LVGL_OBJECT_ACCESS_GET_CLASS(calendar_class);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CALENDAR_HPP
