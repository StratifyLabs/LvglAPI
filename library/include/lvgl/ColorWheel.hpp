#ifndef LVGLAPI_LVGL_COLORPICKER_HPP
#define LVGLAPI_LVGL_COLORPICKER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class ColorWheel : public ObjectAccess<ColorWheel> {
public:

  enum class IsKnobRecolor {
    no, yes
  };

  explicit ColorWheel(const char *name = "", IsKnobRecolor is_knob_recolor = IsKnobRecolor::yes);
  explicit ColorWheel(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->colorwheel_class; }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_COLORPICKER_HPP
