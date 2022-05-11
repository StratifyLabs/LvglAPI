#include "lvgl/List.hpp"
#include "lvgl/Event.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(List);


List::List(const char *name) {
  construct_list(name);
}

List &List::add_button(
  const char *name,
  const char *symbol,
  const char *text,
  void (*setup)(Button)) {

  if( symbol != nullptr ) {
    API_ASSERT(!var::StringView(symbol).is_empty());
  }

  auto object = api()->list_add_btn(m_object, symbol, text);
  api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
  set_user_data(object, name);

  auto button = Button(object);
  if (setup) {
    setup(button);
  }

  for (u32 i = 0; i < get_child_count(); i++) {
    get_child(i).get<Generic>().set_border_side(BorderSide::bottom);
  }

  // last item has no border
  button.set_border_side(BorderSide::none);

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
