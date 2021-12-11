#include "lvgl/List.hpp"
#include "lvgl/Event.hpp"

using namespace lvgl;

List::List(const char *name) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object, name);
}

List &List::add_button(
  const char *name,
  const char *symbol,
  const char *text,
  void (*setup)(Button)) {
  auto object = api()->list_add_btn(m_object, symbol, text);
  api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
  set_user_data(object, name);

  if (setup) {
    Button button(object);
    setup(button);
  }
  return *this;
}

List &List::add_button(const char *symbol, const char *text) {
  return add_button("", symbol, text, nullptr);
}

List &List::add_text(const char *name, const char *text, void (*setup)(Label)) {
  auto object = api()->list_add_text(m_object, text);
  api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
  set_user_data(object, name);
  if (setup) {
    Label label(object);
    setup(label);
  }
  return *this;
}

List &List::add_text(const char *text) { return add_text("", text, nullptr); }
