#ifndef LVGLAPI_LVGL_LINE_HPP
#define LVGLAPI_LVGL_LINE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Line : public ObjectAccess<Line> {
public:
  explicit Line(const char * name = "");
  explicit Line(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->line_class;
  }

};

}

#endif // LVGLAPI_LVGL_LINE_HPP
