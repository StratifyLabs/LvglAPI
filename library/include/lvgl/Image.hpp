#ifndef LVGLAPI_LVGL_IMAGE_HPP
#define LVGLAPI_LVGL_IMAGE_HPP

#include <var/StackString.hpp>
#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {

class Image : public ObjectAccess<Image> {
public:
  explicit Image(const char *name = "");
  explicit Image(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->image_class; }

  Image &set_source(const var::StringView src) {
    api()->img_set_src(m_object, var::PathString(src).cstring());
    return *this;
  }

  Image &set_source(const void *data_source) {
    api()->img_set_src(m_object, data_source);
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

  Image &set_zoom(float value) {
    api()->img_set_zoom(m_object, u16(value * 256.0f));
    return *this;
  }

  Image &set_antialias(bool value = true) {
    api()->img_set_antialias(m_object, value);
    return *this;
  }

  API_NO_DISCARD const void *get_source() const { return api()->img_get_src(m_object); }

  API_NO_DISCARD lv_coord_t get_offset_x() const {
    return api()->img_get_offset_x(m_object);
  }

  API_NO_DISCARD lv_coord_t get_offset_y() const {
    return api()->img_get_offset_y(m_object);
  }

  API_NO_DISCARD Point get_offset() const { return {get_offset_x(), get_offset_y()}; }

  API_NO_DISCARD u16 get_angle() const { return api()->img_get_angle(m_object); }

  API_NO_DISCARD Point get_pivot() const {
    Point result;
    api()->img_get_pivot(m_object, result.point());
    return result;
  }

  API_NO_DISCARD u16 get_zoom() const { return api()->img_get_zoom(m_object); }

  API_NO_DISCARD bool is_antialias() const { return api()->img_get_antialias(m_object); }

  class Info {
  public:
    /* Using Info() = default; causes problems with
     * the following code
     *
     * int function(){
     *   static const auto font_info = Font::Info();
     * }
     *
     * It causes a crash on ARM Cortex M7. The problem
     * is with the var::NameString member. It seems
     * it doesn't get moved correctly.
     *
     */

    Info() = default;
    ;
    explicit Info(const char *name, const lv_img_dsc_t *value)
      : m_name(name), m_image(value) {}

    API_NO_DISCARD bool is_valid() const { return m_image != nullptr; }
    API_NO_DISCARD lv_coord_t width() const { return m_image->header.w; }
    API_NO_DISCARD lv_coord_t height() const { return m_image->header.h; }
    API_NO_DISCARD const void *source() const { return m_image; }

  private:
    API_AF(Info, const char *, name, nullptr);
    API_AF(Info, const lv_img_dsc_t *, image, nullptr);
  };

  static Info find(const char *name, Size size);
  static Info find(const char *name) { return find(name, Size(0, 0)); }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_IMAGE_HPP
