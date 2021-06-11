#ifndef LVGLAPI_LVGL_OBJECT_HPP
#define LVGLAPI_LVGL_OBJECT_HPP

#include <var/StringView.hpp>

#include "Event.hpp"
#include "Style.hpp"

namespace lv {

enum class State {
  default_ = LV_STATE_DEFAULT,
  checked = LV_STATE_CHECKED,
  focused = LV_STATE_FOCUSED,
  focus_key = LV_STATE_FOCUS_KEY,
  edited = LV_STATE_EDITED,
  hovered = LV_STATE_HOVERED,
  pressed = LV_STATE_PRESSED,
  scrolled = LV_STATE_SCROLLED,
  disabled = LV_STATE_DISABLED,

  user1 = LV_STATE_USER_1,
  user2 = LV_STATE_USER_2,
  user3 = LV_STATE_USER_3,
  user4 = LV_STATE_USER_4,
  any = LV_STATE_ANY
};

enum class ScrollBarMode {
  off = LV_SCROLLBAR_MODE_OFF,
  on = LV_SCROLLBAR_MODE_ON,
  active = LV_SCROLLBAR_MODE_ACTIVE,
  auto_ = LV_SCROLLBAR_MODE_AUTO
};

enum class ScrollSnap {
  off = LV_SCROLL_SNAP_NONE,
  start = LV_SCROLL_SNAP_START,
  end = LV_SCROLL_SNAP_END,
  center = LV_SCROLL_SNAP_CENTER
};

enum class IsAnimate {
  no = LV_ANIM_OFF,
  yes = LV_ANIM_ON,
  repeat_infinite = LV_ANIM_REPEAT_INFINITE
};

enum class IsIgnoreFloating { no, yes };

enum class Part {
  main = LV_PART_MAIN,
  scrollbar = LV_PART_SCROLLBAR,
  indicator = LV_PART_INDICATOR,
  knob = LV_PART_KNOB,
  selected = LV_PART_SELECTED,
  items = LV_PART_ITEMS,
  ticks = LV_PART_TICKS,
  cursor = LV_PART_CURSOR,
  any = LV_PART_ANY
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

enum class Key {
  up = LV_KEY_UP,
  down = LV_KEY_DOWN,
  right = LV_KEY_RIGHT,
  left = LV_KEY_LEFT,
  escape = LV_KEY_ESC,
  delete_ = LV_KEY_DEL,
  backspace = LV_KEY_BACKSPACE,
  enter = LV_KEY_ENTER,
  next = LV_KEY_NEXT,
  previous = LV_KEY_PREV,
  home = LV_KEY_HOME,
  end = LV_KEY_END
};

class Object : public Api {
public:
  using Flags = ObjectFlags;

  class Class {

  private:
    friend class Object;
    lv_obj_class_t m_class;
  };

  template <class ChildClass, typename... Args> ChildClass add_child(Args... args) {
    return ChildClass(*this, args...);
  }

  static void initialize() { lv_init(); }
  static void finalize() {
#if LV_ENABLE_GC || !LV_MEM_CUSTOM
    lv_deinit();
#endif
  }

  static Object active_screen() {
    Object result(lv_scr_act());
    result.set_name("objroot");
    return result;
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
    return api()->obj_check_type(m_object, &value.m_class);
  }

  bool is_class(const Class &value) const {
    return api()->obj_has_class(m_object, &value.m_class);
  }

  Class get_class() const {
    // this is wrong
    Class result;
    api()->obj_get_class(m_object);
    return result;
  }

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

  u32 get_child_count() const { return api()->obj_get_child_cnt(m_object); }

  u32 get_child_id() const { return api()->obj_get_child_id(m_object); }

  Object get_parent() const { return Object(api()->obj_get_parent(m_object)); }

  Object get_child(s32 id) const { return Object(api()->obj_get_child(m_object, id)); }

  Object get_child(const char *name) const {
    const auto count = get_child_count();
    for (u32 i = 0; i < count; i++) {
      auto child = get_child(i);
      if (is_name_matched(child, name)) {
        return child;
      }
    }
    return Object();
  }

  template <bool isAssertOnFail = true> Object find(const char *name) const {
    // recursively find the child
    auto get = get_child(name);
    if (get.object() != nullptr) {
      return get;
    }
    const auto count = get_child_count();
    for (u32 i = 0; i < count; i++) {
      const auto child = get_child(i);
      auto result = child.find<false>(name);
      if (result.m_object != nullptr) {
        return result;
      }
    }
    if (isAssertOnFail) {
      API_ASSERT(false);
    }
    return Object();
  }

  template <class ReinterpretedClass> ReinterpretedClass *cast() {
    return reinterpret_cast<ReinterpretedClass *>(this);
  }

  bool is_editable() const { return api()->obj_is_editable(m_object); }

  lv_obj_t *object() { return m_object; }
  const lv_obj_t *object() const { return m_object; }

  const char *name() const {
    API_ASSERT(m_object != nullptr);

    return m_object->user_data ? reinterpret_cast<const char *>(m_object->user_data)
                               : "unnamed";
  }

  Object() = default;

protected:
  lv_obj_t *m_object = nullptr;

  friend class TabView;
  void set_name(const char *name) {
    API_ASSERT(m_object != nullptr);
    m_object->user_data = (void *)name;
  }

  static bool is_name_matched(const Object &child, const char *name) {
    const auto child_name = child.name();
    if (child_name != nullptr && var::StringView(child.name()) == name) {
      return true;
    }
    return false;
  }

private:
  explicit Object(lv_obj_t *obj) : m_object(obj) {}
};

template <class Derived> class ObjectAccess : public Object {
public:
  Derived &add_flag(Flags flags) {
    api()->obj_add_flag(m_object, static_cast<lv_obj_flag_t>(flags));
    return static_cast<Derived &>(*this);
  }

  Derived &clear_flag(Flags flags) {
    api()->obj_clear_flag(m_object, static_cast<lv_obj_flag_t>(flags));
    return static_cast<Derived &>(*this);
  }

  Derived &add_state(State state) {
    api()->obj_add_state(m_object, static_cast<lv_state_t>(state));
    return static_cast<Derived &>(*this);
  }

  Derived &clear_state(State state) {
    api()->obj_clear_state(m_object, static_cast<lv_state_t>(state));
    return static_cast<Derived &>(*this);
  }

  Derived &allocate_special_attributes() {
    api()->obj_allocate_spec_attr(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_position(const Point &position) {
    api()->obj_set_pos(m_object, position.x(), position.y());
    return static_cast<Derived &>(*this);
  }

  Derived &set_x(lv_coord_t value) {
    api()->obj_set_x(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_y(lv_coord_t value) {
    api()->obj_set_y(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_size(const Size &size) {
    api()->obj_set_size(m_object, size.width(), size.height());
    return static_cast<Derived &>(*this);
  }

  Derived &refresh_size() {
    api()->obj_refr_size(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_width(lv_coord_t value) {
    api()->obj_set_width(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_height(lv_coord_t value) {
    api()->obj_set_height(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_content_width(lv_coord_t value) {
    api()->obj_set_content_width(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_content_height(lv_coord_t value) {
    api()->obj_set_content_height(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_content_size(const Size &size) {
    return set_content_width(size.width()).set_content_height(size.height());
  }

  Derived &set_layout(u32 layout) {
    api()->obj_set_layout(m_object, layout);
    return static_cast<Derived &>(*this);
  }

  Derived &mark_layout_as_dirty() {
    api()->obj_mark_layout_as_dirty(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &update_layout() {
    api()->obj_update_layout(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_alignment(Alignment alignment) {
    api()->obj_set_align(m_object, static_cast<lv_align_t>(alignment));
    return static_cast<Derived &>(*this);
  }

  Derived &align(Alignment alignment, const Point &offset = Point()) {
    api()->obj_align(
      m_object, static_cast<lv_align_t>(alignment), offset.x(), offset.y());
    return static_cast<Derived &>(*this);
  }

  Derived &
  align(const Object &object, Alignment alignment, const Point &offset = Point()) {
    api()->obj_align_to(
      m_object, object.object(), static_cast<lv_align_t>(alignment), offset.x(),
      offset.y());
    return static_cast<Derived &>(*this);
  }

  Derived &refresh_self_size() {
    api()->obj_refresh_self_size(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &refresh_position() {
    api()->obj_refr_pos(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &move_to(const Point &position) {
    api()->obj_refr_pos(m_object, position.x(), position.y());
    return static_cast<Derived &>(*this);
  }

  Derived &
  move_children_by(const Point &difference, IsIgnoreFloating is_ignore_floating) {
    api()->obj_move_children_by(
      m_object, difference.x(), difference.y(),
      is_ignore_floating == IsIgnoreFloating::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate_area(const Area &area) {
    api()->obj_invalidate_area(m_object, area.area());
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate() {
    api()->obj_invalidate(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_extended_click_area(lv_coord_t size) {
    api()->obj_set_ext_click_area(m_object, size);
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_mode(ScrollBarMode value) {
    api()->obj_set_scrollbar_mode(m_object, static_cast<lv_scrollbar_mode_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_direction(Direction value) {
    api()->obj_set_scroll_dir(m_object, static_cast<lv_dir_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_snap_x(ScrollSnap value) {
    api()->obj_set_scroll_snap_x(m_object, static_cast<lv_scroll_snap_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_snap_y(ScrollSnap value) {
    api()->obj_set_scroll_snap_y(m_object, static_cast<lv_scroll_snap_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_by(const Point &position, IsAnimate is_animate) {
    api()->obj_scroll_by(
      m_object, position.x(), position.y(), is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to(const Point &position, IsAnimate is_animate) {
    api()->obj_scroll_to(
      m_object, position.x(), position.y(), is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_x(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_x(m_object, value, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_y(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_y(m_object, value, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view(IsAnimate is_animate) {
    api()->obj_scroll_to_view(m_object, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view_recursive(IsAnimate is_animate) {
    api()->obj_scroll_to_view_recursive(
      m_object, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &update_snap(IsAnimate is_animate) {
    api()->obj_update_snap(m_object, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate_scrollbar() {
    api()->obj_scrollbar_invalidate(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &add_style(Style &style, lv_style_selector_t style_selector = 0) {
    api()->obj_add_style(m_object, style.style(), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(const Style &style, lv_style_selector_t style_selector) {
    api()->obj_remove_style(m_object, style.style(), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &refresh_style(Part part, lv_style_selector_t style_selector) {
    api()->obj_remove_style(m_object, static_cast<lv_part_t>(part), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &clean() {
    api()->obj_clean(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_parent(Object parent) {
    api()->obj_set_parent(m_object, parent.object());
    return static_cast<Derived &>(*this);
  }

  Derived &move_to_foreground() {
    api()->obj_move_foreground(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &move_to_background() {
    api()->obj_move_background(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &add_event_callback(
    EventCode event_code,
    void *context,
    void (*event_callback)(lv_event_t *)) {
    api()->obj_add_event_cb(
      m_object, event_callback, static_cast<lv_event_code_t>(event_code), context);
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_flow(FlexFlow value) {
    api()->obj_set_flex_flow(m_object, static_cast<lv_flex_flow_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_grow(u8 value) {
    api()->obj_set_flex_grow(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_align(FlexAlign main, FlexAlign cross, FlexAlign track) {
    api()->obj_set_flex_align(
      m_object, static_cast<lv_flex_align_t>(main), static_cast<lv_flex_align_t>(cross),
      static_cast<lv_flex_align_t>(track));
    return static_cast<Derived &>(*this);
  }

  template <class CreateDerived> class CreateAccess {
  public:
    using Callback = void (*)(Derived &, void *);

    CreateAccess(const char *name_value) : m_name(name_value) {}

    const char *name() const { return m_name; }

    Callback initialize() const { return m_initialize; }

    void *context() const { return m_context; }

    CreateDerived &set_context(void *context) {
      m_context = context;
      return static_cast<CreateDerived &>(*this);
    }

    CreateDerived &set_initialize(Callback callback) {
      m_initialize = callback;
      return static_cast<CreateDerived &>(*this);
    }

  private:
    Callback m_initialize = nullptr;
    void *m_context = nullptr;
    const char *m_name = nullptr;
  };

  template <class ChildClass, class ChildClassCreate>
  Derived &add(const ChildClassCreate &create) {
    ChildClass child(*this, create);
    if (create.initialize()) {
      create.initialize()(child, create.context());
    }
    return static_cast<Derived &>(*this);
  }
};

class Container : public ObjectAccess<Container> {
public:
  Container(const char *name) {
    m_object = api()->obj_create(lv_scr_act());
    set_name(name);
  }
  Container(lv_obj_t *object) { m_object = object; }

  static Container active_screen() {
    Container result(lv_scr_act());
    result.set_name("activeScreen");
    return result;
  }

private:
};

API_OR_NAMED_FLAGS_OPERATOR(Object, Flags)

} // namespace lv

#endif // LVGLAPI_LVGL_OBJECT_HPP
