#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Button.hpp"
#include "Generic.hpp"
#include "Label.hpp"

namespace lvgl {


class List : public ObjectAccess<List> {
public:
  explicit List(const char *name = "");
  explicit List(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  List &add_button(const char *symbol, const char *text);

  List &add_button(
    const char *name,
    const char *symbol,
    const char *text,
    void (*setup)(Button) = nullptr);

  List &add_text(const char *text);

  List &add_text(
    const char *name,
    const char *text,
    void (*setup)(Label label) = nullptr);

  const char *get_button_text(Object button) {
    return api()->list_get_btn_text(object(), button.object());
  }


};


} // namespace lvgl

#endif // LVGLAPI_LVGL_LIST_HPP
