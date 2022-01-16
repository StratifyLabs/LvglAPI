#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {


class Button : public ObjectAccess<Button> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Button);

  LVGL_OBJECT_ACCESS_GET_CLASS(button_class);

  Button & add_label_as_static(const char * text){
    return add(Label().set_text_as_static(text).center());
  }

  Button & add_label(const char * text){
    return add(Label().set_text(text).center());
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
