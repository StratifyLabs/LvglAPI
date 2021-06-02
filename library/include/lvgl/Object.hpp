#ifndef LVGLAPI_LVGL_OBJECT_HPP
#define LVGLAPI_LVGL_OBJECT_HPP

#include <api/macros.hpp>
#include <lvgl.h>

namespace lv {

enum class State {
  default_ = LV_STATE_DEFAULT,
  checked = LV_STATE_CHECKED,
  focused = LV_STATE_FOCUSED,
  edited = LV_STATE_EDITED,
  hovered = LV_STATE_HOVERED,
  pressed = LV_STATE_PRESSED,
  disabled = LV_STATE_DISABLED
};

enum class Layout {
  off = LV_LAYOUT_OFF,
  center = LV_LAYOUT_CENTER,
  column_left = LV_LAYOUT_COLUMN_LEFT,
  column_middle = LV_LAYOUT_COLUMN_MID,
  column_right = LV_LAYOUT_COLUMN_RIGHT,
  row_top = LV_LAYOUT_ROW_TOP,
  row_middle = LV_LAYOUT_ROW_MID,
  row_bottom = LV_LAYOUT_ROW_BOTTOM,
  pretty_top = LV_LAYOUT_PRETTY_TOP,
  pretty_middle = LV_LAYOUT_PRETTY_MID,
  pretty_bottom = LV_LAYOUT_PRETTY_BOTTOM,
  grid = LV_LAYOUT_GRID
};

class Part {
public:
  constexpr Part(uint8_t value) : m_value(value){}
  constexpr operator uint8_t () const { return m_value; }

protected:
  uint8_t m_value;
};

enum class IsAnimate {
  no =  LV_ANIM_OFF,
  yes = LV_ANIM_ON,
  repeat_infinite = LV_ANIM_REPEAT_INFINITE
};

enum class Event {
  pressed = LV_EVENT_PRESSED,
  pressing = LV_EVENT_PRESSING,
  press_lost = LV_EVENT_PRESS_LOST,
  short_clicked = LV_EVENT_SHORT_CLICKED,
  long_pressed = LV_EVENT_LONG_PRESSED,
  long_pressed_repeat = LV_EVENT_LONG_PRESSED_REPEAT,
  clicked = LV_EVENT_CLICKED,
  released = LV_EVENT_RELEASED,
  drag_begin = LV_EVENT_DRAG_BEGIN,
  drag_end = LV_EVENT_DRAG_END,
  drag_throw_begin = LV_EVENT_DRAG_THROW_BEGIN,
  gesture = LV_EVENT_GESTURE,
  key = LV_EVENT_KEY,
  focused = LV_EVENT_FOCUSED,
  defocused = LV_EVENT_DEFOCUSED,
  leave = LV_EVENT_LEAVE,
  value_changed = LV_EVENT_VALUE_CHANGED,
  insert = LV_EVENT_INSERT,
  refresh = LV_EVENT_REFRESH,
  apply = LV_EVENT_APPLY,
  cancel = LV_EVENT_CANCEL,
  delete_ = LV_EVENT_DELETE
};

enum class Signal {
  cleanup = LV_SIGNAL_CLEANUP,
  child_changed = LV_SIGNAL_CHILD_CHG,
  coordinate_changed = LV_SIGNAL_COORD_CHG,
  parent_size_changed = LV_SIGNAL_PARENT_SIZE_CHG,
  style_changed = LV_SIGNAL_STYLE_CHG,
  base_direction_changed = LV_SIGNAL_BASE_DIR_CHG,
  extra_padding_changed = LV_SIGNAL_REFR_EXT_DRAW_PAD,
  get_type = LV_SIGNAL_GET_TYPE,
  get_style = LV_SIGNAL_GET_STYLE,
  get_state = LV_SIGNAL_GET_STATE_DSC,
  hit_test = LV_SIGNAL_HIT_TEST,
  pressed = LV_SIGNAL_PRESSED,
  pressing = LV_SIGNAL_PRESSING,
  press_lost = LV_SIGNAL_PRESS_LOST,
  released = LV_SIGNAL_RELEASED,
  long_press = LV_SIGNAL_LONG_PRESS,
  long_press_repeat = LV_SIGNAL_LONG_PRESS_REP,
  drag_begin = LV_SIGNAL_DRAG_BEGIN,
  drag_end = LV_SIGNAL_DRAG_END,
  gesture = LV_SIGNAL_GESTURE,
  leave = LV_SIGNAL_LEAVE,
  focus = LV_SIGNAL_FOCUS,
  defocus = LV_SIGNAL_DEFOCUS,
  control = LV_SIGNAL_CONTROL,
  get_editable = LV_SIGNAL_GET_EDITABLE
};


enum class Protection {
  none = LV_PROTECT_NONE,
  position = LV_PROTECT_POS,
  follow = LV_PROTECT_FOLLOW,
  parent = LV_PROTECT_PARENT,
  press_lost = LV_PROTECT_PRESS_LOST,
  click_focus = LV_PROTECT_CLICK_FOCUS,
  child_change = LV_PROTECT_CHILD_CHG
};

class Style {
public:
  lv_style_t *style() { return &m_style; }

  const lv_style_t *style() const { return &m_style; }

private:
  lv_style_t m_style;
};

enum class DragDirection {
  horizontal = LV_DRAG_DIR_HOR,
  vertical = LV_DRAG_DIR_VER,
  both = LV_DRAG_DIR_BOTH,
  first = LV_DRAG_DIR_ONE
};

enum class BaseDirection {
  left_to_right = LV_BIDI_DIR_LTR,
  right_to_left = LV_BIDI_DIR_RTL,
  auto_ = LV_BIDI_DIR_AUTO,
  inherit = LV_BIDI_DIR_INHERIT,
  neutral = LV_BIDI_DIR_NEUTRAL,
  weak = LV_BIDI_DIR_WEAK
};

class Point {
public:
  Point() = default;
  Point(lv_coord_t x, lv_coord_t y) : m_point{x, y} {}

  Point operator+(const Point &a) const {
    return Point(m_point.x + a.m_point.x, m_point.y + a.m_point.y);
  }

  Point &operator+(const Point &a) {
    m_point.x += a.m_point.x;
    m_point.y += a.m_point.y;
    return *this;
  }

  lv_coord_t x() const { return m_point.x; }

  lv_coord_t y() const { return m_point.y; }

private:
  lv_point_t m_point{};
};

class Area {
public:
  Area(lv_coord_t w, lv_coord_t h) : m_width(w), m_height(h) {}

  lv_coord_t width() const { return m_width; }

  lv_coord_t height() const { return m_height; }

private:
  lv_coord_t m_width;
  lv_coord_t m_height;
};

class Region {
public:
  Region(const Point &point, const Area &area) {
    m_region.x1 = point.x();
    m_region.y1 = point.y();
    m_region.x2 = point.x() + area.width();
    m_region.y2 = point.y() + area.height();
  }

  lv_area_t *region() { return &m_region; }

  const lv_area_t *region() const { return &m_region; }

private:
  lv_area_t m_region;
};

class Object {
public:
  Object();
  Object(Object &parent, const Object *copy = nullptr) {
    m_object = lv_obj_create(parent.m_object, copy ? copy->m_object : nullptr);
  }

  ~Object() { lv_obj_del(m_object); }

  static void initialize() { lv_init(); }
  static void finalize() { lv_deinit(); }

  enum class IsRecursive { no, yes };

  enum class DesignMode {
    draw_main = LV_DESIGN_DRAW_MAIN,
    draw_post = LV_DESIGN_DRAW_POST,
    cover_check = LV_DESIGN_COVER_CHK
  };

  size_t count_children(IsRecursive is_recursive = IsRecursive::no) const {
    if (is_recursive == IsRecursive::no) {
      return lv_obj_count_children(m_object);
    }
    return lv_obj_count_children_recursive(m_object);
  }

  bool is_visible(Region &region) const {
    return lv_obj_area_is_visible(m_object, region.region());
  }

  bool is_visible() const { return lv_obj_is_visible(m_object); }


  State get_state(Part part) const {
    return State(lv_obj_get_state(m_object, part));
  }

  Protection get_protection() const {
    return Protection(lv_obj_get_protect(m_object));
  }


  lv_obj_t *object() { return m_object; }
  const lv_obj_t *object() const { return m_object; }

protected:
  lv_obj_t *m_object = nullptr;
};

template <class Derived> class ObjectAccess : public Object {
public:
  Derived &add_style(Part part, Style &style) {
    lv_obj_add_style(m_object, part, style.style());
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(Part part, Style &style) {
    lv_obj_remove_style(m_object, part, style.style());
    return static_cast<Derived &>(*this);
  }

  Derived &clean_style_list(Part part, Style &style) {
    lv_obj_remove_style(m_object, part, style.style());
    return static_cast<Derived &>(*this);
  }

  Derived &reset_style_list(Part part, Style &style) {
    lv_obj_remove_style(m_object, part, style.style());
    return static_cast<Derived &>(*this);
  }

  Derived &clean() {
    lv_obj_clean(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_parent(Object &parent) {
    lv_obj_set_parent(m_object, parent.object());
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate_region(const Region &region) {
    lv_obj_invalidate_area(m_object, region.region());
    return static_cast<Derived &>(*this);
  }

  Derived &move_to_foreground() {
    lv_obj_move_foreground(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &move_to_background() {
    lv_obj_move_background(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &set_position(const Point &position) {
    lv_obj_set_pos(m_object, position.x(), position.y());
    return static_cast<Derived &>(*this);
  }

  Derived &set_auto_realign(bool value = true) {
    lv_obj_set_auto_realign(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_hidden(bool value = true) {
    lv_obj_set_hidden(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_clickable(bool value = true) {
    lv_obj_set_click(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_drag_parent(bool value = true) {
    lv_obj_set_drag_parent(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_focus_parent(bool value = true) {
    lv_obj_set_focus_parent(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_gesture_parent(bool value = true) {
    lv_obj_set_gesture_parent(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_propagate_events_to_parent(bool value = true) {
    lv_obj_set_parent_event(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_base_direction(bool value = true) {
    lv_obj_set_parent_event(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_draggable(bool value = true) {
    lv_obj_set_drag(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_throwable(bool value = true) {
    lv_obj_set_drag_throw(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_drag_direction(DragDirection value) {
    lv_obj_set_drag_dir(m_object, static_cast<lv_drag_dir_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_bring_to_top_on_click(bool value = true) {
    lv_obj_set_top(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_state(State state) {
    lv_obj_set_state(m_object, static_cast<lv_state_t>(state));
    return static_cast<Derived &>(*this);
  }

  Derived &add_state(State state) {
    lv_obj_add_state(m_object, static_cast<lv_state_t>(state));
    return static_cast<Derived &>(*this);
  }

  Derived &clear_state(State state) {
    lv_obj_clear_state(m_object, static_cast<lv_state_t>(state));
    return static_cast<Derived &>(*this);
  }

  Derived &add_protection(Protection value) {
    lv_obj_add_protect(m_object, static_cast<uint8_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &clear_protection(Protection value) {
    lv_obj_clear_protect(m_object, static_cast<uint8_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &finish_transitions(Part value) {
    lv_obj_finish_transitions(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_event_callback(lv_event_cb_t callback) {
    lv_obj_set_event_cb(m_object, callback);
    return static_cast<Derived &>(*this);
  }

};

enum class Fit {
  none = LV_FIT_NONE,
  tight = LV_FIT_TIGHT,
  parent = LV_FIT_PARENT,
  max = LV_FIT_MAX
};

class Fit4 {

private:
  API_AF(Fit4, Fit, left, Fit::none);
  API_AF(Fit4, Fit, right, Fit::none);
  API_AF(Fit4, Fit, top, Fit::none);
  API_AF(Fit4, Fit, bottom, Fit::none);
};

class Fit2 {

private:
  API_AF(Fit2, Fit, vertical, Fit::none);
  API_AF(Fit2, Fit, horizontal, Fit::none);
};

template<class Derived> class ContainerAccess : public ObjectAccess<Derived> {
public:
  Derived &set_layout(Layout value) {
    lv_cont_set_layout(Object::object(), static_cast<lv_layout_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_fit(const Fit4 & fit) {
    lv_cont_set_fit4(Object::object(),
                     static_cast<lv_fit_t>(fit.left()),
                     static_cast<lv_fit_t>(fit.right()),
                     static_cast<lv_fit_t>(fit.top()),
                     static_cast<lv_fit_t>(fit.bottom())
                     );
    return static_cast<Derived &>(*this);
  }

  Derived &set_fit(const Fit2 & fit) {
    lv_btn_set_fit2(Object::object(),
                     static_cast<lv_fit_t>(fit.horizontal()),
                     static_cast<lv_fit_t>(fit.vertical())
                     );
    return static_cast<Derived &>(*this);
  }

  Derived &set_fit(const Fit & fit) {
    lv_btn_set_fit(Object::object(),
                    static_cast<lv_fit_t>(fit)
                    );
    return static_cast<Derived &>(*this);
  }

  Fit get_fit_left() const {
    return Fit(lv_cont_get_fit_left(Object::object()));
  }

  Fit get_fit_right() const {
    return Fit(lv_cont_get_fit_right(Object::object()));
  }

  Fit get_fit_top() const {
    return Fit(lv_cont_get_fit_top(Object::object()));
  }

  Fit get_fit_bottom() const {
    return Fit(lv_cont_get_fit_bottom(Object::object()));
  }
};

} // namespace lv

#endif // LVGLAPI_LVGL_OBJECT_HPP
