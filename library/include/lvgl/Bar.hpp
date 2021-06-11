#ifndef LVGLAPI_LVGL_BAR_HPP
#define LVGLAPI_LVGL_BAR_HPP

#include "Object.hpp"

namespace lv {

class Range {
public:
  Range() = default;
  Range(s16 minimum, s16 maximum) : m_minimum(minimum), m_maximum(maximum) {}

private:
  API_AF(Range, s16, minimum, 1);
  API_AF(Range, s16, maximum, 100);
};

template <class Derived> class BarAccess : public ObjectAccess<Derived> {
public:
  Derived &set_range(const Range &value) {
    Object::api()->bar_set_range(Object::object(), value.minimum(), value.maximum());
    return static_cast<Derived &>(*this);
  }

  Derived &set_value(s16 value, IsAnimate is_animate = IsAnimate::yes) {
    Object::api()->bar_set_value(
      Object::object(), value, static_cast<lv_anim_enable_t>(is_animate));
    return static_cast<Derived &>(*this);
  }

  Range get_range() const {
    return Range()
      .set_minimum(Object::api()->bar_get_min_value(Object::object()))
      .set_maximum(Object::api()->bar_get_max_value(Object::object()));
  }

  s16 get_value() const { return Object::api()->bar_get_value(Object::object()); }
};

class Bar : public BarAccess<Bar> {
public:

  class Create : public CreateAccess<Create> {
    public:
      Create(const char * name) : CreateAccess(name){}
  };

  Bar(Object parent, const Create & options);

  enum class Mode {
    normal = LV_BAR_MODE_NORMAL,
    symmetrical = LV_BAR_MODE_SYMMETRICAL,
    range = LV_BAR_MODE_RANGE
  };

  Bar &set_mode(Mode value) {
    api()->bar_set_mode(m_object, static_cast<lv_bar_mode_t>(value));
    return *this;
  }
};

} // namespace lv

#endif // LVGLAPI_LVGL_BAR_HPP
