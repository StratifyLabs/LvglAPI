#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {


class Button : public ObjectAccess<Button> {
public:
  explicit Button(const char *name = "");
  Button(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->button_class; }

  Button & add_static_label(const char * text){
    return add(Label().set_text_static(text).center());
  }

  Button & add_label(const char * text){
    return add(Label().set_text(text).center());
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
