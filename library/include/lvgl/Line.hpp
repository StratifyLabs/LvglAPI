#ifndef LVGLAPI_LVGL_LINE_HPP
#define LVGLAPI_LVGL_LINE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Line : public ObjectAccess<Line> {
public:
  explicit Line(const char * name);


  static const lv_obj_class_t * get_class(){
    return api()->line_class;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Line(lv_obj_t * object){ m_object = object; }

};

}

#endif // LVGLAPI_LVGL_LINE_HPP
