#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class MessageBox : public ObjectAccess<MessageBox> {
public:
  class Construct {
  public:

    Construct &set_button_list(const char *list[]) {
      m_button_list = list;
      return *this;
    }

  private:
    friend MessageBox;
    API_AF(Construct, const char *, title, "");
    API_AF(Construct, const char *, message, "");
    API_AB(Construct, add_close_button, true);
    API_AB(Construct, modal, false);

    const char **m_button_list = nullptr;
  };

  explicit MessageBox(const char *name, const Construct &options)
    : ObjectAccess(name), m_construct(&options) {}
  explicit MessageBox(const UserData &context, const Construct &options)
    : ObjectAccess(context.cast_as_name()), m_construct(&options) {}

  static const lv_obj_class_t *get_class() { return api()->message_box_class; }

  const char *get_active_button_text() const {
    return api()->msgbox_get_active_btn_text(m_object);
  }

  Label get_text() const { return Label(api()->msgbox_get_text(m_object)); }

  void close() { api()->msgbox_close(object()); }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit MessageBox(lv_obj_t *object) { m_object = object; }
  MessageBox(Object parent, const MessageBox &options);

  const Construct *m_construct = nullptr;

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
