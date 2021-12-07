#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Button.hpp"
#include "Generic.hpp"
#include "Label.hpp"

namespace lvgl {

class Window : public ObjectAccess<Window> {
public:
  explicit Window(const char *name = "", lv_coord_t header_height = 15_percent);
  explicit Window(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }

  Window &add_button(
    const char *name,
    const void *icon,
    lv_coord_t width,
    void (*setup)(Button) = nullptr) {
    auto object = api()->win_add_btn(m_object, icon, width);
    set_user_data(object, name);
    Button button(object);
    button.add_flag(Flags::event_bubble);
    if (setup) {
      setup(button);
    }
    return *this;
  }

  Window &add_title(const char *name, const char *text, void (*setup)(Label) = nullptr) {
    auto object = api()->win_add_title(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);
    if (setup) {
      setup(Label(object));
    }
    return *this;
  }

  API_NO_DISCARD Generic get_header() const {
    return Generic(api()->win_get_header(m_object));
  }
  API_NO_DISCARD Generic get_content() const {
    return Generic(api()->win_get_content(m_object));
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_WINDOW_HPP
