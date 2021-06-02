#ifndef LVGLAPI_LVGL_SLIDER_HPP
#define LVGLAPI_LVGL_SLIDER_HPP

#include "Bar.hpp"

namespace lv {

class Slider : public BarAccess<Slider> {
public:

  class Part {
  public:
    static auto constexpr background = lv::Part(LV_SLIDER_PART_BG);
    static auto constexpr indicator = lv::Part(LV_SLIDER_PART_INDIC);
    static auto constexpr knob = lv::Part(LV_SLIDER_PART_KNOB);
  };

  enum class Type {
    normal = LV_SLIDER_TYPE_NORMAL,
    symmetrical = LV_SLIDER_TYPE_SYMMETRICAL,
    range = LV_SLIDER_TYPE_RANGE
  };


  Slider();
  Slider(Object & parent, const Slider * copy = nullptr){
    m_object = lv_slider_create(parent.object(), copy ? copy->object() : nullptr);
  }

  Slider & set_type(Type value){
    lv_slider_set_type(m_object, static_cast<lv_slider_type_t>(value));
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
