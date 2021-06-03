#ifndef LVGLAPI_LVGL_OBJECT_HPP
#define LVGLAPI_LVGL_OBJECT_HPP

#include <api/api.hpp>
#include <lvgl.h>

#include "lvgl/lvgl_api.h"

namespace lv {

using LvglApi = api::Api<lvgl_api_t, LVGL_API_REQUEST>;

class Api : public api::ExecutionContext {
public:
  static LvglApi &api() { return m_api; }

private:
  static LvglApi m_api;
};

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

enum class Direction {
  none = LV_DIR_NONE,
  left = LV_DIR_LEFT,
  right = LV_DIR_RIGHT,
  top = LV_DIR_TOP,
  bottom = LV_DIR_BOTTOM,
  horizontal = LV_DIR_HOR,
  vertical = LV_DIR_VER,
  all = LV_DIR_ALL
};

enum class Property {
  invalid = LV_STYLE_PROP_INV,
  width = LV_STYLE_WIDTH,
  minimum_width = LV_STYLE_MIN_WIDTH,
  maximum_width = LV_STYLE_MAX_WIDTH,
  height = LV_STYLE_HEIGHT,
  minimum_height = LV_STYLE_MIN_HEIGHT,
  maximum_height = LV_STYLE_MAX_HEIGHT,
  x = LV_STYLE_X,
  y = LV_STYLE_Y,
  align = LV_STYLE_ALIGN,
  transform_width = LV_STYLE_TRANSFORM_WIDTH,
  transform_height = LV_STYLE_TRANSFORM_HEIGHT,
  translate_x = LV_STYLE_TRANSLATE_X,
  translate_y = LV_STYLE_TRANSLATE_Y,
  transform_zoom = LV_STYLE_TRANSFORM_ZOOM,
  transform_angle = LV_STYLE_TRANSFORM_ANGLE,
  pad_top = LV_STYLE_PAD_TOP,
  pad_bottom = LV_STYLE_PAD_BOTTOM,
  pad_left = LV_STYLE_PAD_LEFT,
  pad_right = LV_STYLE_PAD_RIGHT,
  pad_row = LV_STYLE_PAD_ROW,
  pad_column = LV_STYLE_PAD_COLUMN,
  background_color = LV_STYLE_BG_COLOR,
  background_color_filtered = LV_STYLE_BG_COLOR_FILTERED,
  background_opa = LV_STYLE_BG_OPA,
  background_gradient_color = LV_STYLE_BG_GRAD_COLOR,
  background_gradient_color_filtered = LV_STYLE_BG_GRAD_COLOR_FILTERED,
  background_gradient_direction = LV_STYLE_BG_GRAD_DIR,
  background_main_stop = LV_STYLE_BG_MAIN_STOP,
  background_gradient_stop = LV_STYLE_BG_GRAD_STOP,
  background_image_source = LV_STYLE_BG_IMG_SRC,
  background_image_opa = LV_STYLE_BG_IMG_OPA,
  background_image_recolor = LV_STYLE_BG_IMG_RECOLOR,
  background_image_recolor_filtered = LV_STYLE_BG_IMG_RECOLOR_FILTERED,
  background_image_recolor_opa = LV_STYLE_BG_IMG_RECOLOR_OPA,
  background_image_tiled = LV_STYLE_BG_IMG_TILED,
  border_color = LV_STYLE_BORDER_COLOR,
  border_color_filtered = LV_STYLE_BORDER_COLOR_FILTERED,
  border_opa = LV_STYLE_BORDER_OPA,
  border_width = LV_STYLE_BORDER_WIDTH,
  border_side = LV_STYLE_BORDER_SIDE,
  border_post = LV_STYLE_BORDER_POST,
  outline_width = LV_STYLE_OUTLINE_WIDTH,
  outline_color = LV_STYLE_OUTLINE_COLOR,
  outline_color_filtered = LV_STYLE_OUTLINE_COLOR_FILTERED,
  outline_opa = LV_STYLE_OUTLINE_OPA,
  outline_pad = LV_STYLE_OUTLINE_PAD,

  shadow_width            =  LV_STYLE_SHADOW_WIDTH,
  shadow_ofs_x            =  LV_STYLE_SHADOW_OFS_X,
  shadow_ofs_y            =  LV_STYLE_SHADOW_OFS_Y,
  shadow_spread           =  LV_STYLE_SHADOW_SPREAD,
  shadow_color            = LV_STYLE_SHADOW_COLOR,
  shadow_color_filtered   =  LV_STYLE_SHADOW_COLOR_FILTERED,
  shadow_opa              =  LV_STYLE_SHADOW_OPA,

  img_opa                 = LV_STYLE_IMG_OPA,
  img_recolor             = LV_STYLE_IMG_RECOLOR,
  img_recolor_filtered    =  LV_STYLE_IMG_RECOLOR_FILTERED,
  img_recolor_opa         = LV_STYLE_IMG_RECOLOR_OPA,

  line_width              =  LV_STYLE_LINE_WIDTH,
  line_dash_width         = LV_STYLE_LINE_DASH_WIDTH,
  line_dash_gap           = LV_STYLE_LINE_DASH_GAP,
  line_rounded            = LV_STYLE_LINE_ROUNDED,
  line_color              = LV_STYLE_LINE_COLOR,
  line_color_filtered     = LV_STYLE_LINE_COLOR_FILTERED,
  line_opa                = LV_STYLE_LINE_OPA,

  arc_width               =LV_STYLE_ARC_WIDTH,
  arc_rounded             = LV_STYLE_ARC_ROUNDED,
  arc_color               = LV_STYLE_ARC_COLOR,
  arc_color_filtered      = LV_STYLE_ARC_COLOR_FILTERED,
  arc_opa                 = LV_STYLE_ARC_OPA,
  arc_img_src             = LV_STYLE_ARC_IMG_SRC,

  text_color              = LV_STYLE_TEXT_COLOR,
  text_color_filtered     = LV_STYLE_TEXT_COLOR_FILTERED,
  text_opa                = LV_STYLE_TEXT_OPA,
  text_font               = LV_STYLE_TEXT_FONT,
  text_letter_space       = LV_STYLE_TEXT_LETTER_SPACE,
  text_line_space         = LV_STYLE_TEXT_LINE_SPACE,
  text_decor              = LV_STYLE_TEXT_DECOR,
  text_align              = LV_STYLE_TEXT_ALIGN,

  radius                  = LV_STYLE_RADIUS,
  clip_corner             = LV_STYLE_CLIP_CORNER,
  opa                     = LV_STYLE_OPA,
  color_filter_dsc        = LV_STYLE_COLOR_FILTER_DSC,
  color_filter_opa        = LV_STYLE_COLOR_FILTER_OPA,
  animation_time               = LV_STYLE_ANIM_TIME,
  animation_speed              = LV_STYLE_ANIM_SPEED,
  transition              = LV_STYLE_TRANSITION,
  blend_mode              = LV_STYLE_BLEND_MODE,
  layout                  = LV_STYLE_LAYOUT,
  base_dir                = LV_STYLE_BASE_DIR,


  any   =  LV_STYLE_PROP_ANY

};

enum class IsAnimate {
  no = LV_ANIM_OFF,
  yes = LV_ANIM_ON,
  repeat_infinite = LV_ANIM_REPEAT_INFINITE
};

enum class IsIgnoreFloating { no, yes };

enum class Event {
  pressed = LV_EVENT_PRESSED,
  pressing = LV_EVENT_PRESSING,
  press_lost = LV_EVENT_PRESS_LOST,
  short_clicked = LV_EVENT_SHORT_CLICKED,
  long_pressed = LV_EVENT_LONG_PRESSED,
  long_pressed_repeat = LV_EVENT_LONG_PRESSED_REPEAT,
  clicked = LV_EVENT_CLICKED,
  released = LV_EVENT_RELEASED,
  gesture = LV_EVENT_GESTURE,
  key = LV_EVENT_KEY,
  focused = LV_EVENT_FOCUSED,
  defocused = LV_EVENT_DEFOCUSED,
  leave = LV_EVENT_LEAVE,
  value_changed = LV_EVENT_VALUE_CHANGED,
  insert = LV_EVENT_INSERT,
  refresh = LV_EVENT_REFRESH,
  cancel = LV_EVENT_CANCEL,
  delete_ = LV_EVENT_DELETE
};

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

class Style {
public:
  lv_style_t *style() { return &m_style; }

  const lv_style_t *style() const { return &m_style; }

private:
  friend class Object;
  lv_style_t m_style;
};

class Position {
public:
  Position() = default;
  Position(lv_coord_t x, lv_coord_t y) : m_position{x, y} {}

  Position operator+(const Position &a) const {
    return Position(m_position.x + a.m_position.x,
                    m_position.y + a.m_position.y);
  }

  Position &operator+(const Position &a) {
    m_position.x += a.m_position.x;
    m_position.y += a.m_position.y;
    return *this;
  }

  lv_coord_t x() const { return m_position.x; }
  lv_coord_t y() const { return m_position.y; }

  lv_point_t * position(){
    return &m_position;
  }

  const lv_point_t * position() const {
    return &m_position;
  }

private:
  lv_point_t m_position{};
};

class Size {
public:
  Size(lv_coord_t w, lv_coord_t h) : m_width(w), m_height(h) {}

  lv_coord_t width() const { return m_width; }
  lv_coord_t height() const { return m_height; }

private:
  lv_coord_t m_width;
  lv_coord_t m_height;
};

class Area {
public:
  Area() = default;
  Area(const Position &position, const Size &size) {
    m_area.x1 = position.x();
    m_area.y1 = position.y();
    m_area.x2 = position.x() + size.width();
    m_area.y2 = position.y() + size.height();
  }

  lv_area_t *area() { return &m_area; }

  const lv_area_t *area() const { return &m_area; }

private:
  friend class Object;
  lv_area_t m_area{};
};

enum class Alignment {
  default_ = LV_ALIGN_DEFAULT,
  top_left = LV_ALIGN_TOP_LEFT,
  top_middle = LV_ALIGN_TOP_MID,
  top_right = LV_ALIGN_TOP_RIGHT,
  bottom_left = LV_ALIGN_BOTTOM_LEFT,
  bottom_middle = LV_ALIGN_BOTTOM_MID,
  bottom_right = LV_ALIGN_BOTTOM_RIGHT,
  left_middle = LV_ALIGN_LEFT_MID,
  right_middle = LV_ALIGN_RIGHT_MID,
  center = LV_ALIGN_CENTER,

  out_top_left = LV_ALIGN_OUT_TOP_LEFT,
  out_top_mid = LV_ALIGN_OUT_TOP_MID,
  out_top_right = LV_ALIGN_OUT_TOP_RIGHT,
  out_bottom_left = LV_ALIGN_OUT_BOTTOM_LEFT,
  out_bottom_middle = LV_ALIGN_OUT_BOTTOM_MID,
  out_bottom_right = LV_ALIGN_OUT_BOTTOM_RIGHT,
  out_left_top = LV_ALIGN_OUT_LEFT_TOP,
  out_left_middle = LV_ALIGN_OUT_LEFT_MID,
  out_left_bottom = LV_ALIGN_OUT_LEFT_BOTTOM,
  out_right_top = LV_ALIGN_OUT_RIGHT_TOP,
  out_right_middle = LV_ALIGN_OUT_RIGHT_MID,
  out_right_bottom = LV_ALIGN_OUT_RIGHT_BOTTOM
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

  Object();
  Object(Object &parent) { m_object = lv_obj_create(parent.m_object); }

  ~Object() { lv_obj_del(m_object); }

  static void initialize() { lv_init(); }
  static void finalize() { lv_deinit(); }

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

  bool is_layout_positioned() const {
    return api()->obj_is_layout_positioned(m_object);
  }

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

  lv_coord_t get_self_width() const {
    return api()->obj_get_self_width(m_object);
  }

  lv_coord_t get_self_height() const {
    return api()->obj_get_self_height(m_object);
  }

  lv_coord_t get_content_width() const {
    return api()->obj_get_content_width(m_object);
  }

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

  lv_coord_t get_scroll_top() const {
    return api()->obj_get_scroll_top(m_object);
  }

  lv_coord_t get_scroll_bottom() const {
    return api()->obj_get_scroll_bottom(m_object);
  }

  lv_coord_t get_scroll_left() const {
    return api()->obj_get_scroll_left(m_object);
  }

  lv_coord_t get_scroll_right() const {
    return api()->obj_get_scroll_right(m_object);
  }

  lv_obj_t *object() { return m_object; }
  const lv_obj_t *object() const { return m_object; }

protected:
  lv_obj_t *m_object = nullptr;
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

  Derived &set_position(const Position &position) {
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

  Derived &align(Alignment alignment, const Position &offset) {
    api()->obj_align(m_object, static_cast<lv_align_t>(alignment), offset.x(),
                     offset.y());
    return static_cast<Derived &>(*this);
  }

  Derived &align(const Object &object, Alignment alignment,
                 const Position &offset) {
    api()->obj_align_to(m_object, object.object(),
                        static_cast<lv_align_t>(alignment), offset.x(),
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

  Derived &move_to(const Position &position) {
    api()->obj_refr_pos(m_object, position.x(), position.y());
    return static_cast<Derived &>(*this);
  }

  Derived &move_children_by(const Position &difference,
                            IsIgnoreFloating is_ignore_floating) {
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
    api()->obj_set_scrollbar_mode(m_object,
                                  static_cast<lv_scrollbar_mode_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_direction(Direction value) {
    api()->obj_set_scroll_dir(m_object, static_cast<lv_dir_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_snap_x(ScrollSnap value) {
    api()->obj_set_scroll_snap_x(m_object,
                                 static_cast<lv_scroll_snap_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_scroll_snap_y(ScrollSnap value) {
    api()->obj_set_scroll_snap_y(m_object,
                                 static_cast<lv_scroll_snap_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_by(const Position &position, IsAnimate is_animate) {
    api()->obj_scroll_by(m_object, position.x(), position.y(),
                         is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to(const Position &position, IsAnimate is_animate) {
    api()->obj_scroll_to(m_object, position.x(), position.y(),
                         is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_x(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_x(m_object, value,
                           is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_y(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_y(m_object, value,
                           is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view(IsAnimate is_animate) {
    api()->obj_scroll_to_view(m_object,
                              is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view_recursive(IsAnimate is_animate) {
    api()->obj_scroll_to_view_recursive(
        m_object, is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &update_snap(IsAnimate is_animate) {
    api()->obj_update_snap(m_object,
                           is_animate == IsAnimate::yes ? true : false);
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate_scrollbar() {
    api()->obj_scrollbar_invalidate(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &add_style(const Style &style, lv_style_selector_t style_selector) {
    api()->obj_add_style(m_object, style.style(), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(const Style &style,
                        lv_style_selector_t style_selector) {
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

  Derived &set_parent(Object &parent) {
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
};

API_OR_NAMED_FLAGS_OPERATOR(Object, Flags)

} // namespace lv

#endif // LVGLAPI_LVGL_OBJECT_HPP
