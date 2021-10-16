#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class List : public ObjectAccess<List> {
public:
  explicit List(const char *name = "");

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  List &add_button(const char *symbol, const char *text) {
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, "");
    return *this;
  }

  List &add_button(
    const char *name,
    const char *symbol,
    const char *text,
    void (*configure)(Button &) = nullptr) {
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);

    if (configure) {
      Button button(object);
      configure(button);
    }
    return *this;
  }

  List &add_button(
    const UserData &context,
    const char *symbol,
    const char *text,
    void (*configure)(Button &) = nullptr) {
    return add_button(context.cast_as_name(), symbol, text, configure);
  }

  class ListButton {
    API_AF(ListButton, const char *, left_symbol, "");
    API_AF(ListButton, const char *, text, "");
    API_AF(ListButton, const char *, right_symbol, nullptr);
  };

  static constexpr auto right_symbol_name = "RightSymbol";

  List &add_button(
    const char *name,
    const ListButton &options,
    void (*configure)(Button &) = nullptr) {
    auto object = api()->list_add_btn(m_object, options.left_symbol(), options.text());
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);
    if (configure) {
      Button button(object);
      configure(button);
    }
    if (options.right_symbol()) {
      Button button(object);
      button.add_object(Label(right_symbol_name)
                          .set_width(size_from_content)
                          .set_alignment(Alignment::right_middle)
                          .set_text_static(options.right_symbol()));
    }
    return *this;
  }

  List &set_right_symbol_static(const char *name, const char *value) {
    auto label = find_within<Label, IsAssertOnFail::no>(name, right_symbol_name);
    printf("set right symbol %p\n", label.object());
    if (label.object()) {
      label.set_text_static(value);
    }
    return *this;
  }

  List &clear_right_symbols() {
    for (u32 i = 0; i < get_child_count(); i++) {
      auto label = get_child(i).find<Label, IsAssertOnFail::no>(right_symbol_name);
      if (label.object()) {
        label.set_text_static("");
      }
    }
    return *this;
  }

  List &set_right_symbol(const char *name, const char *value) {
    auto label = find_within<Label, IsAssertOnFail::no>(name, right_symbol_name);
    if (label.object()) {
      label.set_text(value);
    }
    return *this;
  }

  List &add_button(
    const UserData &context,
    const ListButton &options,
    void (*configure)(Button &) = nullptr) {
    return add_button(context.cast_as_name(), options, configure);
  }

  List &add_text(const char *text) {
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, "");
    return *this;
  }

  List &add_text(
    const char *name,
    const char *text,
    void (*configure)(Label &label) = nullptr) {
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);
    if (configure) {
      Label label(object);
      configure(label);
    }
    return *this;
  }

  List &add_text(
    const UserData &context,
    const char *text,
    void (*configure)(Label &label) = nullptr) {
    return add_text(context.cast_as_name(), text, configure);
  }

  const char *get_button_text(Object button) {
    return api()->list_get_btn_text(object(), button.object());
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class DropDownList;
  explicit List(lv_obj_t *object) { m_object = object; }
};

class CheckList : public ObjectAccess<CheckList> {
public:
  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name) : UserDataBase(name) {}

  private:
    API_AB(Data, allow_multiple, false);
    API_AF(Data, const char *, checked_symbol, LV_SYMBOL_OK);
    API_AF(Data, const char *, not_checked_symbol, "");
  };

  explicit CheckList(const Data &user_data);

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  static constexpr auto check_symbol_name = "CheckSymbol";

  CheckList &add_item(const char *name, const char *text) {
    auto object = api()->list_add_btn(m_object, "", text);
    set_user_data(object, name);
    auto button = Container(object).get<Button>();
    button.add_flag(Flags::event_bubble)
      .add_object(Label(check_symbol_name)
                    .set_width(size_from_content)
                    .set_alignment(Alignment::right_middle)
                    .set_text_static(""));
    return *this;
  }

  CheckList &clear_all() {
    for (u32 i = 0; i < get_child_count(); i++) {
      auto label = get_child(i).find<Label, IsAssertOnFail::no>(check_symbol_name);
      if (label.object()) {
        label.set_text_static("");
      }
    }
    return *this;
  }

  CheckList &set_checked(const char *name, bool value = true) {
    auto label = find_within<Label, IsAssertOnFail::no>(name, check_symbol_name);
    if (label.is_valid()) {
      auto *c = user_data<Data>();
      label.set_text_static(value ? c->checked_symbol() : c->not_checked_symbol());
    }
    return *this;
  }

  bool is_checked(const char *name) const {
    auto label = find_within<Label, IsAssertOnFail::no>(name, check_symbol_name);
    if (label.is_valid()) {
      auto *c = user_data<Data>();
      return var::StringView(label.get_text()) == c->checked_symbol();
    }
    return false;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class DropDownList;
  explicit CheckList(lv_obj_t *object) { m_object = object; }
};

class FormList : public ObjectAccess<FormList> {
public:
  class Data : public ::lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

  private:
    API_AB(Data, allow_multiple, false);
    API_AF(Data, const char *, checked_symbol, LV_SYMBOL_OK);
    API_AF(Data, const char *, not_checked_symbol, "");
  };

  explicit FormList(Data &user_data);

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  static constexpr auto value_name = "FormValue";

  enum class ItemType { boolean, string, number, navigation };

  class ItemData : public ::lvgl::UserDataAccess<ItemData> {
  public:
    using Callback = void (*)(lv_event_t *);
    explicit ItemData(const char *name) : UserDataBase(name) {}

  private:
    API_AF(ItemData, const char *, symbol, "");
    API_AF(ItemData, ItemType, type, ItemType::boolean);
    API_AC(ItemData, var::KeyString, value);
    API_AF(ItemData, Callback, clicked_callback, nullptr);
  };

  FormList &add_item(const ItemData &item_data);

private:
  OBJECT_ACCESS_FRIENDS();
  friend class DropDownList;
  explicit FormList(lv_obj_t *object) { m_object = object; }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_LIST_HPP
