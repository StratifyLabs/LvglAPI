#ifndef LVGLAPI_LVGL_BAR_HPP
#define LVGLAPI_LVGL_BAR_HPP

#include "Object.hpp"

namespace lv {

template <class Derived> class BarAccess : public ObjectAccess<Derived> {
public:
  class Range {
    API_AF(Range, s16, minimum, 1);
    API_AF(Range, s16, maximum, 100);
  };

  Derived &set_range(const Range &value) {
    lv_bar_set_range(Object::object(), value.minimum(), value.maximum());
    return static_cast<Derived &>(*this);
  }

  Derived &set_value(s16 value, IsAnimate is_animate = IsAnimate::yes) {
    lv_bar_set_value(Object::object(), value,
                     static_cast<lv_anim_enable_t>(is_animate));
    return *this;
  }

  Range get_range() const {
    Range()
        .set_minimum(lv_bar_get_min_value(Object::object()))
        .set_maximum(lv_bar_get_max_value(Object::object()));
  }

  s16 get_value() const { return lv_bar_get_value(Object::object()); }
};

class Bar : public BarAccess<Bar> {
public:
  Bar();

  enum class Mode {
    normal = LV_BAR_MODE_NORMAL,
    symmetrical = LV_BAR_MODE_SYMMETRICAL,
    range = LV_BAR_MODE_RANGE
  };

  Bar &set_mode(Mode value) {
    lv_bar_set_mode(m_object, static_cast<lv_bar_mode_t>(value));
    return *this;
  }

};

} // namespace lv

#endif // LVGLAPI_LVGL_BAR_HPP
