#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "Object.hpp"

namespace lv {

class Canvas : public ObjectAccess<Canvas> {
public:
  Canvas(Object &parent) {
    m_object =
        lv_canvas_create(parent.object());
  }



};

} // namespace lv

#endif // LVGLAPI_LVGL_CANVAS_HPP
