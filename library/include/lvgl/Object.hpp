#ifndef LVGLAPI_LVGL_OBJECT_HPP
#define LVGLAPI_LVGL_OBJECT_HPP

#include <var/StringView.hpp>

#include "Font.hpp"
#include "Style.hpp"

namespace lvgl {

class UserData {
  void *operator new(size_t size) { return ::operator new(size); }

public:
  explicit UserData(const char *name = "") : m_name(name) {}
  virtual ~UserData() {}

  const char *name() const { return m_name ? m_name : "unnamed"; }

  template <typename Type> Type *cast() const {
    return reinterpret_cast<Type *>(const_cast<UserData *>(this));
  }

  const char *cast_as_name() const { return reinterpret_cast<const char *>(this); }

  void *cast_as_void() const {
    return reinterpret_cast<void *>(const_cast<UserData *>(this));
  }

  bool needs_free() const { return m_needs_free; }

protected:
  // dynamically allocate the UserData and have it live with the created object
  // this will be freed when the associated object is removed
  template <class Derived, typename... Args> static Derived &create(Args... args) {
    auto *result = new Derived(args...);
    result->m_needs_free = true;
    return *result;
  }

private:
  friend class Object;

  static UserData *get_user_data(void *user_data) {
    auto *context = reinterpret_cast<UserData *>(user_data);
    return context->m_magic == reinterpret_cast<void *>(magic_function) ? context
                                                                        : nullptr;
  }

  static void magic_function() {}
  const void *m_magic = reinterpret_cast<void *>(magic_function);
  const char *m_name = nullptr;
  bool m_needs_free = false;
};

template <class Derived> class UserDataAccess : public UserData {
public:
  explicit UserDataAccess(const char *name = "") : UserData(name) {}
  virtual ~UserDataAccess() {}

  template <typename... Args> static Derived &create(Args... args) {
    return UserData::create<Derived>(args...);
  }

protected:
  using UserDataBase = UserDataAccess<Derived>;
};

enum class ObjectFlags {
  hidden = LV_OBJ_FLAG_HIDDEN,
  clickable = LV_OBJ_FLAG_CLICKABLE,
  focusable = LV_OBJ_FLAG_CLICK_FOCUSABLE,
  checkable = LV_OBJ_FLAG_CHECKABLE,
  scrollable = LV_OBJ_FLAG_SCROLLABLE,
  scroll_elastic = LV_OBJ_FLAG_SCROLL_ELASTIC,
  scroll_momentum = LV_OBJ_FLAG_SCROLL_MOMENTUM,
  scroll_one = LV_OBJ_FLAG_SCROLL_ONE,
  scroll_chain = LV_OBJ_FLAG_SCROLL_CHAIN,
  scroll_on_focus = LV_OBJ_FLAG_SCROLL_ON_FOCUS,
  snapable = LV_OBJ_FLAG_SNAPABLE,
  press_lock = LV_OBJ_FLAG_PRESS_LOCK,
  event_bubble = LV_OBJ_FLAG_EVENT_BUBBLE,
  gesture_bubble = LV_OBJ_FLAG_GESTURE_BUBBLE,
  advance_hittest = LV_OBJ_FLAG_ADV_HITTEST,
  ignore_layout = LV_OBJ_FLAG_IGNORE_LAYOUT,
  floating = LV_OBJ_FLAG_FLOATING,
  layout_1 = LV_OBJ_FLAG_LAYOUT_1,
  layout_2 = LV_OBJ_FLAG_LAYOUT_2,
  widget_1 = LV_OBJ_FLAG_WIDGET_1,
  widget_2 = LV_OBJ_FLAG_WIDGET_2,
  user_1 = LV_OBJ_FLAG_USER_1,
  user_2 = LV_OBJ_FLAG_USER_2,
  user_3 = LV_OBJ_FLAG_USER_3,
  user_4 = LV_OBJ_FLAG_USER_4
};

class Object : public Api {
public:
  static constexpr lv_coord_t content_size = LV_SIZE_CONTENT;
  static constexpr lv_coord_t size_from_content = LV_SIZE_CONTENT;

  using Flags = ObjectFlags;

  enum class Editable {
    inherit = LV_OBJ_CLASS_EDITABLE_INHERIT,
    yes = LV_OBJ_CLASS_EDITABLE_TRUE,
    no = LV_OBJ_CLASS_EDITABLE_FALSE
  };

  class Class {
  public:
    u16 width() const { return m_class->width_def; }
    u16 height() const { return m_class->height_def; }

    Editable editable() const { return Editable(m_class->editable); }

    const lv_obj_class_t *class_() const { return m_class; }

  private:
    friend class Object;
    Class(const lv_obj_class_t *value) : m_class(value) {}
    const lv_obj_class_t *m_class;
  };

  static void initialize() { lv_init(); }
  static void finalize() {
#if LV_ENABLE_GC || !LV_MEM_CUSTOM
    lv_deinit();
#endif
  }

  enum class IsRecursive { no, yes };

  bool is_flags(Flags flag) const {
    return api()->obj_has_flag(m_object, static_cast<lv_obj_flag_t>(flag));
  }

  bool is_any_flag(Flags flag) const {
    return api()->obj_has_flag_any(m_object, static_cast<lv_obj_flag_t>(flag));
  }

  State get_state() const { return State(api()->obj_get_state(m_object)); }

  bool is_state(State value) const {
    return api()->obj_has_state(m_object, static_cast<lv_state_t>(value));
  }

  bool check_type(const Class &value) const {
    return api()->obj_check_type(m_object, value.m_class);
  }

  bool has_class(const Class &value) const {
    return api()->obj_has_class(m_object, value.m_class);
  }

  Class get_instance_class() const { return Class(api()->obj_get_class(m_object)); }

  static const lv_obj_class_t *get_class() { return api()->obj_class; }

  bool is_valid() const { return api()->obj_is_valid(m_object); }

  bool is_layout_positioned() const { return api()->obj_is_layout_positioned(m_object); }

  lv_coord_t get_x() const { return api()->obj_get_x(m_object); }
  lv_coord_t get_x2() const { return api()->obj_get_x2(m_object); }
  lv_coord_t get_y() const { return api()->obj_get_y(m_object); }
  lv_coord_t get_y2() const { return api()->obj_get_y2(m_object); }
  lv_coord_t get_width() const { return api()->obj_get_width(m_object); }
  lv_coord_t get_height() const { return api()->obj_get_height(m_object); }

  Size get_size() const { return Size(get_width(), get_height()); }

  Area get_content_area() const {
    Area result;
    api()->obj_get_content_coords(m_object, &result.m_area);
    return result;
  }

  lv_coord_t get_self_width() const { return api()->obj_get_self_width(m_object); }
  lv_coord_t get_self_height() const { return api()->obj_get_self_height(m_object); }
  lv_coord_t get_content_width() const { return api()->obj_get_content_width(m_object); }

  lv_coord_t get_content_height() const {
    return api()->obj_get_content_height(m_object);
  }

  bool is_visible(Area &area) const {
    return api()->obj_area_is_visible(m_object, area.area());
  }

  bool is_visible() const { return api()->obj_is_visible(m_object); }

  ScrollBarMode get_scrollbar_mode() const {
    return ScrollBarMode(api()->obj_get_scrollbar_mode(m_object));
  }

  Direction get_scroll_direction() const {
    return Direction(api()->obj_get_scroll_dir(m_object));
  }

  ScrollSnap get_scroll_snap_x() const {
    return ScrollSnap(api()->obj_get_scroll_snap_x(m_object));
  }

  ScrollSnap get_scroll_snap_y() const {
    return ScrollSnap(api()->obj_get_scroll_snap_y(m_object));
  }

  lv_coord_t get_scroll_x() const { return api()->obj_get_scroll_x(m_object); }
  lv_coord_t get_scroll_y() const { return api()->obj_get_scroll_y(m_object); }
  lv_coord_t get_scroll_top() const { return api()->obj_get_scroll_top(m_object); }
  lv_coord_t get_scroll_bottom() const { return api()->obj_get_scroll_bottom(m_object); }
  lv_coord_t get_scroll_left() const { return api()->obj_get_scroll_left(m_object); }
  lv_coord_t get_scroll_right() const { return api()->obj_get_scroll_right(m_object); }

  Point get_scroll_end() const {
    Point result;
    api()->obj_get_scroll_end(m_object, result.point());
    return result;
  }

  lv_coord_t get_left_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::left_padding, selector);
  }

  lv_coord_t get_right_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::right_padding, selector);
  }

  lv_coord_t get_top_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::top_padding, selector);
  }

  lv_coord_t get_bottom_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::bottom_padding, selector);
  }

  PropertyValue get_property_value(Property property, Selector selector = Selector()) {
    PropertyValue result;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &result.m_value, selector.value());
    return result;
  }

  u32 get_child_count() const { return api()->obj_get_child_cnt(m_object); }
  u32 get_child_id() const { return api()->obj_get_child_id(m_object); }
  Object get_parent() const { return Object(api()->obj_get_parent(m_object)); }
  Object get_child(s32 id) const { return Object(api()->obj_get_child(m_object, id)); }

  template <class TargetClass> TargetClass get() {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return TargetClass(object());
  }

  template <class TargetClass> bool is_class() const {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return api()->obj_get_class(m_object) == TargetClass::get_class();
  }

  ClassType get_class_type() const;
  static const char *to_cstring(ClassType value);
  static ClassType class_type_from_cstring(const char *value);

  Editable is_editable() const { return Editable(api()->obj_is_editable(m_object)); }

  lv_obj_t *object() { return m_object; }
  const lv_obj_t *object() const { return m_object; }

  const char *name() const {
    API_ASSERT(m_object != nullptr);
    if (m_object->user_data == nullptr) {
      return "unnamed";
    }
    if (auto *user_data = UserData::get_user_data(m_object->user_data);
        user_data != nullptr) {
      return user_data->name();
    }
    return reinterpret_cast<const char *>(m_object->user_data);
  }

  template <class UserDataClass> UserDataClass *user_data() const {
    static_assert(std::is_base_of<UserData, UserDataClass>::value);
    if (auto *user_data = UserData::get_user_data(m_object->user_data);
        user_data != nullptr) {
      return reinterpret_cast<UserDataClass *>(user_data);
    }
    return nullptr;
  }

  Object() = default;

  void remove() {
    if (m_object) {
      api()->obj_del(m_object);
      m_object = nullptr;
    }
  }

  void async_remove() {
    if (m_object) {
      api()->obj_del_async(m_object);
      m_object = nullptr;
    }
  }

protected:
  lv_obj_t *m_object = nullptr;

  friend class TabView;

  explicit Object(lv_obj_t *obj) : m_object(obj) {}
  static void set_user_data(lv_obj_t *obj, const char *name);

  static bool is_name_matched(const Object &child, const char *name) {
    const auto child_name = child.name();
    if (
      (child_name != nullptr)
      && ((child_name == name) || (var::StringView(child.name()) == name))) {
      return true;
    }
    return false;
  }

  lv_coord_t get_local_style_as_coord(Property property, Selector selector) const {
    lv_style_value_t value;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &value, selector.value());
    return value.num;
  }

  Color get_local_style_as_color(Property property, Selector selector) const {
    lv_style_value_t value;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &value, selector.value());
    return Color(value.color);
  }

  UserData *get_user_data() const { return UserData::get_user_data(m_object->user_data); }

private:
  friend class Tree;
  friend class Event;
  friend class TileView;
  friend class Group;
  static void delete_user_data(lv_event_t *);
};

API_OR_NAMED_FLAGS_OPERATOR(Object, Flags)

} // namespace lvgl

#endif // LVGLAPI_LVGL_OBJECT_HPP
