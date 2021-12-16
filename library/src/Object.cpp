#include <var/StackString.hpp>

#include "lvgl/Event.hpp"
#include "lvgl/Object.hpp"
#include "lvgl/Theme.hpp"

lvgl::LvglApi lvgl::Api::m_api;

using namespace lvgl;

void Object::construct_object(const char *name) {
  m_object = api()->obj_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_label(const char *name) {
  m_object = api()->label_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_line(const char *name) {
  m_object = api()->line_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_button(const char *name) {
  m_object = api()->btn_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_list(const char *name) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_dropdown(const char *name) {
  m_object = api()->dropdown_create(screen_object());
  set_user_data(m_object, name);
}

Object Object::find_object_worker(const char *name) const {
  // recursively find the child
  if (!is_valid()) {
    return Object();
  }
  auto get = find_child(name);
  if (get.object() != nullptr) {
    return get;
  }
  const auto count = get_child_count();
  for (u32 i = 0; i < count; i++) {
    const auto child = get_child(i);
    auto result = child.find_object<IsAssertOnFail::no>(name);
    if (result.m_object != nullptr) {
      return result;
    }
  }
  return Object();
}

Object Object::find_child(const char *name) const {
  const auto count = get_child_count();
  for (u32 i = 0; i < count; i++) {
    auto child = get_child(i);
    if (is_name_matched(child, name)) {
      return child;
    }
  }
  return {};
}

Object Object::find_parent_by_name(const char *name) const {
  auto current = get_parent();
  while (current.object()) {
    if (current.name() == name) {
      return current;
    }
    current = current.get_parent();
  }
  return Object();
}

void Object::find_names_add_state(const var::StringViewList &name_list, State state) {
  for (const auto &name : name_list) {
    auto *object = find<Object, IsAssertOnFail::no>(var::KeyString(name).cstring()).object();
    if (object) {
      api()->obj_add_state(object, lv_state_t(state));
    }
  }
}

void Object::find_names_clear_state(const var::StringViewList &name_list, State state) {
  for (const auto &name : name_list) {
    auto *object = find<Object, IsAssertOnFail::no>(var::KeyString(name).cstring()).object();
    if (object) {
      api()->obj_clear_state(object, lv_state_t(state));
    }
  }
}

void Object::add_style_from_theme(var::StringView name, Selector selector) {
  const auto theme = Theme::get_theme(*this);
  const auto item_list = name.split(" ");
  for (const auto &item : item_list) {
    const auto *style = theme.find(item);
    if (style) {
      api()->obj_add_style(m_object, (lv_style_t *)style, selector.value());
    }
  }
}

void Object::set_user_data(lv_obj_t *obj, const char *name) {
  API_ASSERT(obj != nullptr);
  if (obj->user_data == nullptr) {
    obj->user_data = (void *)name;
    if (auto *user_data = UserData::get_user_data(obj->user_data);
        user_data && user_data->needs_free()) {
      api()->obj_add_event_cb(obj, delete_user_data, LV_EVENT_DELETE, nullptr);
    }
  }
}

void Object::delete_user_data(lv_event_t *e) {
  if (auto *value = UserData::get_user_data(e->target->user_data); value) {
    delete value;
  }
}

bool Object::is_name_matched(const Object &child, const char *name) {
  const auto child_name = child.name();
  if (
    (child_name != nullptr)
    && ((child_name == name) || (var::StringView(child.name()) == name))) {
    return true;
  }
  return false;
}

lv_coord_t Object::get_local_style_as_coord(Property property, Selector selector) const {
  lv_style_value_t value;
  api()->obj_get_local_style_prop(
    m_object, lv_style_prop_t(property), &value, selector.value());
  return lv_coord_t(value.num);
}

Color Object::get_local_style_as_color(Property property, Selector selector) const {
  lv_style_value_t value;
  api()->obj_get_local_style_prop(
    m_object, lv_style_prop_t(property), &value, selector.value());
  return Color{value.color};
}

#define CLASS_TYPE_CASE(x, y)                                                            \
  if (class_value == api()->y##_class) {                                                 \
    return x::y;                                                                         \
  }

ClassType Object::get_class_type() const {
  const auto *class_value = api()->obj_get_class(m_object);
  // CLASS_TYPE_CASE(ClassType, animation_image);
  CLASS_TYPE_CASE(ClassType, calendar);
  CLASS_TYPE_CASE(ClassType, calendar_header_arrow);
  CLASS_TYPE_CASE(ClassType, calendar_header_dropdown);
  CLASS_TYPE_CASE(ClassType, chart);
  CLASS_TYPE_CASE(ClassType, colorwheel);
  CLASS_TYPE_CASE(ClassType, dropdown);
  CLASS_TYPE_CASE(ClassType, image_button);
  CLASS_TYPE_CASE(ClassType, keyboard);
  CLASS_TYPE_CASE(ClassType, led);
  CLASS_TYPE_CASE(ClassType, list);
  CLASS_TYPE_CASE(ClassType, list_text);
  CLASS_TYPE_CASE(ClassType, list_button);
  CLASS_TYPE_CASE(ClassType, meter);
  CLASS_TYPE_CASE(ClassType, spangroup);
  CLASS_TYPE_CASE(ClassType, spinbox);
  CLASS_TYPE_CASE(ClassType, spinner);
  CLASS_TYPE_CASE(ClassType, tabview);
  CLASS_TYPE_CASE(ClassType, tileview);
  CLASS_TYPE_CASE(ClassType, tileview_tile);
  CLASS_TYPE_CASE(ClassType, window);
  CLASS_TYPE_CASE(ClassType, arc);
  CLASS_TYPE_CASE(ClassType, bar);
  CLASS_TYPE_CASE(ClassType, button);
  CLASS_TYPE_CASE(ClassType, button_matrix);
  CLASS_TYPE_CASE(ClassType, canvas);
  CLASS_TYPE_CASE(ClassType, checkbox);
  CLASS_TYPE_CASE(ClassType, image);
  CLASS_TYPE_CASE(ClassType, line);
  CLASS_TYPE_CASE(ClassType, label);
  CLASS_TYPE_CASE(ClassType, message_box);
  CLASS_TYPE_CASE(ClassType, roller);
  CLASS_TYPE_CASE(ClassType, slider);
  // CLASS_TYPE_CASE(ClassType, switch_);
  if (class_value == api()->switch_class) {
    return ClassType::switch_;
  }
  CLASS_TYPE_CASE(ClassType, table);
  CLASS_TYPE_CASE(ClassType, textarea);
  return ClassType::object;
}

#define PROPERTY_CASE(x, y)                                                              \
  case x::y:                                                                             \
    return MCU_STRINGIFY(y)

#define PROPERTY_STRING_CASE(x, y)                                                       \
  if (value_stringview == MCU_STRINGIFY(x)) {                                            \
    return x::y;                                                                         \
  }

const char *Object::to_cstring(ClassType value) {
  switch (value) {
    PROPERTY_CASE(ClassType, object);
    PROPERTY_CASE(ClassType, animation_image);
    PROPERTY_CASE(ClassType, calendar);
    PROPERTY_CASE(ClassType, calendar_header_arrow);
    PROPERTY_CASE(ClassType, calendar_header_dropdown);
    PROPERTY_CASE(ClassType, chart);
    PROPERTY_CASE(ClassType, colorwheel);
    PROPERTY_CASE(ClassType, dropdown);
    PROPERTY_CASE(ClassType, image_button);
    PROPERTY_CASE(ClassType, keyboard);
    PROPERTY_CASE(ClassType, led);
    PROPERTY_CASE(ClassType, list);
    PROPERTY_CASE(ClassType, list_text);
    PROPERTY_CASE(ClassType, list_button);
    PROPERTY_CASE(ClassType, meter);
    PROPERTY_CASE(ClassType, spangroup);
    PROPERTY_CASE(ClassType, spinbox);
    PROPERTY_CASE(ClassType, spinner);
    PROPERTY_CASE(ClassType, tabview);
    PROPERTY_CASE(ClassType, tileview);
    PROPERTY_CASE(ClassType, tileview_tile);
    PROPERTY_CASE(ClassType, window);
    PROPERTY_CASE(ClassType, arc);
    PROPERTY_CASE(ClassType, bar);
    PROPERTY_CASE(ClassType, button);
    PROPERTY_CASE(ClassType, button_matrix);
    PROPERTY_CASE(ClassType, canvas);
    PROPERTY_CASE(ClassType, checkbox);
    PROPERTY_CASE(ClassType, image);
    PROPERTY_CASE(ClassType, line);
    PROPERTY_CASE(ClassType, label);
    PROPERTY_CASE(ClassType, message_box);
    PROPERTY_CASE(ClassType, roller);
    PROPERTY_CASE(ClassType, slider);
    PROPERTY_CASE(ClassType, switch_);
    PROPERTY_CASE(ClassType, table);
    PROPERTY_CASE(ClassType, textarea);
  }
  return "unknown";
}

ClassType Object::class_type_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(ClassType, animation_image);
  PROPERTY_STRING_CASE(ClassType, calendar);
  PROPERTY_STRING_CASE(ClassType, calendar_header_arrow);
  PROPERTY_STRING_CASE(ClassType, calendar_header_dropdown);
  PROPERTY_STRING_CASE(ClassType, chart);
  PROPERTY_STRING_CASE(ClassType, colorwheel);
  PROPERTY_STRING_CASE(ClassType, dropdown);
  PROPERTY_STRING_CASE(ClassType, image_button);
  PROPERTY_STRING_CASE(ClassType, keyboard);
  PROPERTY_STRING_CASE(ClassType, led);
  PROPERTY_STRING_CASE(ClassType, list);
  PROPERTY_STRING_CASE(ClassType, list_text);
  PROPERTY_STRING_CASE(ClassType, list_button);
  PROPERTY_STRING_CASE(ClassType, meter);
  PROPERTY_STRING_CASE(ClassType, spangroup);
  PROPERTY_STRING_CASE(ClassType, spinbox);
  PROPERTY_STRING_CASE(ClassType, spinner);
  PROPERTY_STRING_CASE(ClassType, tabview);
  PROPERTY_STRING_CASE(ClassType, tileview);
  PROPERTY_STRING_CASE(ClassType, tileview_tile);
  PROPERTY_STRING_CASE(ClassType, window);
  PROPERTY_STRING_CASE(ClassType, arc);
  PROPERTY_STRING_CASE(ClassType, bar);
  PROPERTY_STRING_CASE(ClassType, button);
  PROPERTY_STRING_CASE(ClassType, button_matrix);
  PROPERTY_STRING_CASE(ClassType, canvas);
  PROPERTY_STRING_CASE(ClassType, checkbox);
  PROPERTY_STRING_CASE(ClassType, image);
  PROPERTY_STRING_CASE(ClassType, line);
  PROPERTY_STRING_CASE(ClassType, label);
  PROPERTY_STRING_CASE(ClassType, message_box);
  PROPERTY_STRING_CASE(ClassType, roller);
  PROPERTY_STRING_CASE(ClassType, slider);
  PROPERTY_STRING_CASE(ClassType, switch_);
  PROPERTY_STRING_CASE(ClassType, table);
  PROPERTY_STRING_CASE(ClassType, textarea);
  return ClassType::object;
}
