#ifndef LVGLAPI_LVGL_OBJECT_HPP
#define LVGLAPI_LVGL_OBJECT_HPP

#include <var/StringView.hpp>

#include "Font.hpp"
#include "Style.hpp"
#include "UserData.hpp"

namespace lvgl {

class Object : public Api {
public:
  class Iterator {
  public:
    Iterator() = default;
    Iterator(lv_obj_t *value, size_t index) {
      m_object_value = value;
      m_index = index;
    }
    bool operator!=(Iterator const &a) const noexcept { return m_index != a.m_index; }
    Object operator*() const noexcept {
      return Object(m_object_value).get_child(m_index);
    }
    Iterator &operator++() {
      m_index++;
      return *this;
    }
  private:
    lv_obj_t *m_object_value = nullptr;
    size_t m_index = 0;
  };

  Iterator begin() const noexcept { return Iterator(m_object, 0); }
  Iterator end() const noexcept { return Iterator(m_object, get_child_count()); }
  Iterator cbegin() const noexcept { return Iterator(m_object, 0); }
  Iterator cend() const noexcept { return Iterator(m_object, get_child_count()); }
  static constexpr lv_coord_t content_size = LV_SIZE_CONTENT;
  static constexpr lv_coord_t size_from_content = LV_SIZE_CONTENT;
  static constexpr lv_coord_t radius_circle = LV_RADIUS_CIRCLE;
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
  static const lv_obj_class_t *get_class();
  API_NO_DISCARD bool is_findable() const;
  API_NO_DISCARD bool is_valid() const { return m_object != nullptr; }
  API_NO_DISCARD bool is_layout_positioned() const;
  API_NO_DISCARD lv_coord_t get_x() const;
  API_NO_DISCARD lv_coord_t get_x2() const;
  API_NO_DISCARD lv_coord_t get_y() const;
  API_NO_DISCARD lv_coord_t get_y2() const;
  API_NO_DISCARD lv_coord_t get_width() const;
  API_NO_DISCARD lv_coord_t get_height() const;
  API_NO_DISCARD Area get_content_coordinates() const;
  API_NO_DISCARD Area get_coordinates() const;

  API_NO_DISCARD Size get_size() const;

  API_NO_DISCARD Area get_content_area() const;
  API_NO_DISCARD lv_coord_t get_self_width() const;
  API_NO_DISCARD lv_coord_t get_self_height() const;
  API_NO_DISCARD lv_coord_t get_content_width() const;
  API_NO_DISCARD lv_coord_t get_content_height() const;
  API_NO_DISCARD bool is_visible(Area &area) const;
  API_NO_DISCARD bool is_visible() const;
  API_NO_DISCARD ScrollBarMode get_scrollbar_mode() const;
  API_NO_DISCARD Direction get_scroll_direction() const;
  API_NO_DISCARD ScrollSnap get_scroll_snap_x() const;
  API_NO_DISCARD ScrollSnap get_scroll_snap_y() const;
  API_NO_DISCARD lv_coord_t get_scroll_x() const;
  API_NO_DISCARD lv_coord_t get_scroll_y() const;
  API_NO_DISCARD lv_coord_t get_scroll_top() const;
  API_NO_DISCARD lv_coord_t get_scroll_bottom() const;
  API_NO_DISCARD lv_coord_t get_scroll_left() const;
  API_NO_DISCARD lv_coord_t get_scroll_right() const;

  API_NO_DISCARD Point get_scroll_end() const;
  API_NO_DISCARD lv_coord_t get_left_padding(Selector selector = Selector()) const;
  API_NO_DISCARD lv_coord_t get_right_padding(Selector selector = Selector()) const;
  API_NO_DISCARD lv_coord_t get_top_padding(Selector selector = Selector()) const;
  API_NO_DISCARD lv_coord_t get_bottom_padding(Selector selector = Selector()) const;
  API_NO_DISCARD PropertyValue
  get_property_value(Property property, Selector selector = Selector());

  API_NO_DISCARD u32 get_child_count() const;
  API_NO_DISCARD u32 get_index() const;

  template <class TargetClass = Object> API_NO_DISCARD TargetClass get_parent() const {
    return TargetClass(api()->obj_get_parent(m_object));
  }
  template <class TargetClass = Object>
  API_NO_DISCARD TargetClass get_child(s32 id) const {
    return TargetClass(api()->obj_get_child(m_object, id));
  }

  template <class TargetClass> API_NO_DISCARD TargetClass get() const {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return TargetClass(object());
  }

  template <IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD Object find_object(const char *name) const {
    auto result = find_object_worker(name);
    if ((isAssertOnFail == IsAssertOnFail::yes) && !result.is_valid()) {
      API_ASSERT(false);
    }
    return result;
  }

  template <
    class TargetClass = Object,
    IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find(const char *name) const {
    return TargetClass(find_object<isAssertOnFail>(name).object());
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find_within(const char *top, const char *bottom) const {
    return find_object(top).find<TargetClass, isAssertOnFail>(bottom);
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  API_NO_DISCARD TargetClass find(const std::initializer_list<const char *> list) const {
    auto current = *this;
    for (const char *entry : list) {
      current = current.find_object<isAssertOnFail>(entry);
      if (!current.is_valid()) {
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

  template <class TargetClass>
  API_NO_DISCARD TargetClass find_parent(const char *name) const {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return find_parent_by_name(name).get<TargetClass>();
  }

  template <class TargetClass>
  API_NO_DISCARD TargetClass find_parent_using_partial_name(const char *name) const {
    static_assert(std::is_base_of<Object, TargetClass>::value);
    return find_parent_by_partial_name(name).get<TargetClass>();
  }

  API_NO_DISCARD Object find_child(const char *name) const;
  API_NO_DISCARD Object find(Point point) {
    return Object(api()->indev_search_obj(m_object, point.point()));
  }

  API_NO_DISCARD ClassType get_class_type() const;
  static const char *to_cstring(ClassType value);
  static ClassType class_type_from_string(const var::StringView value);

  API_NO_DISCARD Editable is_editable() const {
    return Editable(api()->obj_is_editable(m_object));
  }

  lv_obj_t *object() { return m_object; }
  API_NO_DISCARD lv_obj_t *object() const { return m_object; }

  API_NO_DISCARD const char *name() const {
    API_ASSERT(m_object != nullptr);
    if (m_object->user_data == nullptr) {
      return "unnamed";
    }
    if (auto *user_data = UserData::get_user_data(m_object->user_data); user_data) {
      return reinterpret_cast<UserData*>(user_data)->m_name;
    }
    return static_cast<const char *>(m_object->user_data);
  }

  template <class UserDataClass> UserDataClass *user_data() const {
    static_assert(std::is_base_of<UserData, UserDataClass>::value);
    if (auto *user_data =
          UserData::get_user_data_derived<UserDataClass>(m_object->user_data);
        user_data) {
      return static_cast<UserDataClass *>(user_data);
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

  void remove_later(const chrono::MicroTime delay) {
    if (m_object) {
      api()->obj_del_delayed(m_object, delay.milliseconds());
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

  void find_names_add_state(const var::StringViewList &name_list, State state);
  void find_names_clear_state(const var::StringViewList &name_list, State state);

  API_MAYBE_UNUSED void construct_object(const char *name);
  API_MAYBE_UNUSED void construct_canvas(const char *name);
  API_MAYBE_UNUSED void construct_label(const char *name);
  API_MAYBE_UNUSED void construct_line(const char *name);
  API_MAYBE_UNUSED void construct_button(const char *name);
  API_MAYBE_UNUSED void construct_list(const char *name);
  API_MAYBE_UNUSED void construct_dropdown(const char *name);
  API_MAYBE_UNUSED void construct_switch(const char *name);

  API_NO_DISCARD lv_coord_t
  get_local_style_as_coord(Property property, Selector selector) const;
  API_NO_DISCARD Color
  get_local_style_as_color(Property property, Selector selector) const;

private:
  friend class Tree;
  friend class Event;
  friend class TileView;
  friend class Group;
  static void delete_user_data(lv_event_t *);

  Object find_object_worker(const char *name) const;

  Object find_parent_by_name(const char *name) const;
  Object find_parent_by_partial_name(var::StringView name) const;
};

API_OR_NAMED_FLAGS_OPERATOR(Object, Flags)

} // namespace lvgl

#endif // LVGLAPI_LVGL_OBJECT_HPP
