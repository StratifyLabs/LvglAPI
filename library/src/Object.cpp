#include <var/StackString.hpp>

#include "lvgl/Event.hpp"
#include "lvgl/Object.hpp"
#include "lvgl/Theme.hpp"

#include "lvgl/macros.hpp"

lvgl::LvglApi lvgl::Api::m_api;

using namespace lvgl;
using namespace var;

void Object::construct_object(const char *name) {
  m_object = api()->obj_create(screen_object());
  set_user_data(m_object, name);
}

void Object::construct_canvas(const char *name) {
  m_object = api()->canvas_create(screen_object());
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

void Object::construct_switch(const char *name) {
  m_object = api()->switch_create(screen_object());
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
    if( StringView(current.name()) == name ){
      return current;
    }
    current = current.get_parent();
  }
  return Object();
}

Object Object::find_parent_by_partial_name(var::StringView name) const {
  auto current = get_parent();
  while (current.object()) {
    if( StringView(current.name()).find(name) != StringView::npos ){
      return current;
    }
    current = current.get_parent();
  }
  return Object();
}


void Object::find_names_add_state(const var::StringViewList &name_list, State state) {
  for (const auto &name : name_list) {
    auto *object =
      find<Object, IsAssertOnFail::no>(var::KeyString(name).cstring()).object();
    if (object) {
      api()->obj_add_state(object, lv_state_t(state));
    }
  }
}

void Object::find_names_clear_state(const var::StringViewList &name_list, State state) {
  for (const auto &name : name_list) {
    auto *object =
      find<Object, IsAssertOnFail::no>(var::KeyString(name).cstring()).object();
    if (object) {
      api()->obj_clear_state(object, lv_state_t(state));
    }
  }
}

void Object::add_style_from_theme(var::StringView name, Selector selector) {
  const auto theme = Theme::get_theme(*this);
  const auto item_list = name.split(" ");
  for (const auto &item : item_list) {
    const auto *style = theme.find_style(item);
    if (style) {
      api()->obj_add_style(m_object, (lv_style_t *)style, selector.value());
    }
  }
}

void Object::set_user_data(lv_obj_t *obj, const char *name) {
  API_ASSERT(obj != nullptr);
  if (obj->user_data == nullptr) {
    obj->user_data = (void *)name;
    if (auto *user_data = UserData::get_user_data_derived<UserData>(obj->user_data); user_data) {
      user_data->m_associated_object = obj;
      if (user_data->m_deleter) {
        api()->obj_add_event_cb(obj, delete_user_data, LV_EVENT_DELETE, nullptr);
      }
    }
  }
}

void Object::delete_user_data(lv_event_t *e) {
  if (auto *value = UserData::get_user_data_derived<UserData>(e->target->user_data); value) {
    value->m_deleter(value);
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

const char *Object::to_cstring(ClassType value) {
  switch (value) {
    LVGL_PROPERTY_CASE(ClassType, object);
    LVGL_PROPERTY_CASE(ClassType, animation_image);
    LVGL_PROPERTY_CASE(ClassType, calendar);
    LVGL_PROPERTY_CASE(ClassType, calendar_header_arrow);
    LVGL_PROPERTY_CASE(ClassType, calendar_header_dropdown);
    LVGL_PROPERTY_CASE(ClassType, chart);
    LVGL_PROPERTY_CASE(ClassType, colorwheel);
    LVGL_PROPERTY_CASE(ClassType, dropdown);
    LVGL_PROPERTY_CASE(ClassType, image_button);
    LVGL_PROPERTY_CASE(ClassType, keyboard);
    LVGL_PROPERTY_CASE(ClassType, led);
    LVGL_PROPERTY_CASE(ClassType, list);
    LVGL_PROPERTY_CASE(ClassType, list_text);
    LVGL_PROPERTY_CASE(ClassType, list_button);
    LVGL_PROPERTY_CASE(ClassType, meter);
    LVGL_PROPERTY_CASE(ClassType, spangroup);
    LVGL_PROPERTY_CASE(ClassType, spinbox);
    LVGL_PROPERTY_CASE(ClassType, spinner);
    LVGL_PROPERTY_CASE(ClassType, tabview);
    LVGL_PROPERTY_CASE(ClassType, tileview);
    LVGL_PROPERTY_CASE(ClassType, tileview_tile);
    LVGL_PROPERTY_CASE(ClassType, window);
    LVGL_PROPERTY_CASE(ClassType, arc);
    LVGL_PROPERTY_CASE(ClassType, bar);
    LVGL_PROPERTY_CASE(ClassType, button);
    LVGL_PROPERTY_CASE(ClassType, button_matrix);
    LVGL_PROPERTY_CASE(ClassType, canvas);
    LVGL_PROPERTY_CASE(ClassType, checkbox);
    LVGL_PROPERTY_CASE(ClassType, image);
    LVGL_PROPERTY_CASE(ClassType, line);
    LVGL_PROPERTY_CASE(ClassType, label);
    LVGL_PROPERTY_CASE(ClassType, message_box);
    LVGL_PROPERTY_CASE(ClassType, roller);
    LVGL_PROPERTY_CASE(ClassType, slider);
    LVGL_PROPERTY_CASE(ClassType, switch_);
    LVGL_PROPERTY_CASE(ClassType, table);
    LVGL_PROPERTY_CASE(ClassType, textarea);
  }
  return "unknown";
}

ClassType Object::class_type_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(ClassType, animation_image);
  LVGL_PROPERTY_STRING_CASE(ClassType, calendar);
  LVGL_PROPERTY_STRING_CASE(ClassType, calendar_header_arrow);
  LVGL_PROPERTY_STRING_CASE(ClassType, calendar_header_dropdown);
  LVGL_PROPERTY_STRING_CASE(ClassType, chart);
  LVGL_PROPERTY_STRING_CASE(ClassType, colorwheel);
  LVGL_PROPERTY_STRING_CASE(ClassType, dropdown);
  LVGL_PROPERTY_STRING_CASE(ClassType, image_button);
  LVGL_PROPERTY_STRING_CASE(ClassType, keyboard);
  LVGL_PROPERTY_STRING_CASE(ClassType, led);
  LVGL_PROPERTY_STRING_CASE(ClassType, list);
  LVGL_PROPERTY_STRING_CASE(ClassType, list_text);
  LVGL_PROPERTY_STRING_CASE(ClassType, list_button);
  LVGL_PROPERTY_STRING_CASE(ClassType, meter);
  LVGL_PROPERTY_STRING_CASE(ClassType, spangroup);
  LVGL_PROPERTY_STRING_CASE(ClassType, spinbox);
  LVGL_PROPERTY_STRING_CASE(ClassType, spinner);
  LVGL_PROPERTY_STRING_CASE(ClassType, tabview);
  LVGL_PROPERTY_STRING_CASE(ClassType, tileview);
  LVGL_PROPERTY_STRING_CASE(ClassType, tileview_tile);
  LVGL_PROPERTY_STRING_CASE(ClassType, window);
  LVGL_PROPERTY_STRING_CASE(ClassType, arc);
  LVGL_PROPERTY_STRING_CASE(ClassType, bar);
  LVGL_PROPERTY_STRING_CASE(ClassType, button);
  LVGL_PROPERTY_STRING_CASE(ClassType, button_matrix);
  LVGL_PROPERTY_STRING_CASE(ClassType, canvas);
  LVGL_PROPERTY_STRING_CASE(ClassType, checkbox);
  LVGL_PROPERTY_STRING_CASE(ClassType, image);
  LVGL_PROPERTY_STRING_CASE(ClassType, line);
  LVGL_PROPERTY_STRING_CASE(ClassType, label);
  LVGL_PROPERTY_STRING_CASE(ClassType, message_box);
  LVGL_PROPERTY_STRING_CASE(ClassType, roller);
  LVGL_PROPERTY_STRING_CASE(ClassType, slider);
  LVGL_PROPERTY_STRING_CASE(ClassType, switch_);
  LVGL_PROPERTY_STRING_CASE(ClassType, table);
  LVGL_PROPERTY_STRING_CASE(ClassType, textarea);
  return ClassType::object;
}

u32 Object::get_child_count() const { return api()->obj_get_child_cnt(m_object); }

u32 Object::get_index() const { return api()->obj_get_index(m_object); }

PropertyValue Object::get_property_value(Property property, Selector selector) {
  PropertyValue result;
  api()->obj_get_local_style_prop(
    m_object, lv_style_prop_t(property), &result.m_value, selector.value());
  return result;
}

lv_coord_t Object::get_bottom_padding(Selector selector) const {
  return get_local_style_as_coord(Property::bottom_padding, selector);
}

lv_coord_t Object::get_top_padding(Selector selector) const {
  return get_local_style_as_coord(Property::top_padding, selector);
}
lv_coord_t Object::get_right_padding(Selector selector) const {
  return get_local_style_as_coord(Property::right_padding, selector);
}
lv_coord_t Object::get_left_padding(Selector selector) const {
  return get_local_style_as_coord(Property::left_padding, selector);
}
Point Object::get_scroll_end() const {
  Point result;
  api()->obj_get_scroll_end(m_object, result.point());
  return result;
}
lv_coord_t Object::get_scroll_right() const {
  return api()->obj_get_scroll_right(m_object);
}
lv_coord_t Object::get_scroll_left() const {
  return api()->obj_get_scroll_left(m_object);
}
lv_coord_t Object::get_scroll_bottom() const {
  return api()->obj_get_scroll_bottom(m_object);
}
lv_coord_t Object::get_scroll_top() const {
  return api()->obj_get_scroll_top(m_object);
}
lv_coord_t Object::get_scroll_y() const {
  return api()->obj_get_scroll_y(m_object);
}
lv_coord_t Object::get_scroll_x() const {
  return api()->obj_get_scroll_x(m_object);
}
ScrollSnap Object::get_scroll_snap_y() const {
  return ScrollSnap(api()->obj_get_scroll_snap_y(m_object));
}
ScrollSnap Object::get_scroll_snap_x() const {
  return ScrollSnap(api()->obj_get_scroll_snap_x(m_object));
}
Direction Object::get_scroll_direction() const {
  return Direction(api()->obj_get_scroll_dir(m_object));
}
ScrollBarMode Object::get_scrollbar_mode() const {
  return ScrollBarMode(api()->obj_get_scrollbar_mode(m_object));
}
bool Object::is_visible() const { return api()->obj_is_visible(m_object); }
bool Object::is_visible(Area &area) const {
  return api()->obj_area_is_visible(m_object, area.area());
}
lv_coord_t Object::get_content_height() const {
  return api()->obj_get_content_height(m_object);
}
lv_coord_t Object::get_content_width() const {
  return api()->obj_get_content_width(m_object);
}
lv_coord_t Object::get_self_height() const {
  return api()->obj_get_self_height(m_object);
}
lv_coord_t Object::get_self_width() const {
  return api()->obj_get_self_width(m_object);
}
Area Object::get_content_area() const {
  Area result;
  api()->obj_get_content_coords(m_object, &result.m_area);
  return result;
}
Size Object::get_size() const { return {get_width(), get_height()}; }
lv_coord_t Object::get_height() const { return api()->obj_get_height(m_object); }
lv_coord_t Object::get_width() const { return api()->obj_get_width(m_object); }
lv_coord_t Object::get_y2() const { return api()->obj_get_y2(m_object); }
lv_coord_t Object::get_y() const { return api()->obj_get_y(m_object); }
lv_coord_t Object::get_x2() const { return api()->obj_get_x2(m_object); }
lv_coord_t Object::get_x() const { return api()->obj_get_x(m_object); }
bool Object::is_layout_positioned() const {
  return api()->obj_is_layout_positioned(m_object);
}
bool Object::is_findable() const { return api()->obj_is_valid(m_object); }
const lv_obj_class_t *Object::get_class() { return api()->obj_class; }

Area Object::get_coordinates() const {
  lv_area_t area;
  api()->obj_get_coords(m_object, &area);
  return Area(area);
}

Area Object::get_content_coordinates() const {
  lv_area_t area;
  api()->obj_get_content_coords(m_object, &area);
  return Area(area);
}
