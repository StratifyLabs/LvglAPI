#ifndef LVGLAPI_LVGL_BAR_HPP
#define LVGLAPI_LVGL_BAR_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Range {
public:
  Range() = default;
  Range(s16 minimum, s16 maximum) : m_minimum(minimum), m_maximum(maximum) {}

  static Range from_string(const var::StringView value) {
    // min is zero, string is expresse as <value>/<maximum>
    const auto tokens = value.split("/");
    return Range()
      .set_value(tokens.count() > 0 ? tokens.at(0).to_integer() : 0)
      .set_maximum(tokens.count() > 1 ? tokens.at(1).to_integer() : 100);
  }

private:
  API_AF(Range, s16, minimum, 0);
  API_AF(Range, s16, maximum, 100);
  API_AF(Range, s16, value, 0);
};

template <class Derived> class BarAccess : public ObjectAccess<Derived> {
public:
  BarAccess() = default;
  BarAccess(u32 type) : ObjectAccess<Derived>(type) {}
  BarAccess(const char *name) : ObjectAccess<Derived>(name) {}

  Derived &set_range(const Range &value) {
    Object::api()->bar_set_range(Object::object(), value.minimum(), value.maximum());
    return static_cast<Derived &>(*this);
  }

  Derived &set_start_value(s16 start_value, IsAnimate is_animate = IsAnimate::yes) {
    Object::api()->bar_set_start_value(
      Object::object(), start_value, lv_anim_enable_t(is_animate));
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

  Derived &set_value(const Range &value, IsAnimate is_animate = IsAnimate::yes) {
    const auto range = get_range();
    if (value.minimum() != range.minimum() || value.maximum() != range.maximum()) {
      set_range(value);
    }
    Object::api()->bar_set_value(
      Object::object(), value.value(), static_cast<lv_anim_enable_t>(is_animate));
    return static_cast<Derived &>(*this);
  }

  s16 get_value() const { return Object::api()->bar_get_value(Object::object()); }

};

class Bar : public BarAccess<Bar> {
public:
  explicit Bar(const char *name);

  static const lv_obj_class_t *get_class() { return api()->bar_class; }

  enum class Mode {
    normal = LV_BAR_MODE_NORMAL,
    symmetrical = LV_BAR_MODE_SYMMETRICAL,
    range = LV_BAR_MODE_RANGE
  };

  Bar &set_mode(Mode value) {
    api()->bar_set_mode(m_object, static_cast<lv_bar_mode_t>(value));
    return *this;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Bar(lv_obj_t *object) { m_object = object; }
};

} // namespace lvgl

namespace printer {
Printer &operator<<(Printer &printer, const lvgl::Range &range);
}

#endif // LVGLAPI_LVGL_BAR_HPP
