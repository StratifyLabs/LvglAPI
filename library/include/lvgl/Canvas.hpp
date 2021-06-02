#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "Object.hpp"

namespace lv {

class Canvas : public ObjectAccess<Canvas> {
public:
  Canvas(Object &parent, const Canvas *copy = nullptr) {
    m_object =
        lv_canvas_create(parent.object(), copy ? copy->object() : nullptr);
  }

  Canvas& set_pixel(const Point & point, lv_color_t color){
    lv_canvas_set_px(object(), point.x(), point.y(), color);
    return *this;
  }

  Canvas& draw_rectangle();
  Canvas& draw_text();
  Canvas& draw_image();
  Canvas& draw_line();
  Canvas& draw_polygon();
  Canvas& draw_arc();

};

} // namespace lv

#endif // LVGLAPI_LVGL_CANVAS_HPP
