#ifndef LVGLAPI_LVGL_ROLLER_HPP
#define LVGLAPI_LVGL_ROLLER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Roller : public ObjectAccess<Roller> {
public:
  enum class Mode { normal = LV_ROLLER_MODE_NORMAL, infinite = LV_ROLLER_MODE_INFINITE };

  explicit Roller(const char * name);

  static const lv_obj_class_t * get_class(){
    return api()->roller_class;
  }

  Roller &set_options(const char *options, Mode mode = Mode::normal) {
    api()->roller_set_options(object(), options, static_cast<lv_roller_mode_t>(mode));
    return *this;
  }

  Roller & set_selected(u16 select_option, IsAnimate is_animate = IsAnimate::yes){
    api()->roller_set_selected(m_object, select_option, static_cast<lv_anim_enable_t>(is_animate));
    return *this;
  }

  Roller & set_visible_row_count(u8 count){
    api()->roller_set_visible_row_count(object(), count);
    return *this;
  }

  template<class StringClass> StringClass get_selected() const {
    StringClass result;
    api()->roller_get_selected_str(object(), result.data(), result.capacity());
    return result;
  }

  const char * get_options() const {
    return api()->roller_get_options(object());
  }

  u16 get_option_count() const {
    return api()->roller_get_option_cnt(object());
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Roller(lv_obj_t * object){ m_object = object; }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_ROLLER_HPP
