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
  virtual ~UserData() = default;

  API_NO_DISCARD const char *name() const { return m_name ? m_name : "unnamed"; }

  template <typename Type> Type *cast() const {
    return reinterpret_cast<Type *>(const_cast<UserData *>(this));
  }

  API_NO_DISCARD const char *cast_as_name() const { return reinterpret_cast<const char *>(this); }

  API_NO_DISCARD void *cast_as_void() const {
    return reinterpret_cast<void *>(const_cast<UserData *>(this));
  }

  API_NO_DISCARD bool needs_free() const { return m_needs_free; }

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
  virtual ~UserDataAccess() = default;

  template <typename... Args> static Derived &create(Args... args) {
    return UserData::create<Derived>(args...);
  }

protected:
  using UserDataBase = UserDataAccess<Derived>;
};

class Object : public Api {
public:
  static constexpr lv_coord_t content_size = LV_SIZE_CONTENT;
  static constexpr lv_coord_t size_from_content = LV_SIZE_CONTENT;

  using Flags = ::lvgl::Flags;

  enum class Editable {
    inherit = LV_OBJ_CLASS_EDITABLE_INHERIT,
    yes = LV_OBJ_CLASS_EDITABLE_TRUE,
    no = LV_OBJ_CLASS_EDITABLE_FALSE
  };

  static void initialize() { lv_init(); }
  static void finalize() {
#if LV_ENABLE_GC || !LV_MEM_CUSTOM
    lv_deinit();
#endif
  }

  enum class IsRecursive { no, yes };

  API_NO_DISCARD bool has_flag(Flags flag) const {
    return api()->obj_has_flag(m_object, lv_obj_flag_t(flag));
  }

  API_NO_DISCARD bool has_any_flag(Flags flag) const {
    return api()->obj_has_flag_any(m_object, lv_obj_flag_t(flag));
  }

  API_NO_DISCARD State get_state() const { return State(api()->obj_get_state(m_object)); }

  API_NO_DISCARD bool has_state(State value) const {
    return api()->obj_has_state(m_object, lv_state_t(value));
  }

  template <class TargetClass> API_NO_DISCARD bool check_type() const {
    return api()->obj_check_type(m_object, TargetClass::get_class());
  }

  template <class TargetClass> API_NO_DISCARD bool is_class() const {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return api()->obj_get_class(m_object) == TargetClass::get_class();
  }

  template <class TargetClass> API_NO_DISCARD bool has_class() const {
    return api()->obj_has_class(m_object, TargetClass::get_class());
  }

  static const lv_obj_class_t *get_class() { return api()->obj_class; }

  API_NO_DISCARD bool is_findable() const { return api()->obj_is_valid(m_object); }
  API_NO_DISCARD bool is_valid() const { return m_object != nullptr; }

  API_NO_DISCARD bool is_layout_positioned() const { return api()->obj_is_layout_positioned(m_object); }

  API_NO_DISCARD lv_coord_t get_x() const { return api()->obj_get_x(m_object); }
  API_NO_DISCARD lv_coord_t get_x2() const { return api()->obj_get_x2(m_object); }
  API_NO_DISCARD lv_coord_t get_y() const { return api()->obj_get_y(m_object); }
  API_NO_DISCARD lv_coord_t get_y2() const { return api()->obj_get_y2(m_object); }
  API_NO_DISCARD lv_coord_t get_width() const { return api()->obj_get_width(m_object); }
  API_NO_DISCARD lv_coord_t get_height() const { return api()->obj_get_height(m_object); }

  API_NO_DISCARD Size get_size() const { return {get_width(), get_height()}; }

  API_NO_DISCARD Area get_content_area() const {
    Area result;
    api()->obj_get_content_coords(m_object, &result.m_area);
    return result;
  }

  API_NO_DISCARD lv_coord_t get_self_width() const { return api()->obj_get_self_width(m_object); }
  API_NO_DISCARD lv_coord_t get_self_height() const { return api()->obj_get_self_height(m_object); }
  API_NO_DISCARD lv_coord_t get_content_width() const { return api()->obj_get_content_width(m_object); }

  API_NO_DISCARD lv_coord_t get_content_height() const {
    return api()->obj_get_content_height(m_object);
  }

  API_NO_DISCARD bool is_visible(Area &area) const {
    return api()->obj_area_is_visible(m_object, area.area());
  }

  API_NO_DISCARD bool is_visible() const { return api()->obj_is_visible(m_object); }

  API_NO_DISCARD ScrollBarMode get_scrollbar_mode() const {
    return ScrollBarMode(api()->obj_get_scrollbar_mode(m_object));
  }

  API_NO_DISCARD Direction get_scroll_direction() const {
    return Direction(api()->obj_get_scroll_dir(m_object));
  }

  API_NO_DISCARD ScrollSnap get_scroll_snap_x() const {
    return ScrollSnap(api()->obj_get_scroll_snap_x(m_object));
  }

  API_NO_DISCARD ScrollSnap get_scroll_snap_y() const {
    return ScrollSnap(api()->obj_get_scroll_snap_y(m_object));
  }

  API_NO_DISCARD lv_coord_t get_scroll_x() const { return api()->obj_get_scroll_x(m_object); }
  API_NO_DISCARD lv_coord_t get_scroll_y() const { return api()->obj_get_scroll_y(m_object); }
  API_NO_DISCARD lv_coord_t get_scroll_top() const { return api()->obj_get_scroll_top(m_object); }
  API_NO_DISCARD lv_coord_t get_scroll_bottom() const { return api()->obj_get_scroll_bottom(m_object); }
  API_NO_DISCARD lv_coord_t get_scroll_left() const { return api()->obj_get_scroll_left(m_object); }
  API_NO_DISCARD lv_coord_t get_scroll_right() const { return api()->obj_get_scroll_right(m_object); }

  API_NO_DISCARD Point get_scroll_end() const {
    Point result;
    api()->obj_get_scroll_end(m_object, result.point());
    return result;
  }

  API_NO_DISCARD lv_coord_t get_left_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::left_padding, selector);
  }

  API_NO_DISCARD lv_coord_t get_right_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::right_padding, selector);
  }

  API_NO_DISCARD lv_coord_t get_top_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::top_padding, selector);
  }

  API_NO_DISCARD lv_coord_t get_bottom_padding(Selector selector = Selector()) const {
    return get_local_style_as_coord(Property::bottom_padding, selector);
  }

  API_NO_DISCARD PropertyValue get_property_value(Property property, Selector selector = Selector()) {
    PropertyValue result;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &result.m_value, selector.value());
    return result;
  }

  API_NO_DISCARD u32 get_child_count() const { return api()->obj_get_child_cnt(m_object); }
  API_NO_DISCARD u32 get_child_id() const { return api()->obj_get_child_id(m_object); }
  API_NO_DISCARD Object get_parent() const { return Object(api()->obj_get_parent(m_object)); }
  API_NO_DISCARD Object get_child(s32 id) const { return Object(api()->obj_get_child(m_object, id)); }

  template <class TargetClass> API_NO_DISCARD TargetClass get() {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return TargetClass(object());
  }

  template <IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD Object find_object(const char *name) const {
    auto result = find_object_worker(name);
    if( (isAssertOnFail == IsAssertOnFail::yes) && !result.is_valid() ){
      API_ASSERT(false);
    }
    return result;
  }

  template <class TargetClass = Object, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find(const char *name) const {
    return TargetClass(find_object<isAssertOnFail>(name).object());
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find_within(const char * top, const char * bottom) const {
    return find_object(top).find<TargetClass, isAssertOnFail>(bottom);
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find(const std::initializer_list<const char*> list) const {
    auto current = *this;
    for(const char * entry: list){
      current = current.find_object<isAssertOnFail>(entry);
      if( !current.is_valid() ){
        return Object().get<TargetClass>();
      }
    }
    return TargetClass(current.object());
  }

  template <class TargetClass> API_NO_DISCARD TargetClass find_parent() {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    auto current = get_parent();
    while (true) {
      if (current.object() == nullptr) {
        API_ASSERT(false);
      } else {
        if (current.is_class<TargetClass>()) {
          return current.get<TargetClass>();
        }
      }
      current = current.get_parent();
    }
  }

  API_NO_DISCARD Object find_child(const char *name) const;
  API_NO_DISCARD Object find(Point point){
    return Object(api()->indev_search_obj(m_object, point.point()));
  }

  API_NO_DISCARD ClassType get_class_type() const;
  static const char *to_cstring(ClassType value);
  static ClassType class_type_from_cstring(const char *value);

  API_NO_DISCARD Editable is_editable() const { return Editable(api()->obj_is_editable(m_object)); }

  lv_obj_t *object() { return m_object; }
  API_NO_DISCARD lv_obj_t *object() const { return m_object; }

  API_NO_DISCARD const char *name() const {
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
  friend class TabView;
  friend class Display;
  lv_obj_t *m_object = nullptr;

  void add_style_from_theme(var::StringView name, Selector selector = Selector());

  explicit Object(lv_obj_t *obj) : m_object(obj) {}
  static void set_user_data(lv_obj_t *obj, const char *name);
  static bool is_name_matched(const Object &child, const char *name);

  void construct_object(const char * name);
  void construct_label(const char * name);
  void construct_button(const char * name);

  API_NO_DISCARD lv_coord_t get_local_style_as_coord(Property property, Selector selector) const {
    lv_style_value_t value;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &value, selector.value());
    return value.num;
  }

  API_NO_DISCARD Color get_local_style_as_color(Property property, Selector selector) const {
    lv_style_value_t value;
    api()->obj_get_local_style_prop(
      m_object, lv_style_prop_t(property), &value, selector.value());
    return Color{value.color};
  }

  API_NO_DISCARD UserData *get_user_data() const { return UserData::get_user_data(m_object->user_data); }

private:
  friend class Tree;
  friend class Event;
  friend class TileView;
  friend class Group;
  static void delete_user_data(lv_event_t *);

  Object find_object_worker(const char *name) const;
};

API_OR_NAMED_FLAGS_OPERATOR(Object, Flags)

} // namespace lvgl

#endif // LVGLAPI_LVGL_OBJECT_HPP
