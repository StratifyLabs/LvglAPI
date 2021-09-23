#ifndef LVGLAPI_LVGL_LINE_HPP
#define LVGLAPI_LVGL_LINE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Line : public ObjectAccess<Line> {
public:
  explicit Line(const char * name) : ObjectAccess(name){}
  explicit Line(const Context & context) : ObjectAccess(context.cast_as_name()){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Line(lv_obj_t * object){ m_object = object; }
  Line(Object parent, const Line &);

};

}

#endif // LVGLAPI_LVGL_LINE_HPP
