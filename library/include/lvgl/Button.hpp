#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Button : public ObjectAccess<Button> {
public:
  explicit Button(const char *name = "");

  static const lv_obj_class_t *get_class() { return api()->button_class; }


  Button & add_static_label(const char * text){
    return add(Label().set_text_static(text).center());
  }


private:
  OBJECT_ACCESS_FRIENDS();
  friend class List;
  friend class Window;
  friend class TabView;
  friend class MessageBox;
  Button(lv_obj_t *object) { m_object = object; }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
