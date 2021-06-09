#ifndef LVGLAPI_LVGL_IMAGE_HPP
#define LVGLAPI_LVGL_IMAGE_HPP

#include <var/StackString.hpp>
#include <var/StringView.hpp>

#include "Object.hpp"

namespace lv {

class Image : public ObjectAccess<Image> {
public:
  Image(Object &parent);

  Image &set_source(const var::StringView src) {
    api()->img_set_src(m_object, var::PathString(src).cstring());
    return *this;
  }

  Image &set_offset_x(lv_coord_t value) {
    api()->img_set_offset_x(m_object, value);
    return *this;
  }

  Image &set_offset_y(lv_coord_t value) {
    api()->img_set_offset_y(m_object, value);
    return *this;
  }

  Image &set_offset(const Point &position) {
    return set_offset_x(position.x()).set_offset_y(position.y());
  }


  Image &set_angle(s16 value) {
    api()->img_set_angle(m_object, value);
    return *this;
  }

  Image &set_pivot(const Point &position) {
    api()->img_set_pivot(m_object, position.x(), position.y());
    return *this;
  }

  Image &set_zoom(u16 value) {
    api()->img_set_zoom(m_object, value);
    return *this;
  }

  Image &set_antialias(bool value = true) {
    api()->img_set_antialias(m_object, value);
    return *this;
  }

  const void * get_source() const {
    return api()->img_get_src(m_object);
  }

  lv_coord_t get_offset_x() const {
    return api()->img_get_offset_x(m_object);
  }

  lv_coord_t get_offset_y() const {
    return api()->img_get_offset_y(m_object);
  }

  Point get_offset() const {
    return Point(get_offset_x(), get_offset_y());
  }

  u16 get_angle() const {
    return api()->img_get_angle(m_object);
  }

  Point get_pivot() const {
    Point result;
    api()->img_get_pivot(m_object, result.point());
    return result;
  }

  u16 get_zoom() const {
    return api()->img_get_zoom(m_object);
  }

  bool is_antialias() const {
    return api()->img_get_antialias(m_object);
  }

};

} // namespace lv

#endif // LVGLAPI_LVGL_IMAGE_HPP
