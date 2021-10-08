#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class List : public ObjectAccess<List> {
public:
  explicit List(const char *name) : ObjectAccess(name) {}
  explicit List(const Context &context) : ObjectAccess(context.cast_as_name()) {}


  static const lv_obj_class_t * get_class(){
    return api()->list_class;
  }

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

  List &add_button(
    const Context &context,
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
    object->user_data = (void *)name;
    if (configure) {
      Button button(object);
      configure(button);
    }
    if (options.right_symbol()) {
      Button button(object);
      button.add(Label(right_symbol_name).configure([](Label &label) {
        label.set_width(size_from_content).set_alignment(Alignment::right_middle);
      }));
      button.find(right_symbol_name)
        .cast<Label>()
        ->set_text_static(options.right_symbol());
    }
    return *this;
  }

  List &set_right_symbol_static(const char *name, const char *value) {
    auto *label = find(name).find<IsAssertOnFail::no>(right_symbol_name).cast<Label>();
    if (label) {
      label->set_text_static(value);
    }
    return *this;
  }

  List &clear_right_symbols() {
    for (u32 i = 0; i < get_child_count(); i++) {
      auto *label =
        get_child(i).find<IsAssertOnFail::no>(right_symbol_name).cast<Label>();
      if (label) {
        label->set_text_static("");
      }
    }
    return *this;
  }

  List &set_right_symbol(const char *name, const char *value) {
    auto *label = find(name).find<IsAssertOnFail::no>(right_symbol_name).cast<Label>();
    if (label) {
      label->set_text(value);
    }
    return *this;
  }

  List &add_button(
    const Context &context,
    const ListButton &options,
    void (*configure)(Button &) = nullptr) {
    return add_button(context.cast_as_name(), options, configure);
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

  List &add_text(
    const Context &context,
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
  List(Object parent, const List &);
};

class CheckList : public ObjectAccess<CheckList> {
public:
  class Context : public Object::Context {
  public:
    explicit Context(const char *name) : Object::Context(name) {}

  private:
    API_AB(Context, allow_multiple, false);
    API_AF(Context, const char *, checked_symbol, LV_SYMBOL_OK);
    API_AF(Context, const char *, not_checked_symbol, "");
  };

  explicit CheckList(const Context &context) : ObjectAccess(context.cast_as_name()) {}

  static const lv_obj_class_t * get_class(){
    return api()->list_class;
  }

  static constexpr auto check_symbol_name = "CheckSymbol";

  CheckList &add_item(const char *name, const char *text) {
    auto object = api()->list_add_btn(m_object, "", text);
    object->user_data = (void *)name;
    auto button = Container(object).get<Button>();
    button.add_flag(Flags::event_bubble)
      .add(Label(check_symbol_name).configure([](Label &label) {
        label.set_width(size_from_content).set_alignment(Alignment::right_middle);
      }));
    button.find(check_symbol_name).cast<Label>()->set_text_static("");
    return *this;
  }

  CheckList &clear_all() {
    for (u32 i = 0; i < get_child_count(); i++) {
      auto object = get_child(i).find<IsAssertOnFail::no>(check_symbol_name);
      if (object.is_valid()) {
        object.cast<Label>()->set_text_static("");
      }
    }
    return *this;
  }

  CheckList &set_checked(const char *name, bool value = true) {
    auto object = find(name).find<IsAssertOnFail::no>(check_symbol_name);
    if (object.is_valid()) {
      auto *c = context<Context>();
      object.cast<Label>()->set_text_static(value ? c->checked_symbol() : c->not_checked_symbol());
    }
    return *this;
  }

  bool is_checked(const char *name) const {
    auto object = find(name).find<IsAssertOnFail::no>(check_symbol_name);
    if (object.is_valid()) {
      auto *c = context<Context>();
      return var::StringView(object.cast<Label>()->get_text()) == c->checked_symbol();
    }
    return false;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class DropDownList;
  explicit CheckList(lv_obj_t *object) { m_object = object; }
  CheckList(Object parent, const CheckList &);
};

class FormList : public ObjectAccess<FormList> {
public:
  class Context : public Object::Context {
  public:
    explicit Context(const char *name) : Object::Context(name) {}

  private:
    API_AB(Context, allow_multiple, false);
    API_AF(Context, const char *, checked_symbol, LV_SYMBOL_OK);
    API_AF(Context, const char *, not_checked_symbol, "");
  };

  explicit FormList(const Context &context) : ObjectAccess(context.cast_as_name()) {}

  static const lv_obj_class_t * get_class(){
    return api()->list_class;
  }

  static constexpr auto value_name = "FormValue";

  enum class ItemType {
    boolean,
    string,
    number,
    navigation
  };

  class ItemContext : public Object::Context {
  public:

    using Callback = void (*)(ItemContext * item_context, lv_event_t*);

    explicit ItemContext(const char *name) : Object::Context(name) {}

  private:
    API_AF(ItemContext, ItemType, type, ItemType::boolean);
    API_AC(ItemContext, var::KeyString, value);
    API_AF(ItemContext, Callback, edit_callback, nullptr);
  };

  FormList &add_item(const ItemContext & item_context);


private:
  OBJECT_ACCESS_FRIENDS();
  friend class DropDownList;
  explicit FormList(lv_obj_t *object) { m_object = object; }
  FormList(Object parent, const FormList &);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_LIST_HPP
