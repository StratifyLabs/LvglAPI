#include "lvgl/List.hpp"
#include "lvgl/Event.hpp"

using namespace lvgl;

List::List(const char * name) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,name);
}

CheckList::CheckList(const Data &user_data) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,user_data.cast_as_name());
  get<CheckList>().add_event_callback(EventCode::clicked, [](lv_event_t *e) {
    const Event event(e);
    if (event.target().name() == event.current_target().name()) {
      return;
    }

    const char *button_name = event.target().name();
    auto checklist = event.current_target<CheckList>();
    auto *c = checklist.user_data<Data>();
    if (c->is_allow_multiple() == false) {
      checklist.clear_all();
      checklist.set_checked(button_name);
    } else {
      // toggle the item that was pressed
      const auto is_checked = checklist.is_checked(button_name);
      checklist.set_checked(button_name, !is_checked);
    }
  });
}

FormList::FormList(Data& data) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,data.cast_as_name());
}

FormList &FormList::add_item(const ItemData &item_data) {
  auto object = api()->list_add_btn(m_object, item_data.symbol(), item_data.name());
  set_user_data(object, item_data.cast_as_name());
  auto button = Container(object).get<Button>();

  button.add_flag(Flags::event_bubble)
    .add_event_callback(
      EventCode::clicked,
      [](lv_event_t *e) {
        const Event event(e);
        auto *c = event.target().user_data<ItemData>();
        auto button = event.target<Button>();
        auto label = button.find<Label>(value_name);
        if (c->type() == ItemType::boolean) {
          if (var::StringView(label.get_text()).is_empty()) {
            label.set_text_static(LV_SYMBOL_OK);
          } else {
            label.set_text_static("");
          }
        } else {
          if (c->clicked_callback()) {
            c->clicked_callback()(e);
          }
          if (c->type() != ItemType::navigation) {
            label.set_text_static(c->value());
          }
        }
      })
    .add_object(Label(value_name)
                  .set_width(size_from_content)
                  .set_alignment(Alignment::right_middle));

  auto *c = button.user_data<ItemData>();
  button.find<Label>(value_name)
    .set_text_static(
      (c->type() == ItemType::navigation) ? LV_SYMBOL_RIGHT : c->value().cstring());
  return *this;
}
