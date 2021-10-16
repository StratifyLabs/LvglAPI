#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "Label.hpp"
#include "Button.hpp"
#include "ButtonMatrix.hpp"

namespace lvgl {


class MessageBox : public ObjectAccess<MessageBox> {
public:
  struct Construct {

    Construct &set_button_list(const char *list[]) {
      button_list = list;
      return *this;
    }

    API_PUBLIC_MEMBER(Construct, const char *, name, "");
    API_PUBLIC_MEMBER(Construct, const char *, title, "");
    API_PUBLIC_MEMBER(Construct, const char *, message, "");
    API_PUBLIC_BOOL(Construct, add_close_button, true);
    API_PUBLIC_BOOL(Construct, modal, false);

    const char **button_list = nullptr;
  };

  MessageBox(const Construct &options);
  explicit MessageBox(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->message_box_class; }

  const char *get_active_button_text() const {
    return api()->msgbox_get_active_btn_text(m_object);
  }

  Label get_title() const { return Label(api()->msgbox_get_title(m_object)); }
  Label get_text() const { return Label(api()->msgbox_get_text(m_object)); }
  Button get_close_button() const  { return Button(api()->msgbox_get_close_btn(m_object)); }
  ButtonMatrix get_buttons() const {return ButtonMatrix(api()->msgbox_get_btns(m_object)); }

  void close() { api()->msgbox_close(object()); }


};

} // namespace lvgl

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
