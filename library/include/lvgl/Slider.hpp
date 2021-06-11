#ifndef LVGLAPI_LVGL_SLIDER_HPP
#define LVGLAPI_LVGL_SLIDER_HPP

#include "Bar.hpp"

namespace lv {

class Slider : public BarAccess<Slider> {
public:

  enum class Mode {
    normal = LV_SLIDER_MODE_NORMAL,
    symmetrical = LV_SLIDER_MODE_SYMMETRICAL,
    range = LV_SLIDER_MODE_RANGE
  };

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Slider(Object parent, const Create & options){
    m_object = lv_slider_create(parent.object());
    set_name(options.name());
  }

  Slider & set_mode(Mode value){
    lv_slider_set_mode(m_object, static_cast<lv_slider_mode_t>(value));
    return *this;
  }

  Slider & set_left_value(int16_t value, IsAnimate is_animate = IsAnimate::yes){
    lv_slider_set_left_value(m_object, value, static_cast<lv_anim_enable_t>(is_animate));
    return *this;
  }

  int16_t get_left_value() const {
    return lv_slider_get_left_value(m_object);
  }

};

}

#endif // LVGLAPI_LVGL_SLIDER_HPP
