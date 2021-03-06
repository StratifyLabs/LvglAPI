#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "Button.hpp"
#include "ButtonMatrix.hpp"
#include "Label.hpp"

#if defined MessageBox
#undef MessageBox
#endif

namespace lvgl {

class MessageBox : public ObjectAccess<MessageBox> {
public:
  struct Construct {

    Construct &set_button_list(const char *list[]) {
      button_list = list;
      return *this;
    }

    // name is first
    API_PUBLIC_MEMBER(Construct, const char *, name, "");

    // alphabetical
    API_PUBLIC_BOOL(Construct, add_close_button, true);
    const char **button_list = nullptr;
    API_PUBLIC_BOOL(Construct, modal, false);
    API_PUBLIC_MEMBER(Construct, const char *, message, "");
    API_PUBLIC_MEMBER(Construct, const char *, title, "");
  };

  explicit MessageBox(const Construct &options);
  explicit MessageBox(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->message_box_class; }

  API_NO_DISCARD const char *get_active_button_text() const {
    return api()->msgbox_get_active_btn_text(m_object);
  }

  API_NO_DISCARD Label get_title() const { return Label(api()->msgbox_get_title(m_object)); }
  API_NO_DISCARD Label get_text() const { return Label(api()->msgbox_get_text(m_object)); }
  API_NO_DISCARD Button get_close_button() const {
    return Button(api()->msgbox_get_close_btn(m_object));
  }
  API_NO_DISCARD ButtonMatrix get_buttons() const {
    return ButtonMatrix(api()->msgbox_get_btns(m_object));
  }

  void close() { api()->msgbox_close(object()); }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
