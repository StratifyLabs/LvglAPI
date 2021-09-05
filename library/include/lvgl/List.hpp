#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Button.hpp"
#include "Label.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class List : public ObjectAccess<List> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}
  };

  explicit List(const char * name) : ObjectAccess(name){}

  List &add_button(const char *symbol, const char *text) {
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = nullptr;
    return *this;
  }


  List &add_button(
    const char *name,
    const char *symbol,
    const char *text,
    void (*configure)(Button &) = nullptr) {
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void *)name;
    if (configure) {
      Button button(object);
      configure(button);
    }
    return *this;
  }

  List &add_text(const char *text) {
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = nullptr;
    return *this;
  }

  List &add_text(
    const char *name,
    const char *text,
    void (*configure)(Label &label) = nullptr) {
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void *)name;
    if (configure) {
      Label label(object);
      configure(label);
    }
    return *this;
  }

  const char *get_button_text(Object button) {
    return api()->list_get_btn_text(object(), button.object());
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit List(lv_obj_t * object){ m_object = object; }
  List(Object parent, const List &);
  List(Object parent, const Create &options);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_LIST_HPP
