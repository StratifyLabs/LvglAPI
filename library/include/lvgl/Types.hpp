#ifndef LVGLAPI_LVGL_TYPES_HPP
#define LVGLAPI_LVGL_TYPES_HPP


#include <api/api.hpp>
#include <chrono/MicroTime.hpp>

#include <lvgl.h>
#include <lvgl_api.h>

namespace lvgl {

using LvglApi = api::Api<lvgl_api_t, LVGL_API_REQUEST>;

class Api : public api::ExecutionContext {
public:
  static LvglApi &api() { return m_api; }

private:
  static LvglApi m_api;
};

class Point {
public:
  Point() = default;
  Point(lv_coord_t x, lv_coord_t y) : m_point{x, y} {}
  Point(const lv_point_t & point) : m_point(point){}

  Point operator+(const Point &a) const {
    return Point(m_point.x + a.m_point.x,
                 m_point.y + a.m_point.y);
  }

  Point &operator+(const Point &a) {
    m_point.x += a.m_point.x;
    m_point.y += a.m_point.y;
    return *this;
  }

  lv_coord_t x() const { return m_point.x; }
  lv_coord_t y() const { return m_point.y; }

  lv_point_t *point() { return &m_point; }

  const lv_point_t *point() const { return &m_point; }

private:
  lv_point_t m_point{};
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
  Area(const Point &position, const Size &size) {
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

enum class EventCode {
  all = LV_EVENT_ALL,
  pressed = LV_EVENT_PRESSED,
  pressing = LV_EVENT_PRESSING,
  press_lost = LV_EVENT_PRESS_LOST,
  short_clicked = LV_EVENT_SHORT_CLICKED,
  long_pressed = LV_EVENT_LONG_PRESSED,
  long_pressed_repeat = LV_EVENT_LONG_PRESSED_REPEAT,
  clicked = LV_EVENT_CLICKED,
  released = LV_EVENT_RELEASED,
  scroll_begin = LV_EVENT_SCROLL_BEGIN,
  scroll_end = LV_EVENT_SCROLL_END,
  scroll = LV_EVENT_SCROLL,
  gesture = LV_EVENT_GESTURE,
  key = LV_EVENT_KEY,

  focused = LV_EVENT_FOCUSED,
  defocused = LV_EVENT_DEFOCUSED,
  leave = LV_EVENT_LEAVE,
  hit_test = LV_EVENT_HIT_TEST,

  cover_check = LV_EVENT_COVER_CHECK,
  refresh_external_drawing_size = LV_EVENT_REFR_EXT_DRAW_SIZE,
  draw_main_begin = LV_EVENT_DRAW_MAIN_BEGIN,
  draw_main = LV_EVENT_DRAW_MAIN,
  draw_main_end = LV_EVENT_DRAW_MAIN_END,
  draw_post_begin = LV_EVENT_DRAW_POST_BEGIN,
  draw_post = LV_EVENT_DRAW_POST,
  draw_post_end = LV_EVENT_DRAW_POST_END,
  draw_part_begin = LV_EVENT_DRAW_PART_BEGIN,
  draw_part_end = LV_EVENT_DRAW_PART_END,

  value_changed = LV_EVENT_VALUE_CHANGED,
  insert = LV_EVENT_INSERT,
  refresh = LV_EVENT_REFRESH,
  ready = LV_EVENT_READY,
  cancel = LV_EVENT_CANCEL,

  delete_ = LV_EVENT_DELETE,
  child_changed = LV_EVENT_CHILD_CHANGED,
  size_changed = LV_EVENT_SIZE_CHANGED,
  style_changed = LV_EVENT_STYLE_CHANGED,
  layout_changed = LV_EVENT_LAYOUT_CHANGED,
  get_self_size = LV_EVENT_GET_SELF_SIZE
};

enum class TextDecoration {
  none = LV_TEXT_DECOR_NONE,
  underline = LV_TEXT_DECOR_UNDERLINE,
  strikethrough = LV_TEXT_DECOR_STRIKETHROUGH
};

enum class TextAlignment {
  auto_ = LV_TEXT_ALIGN_AUTO,
  left = LV_TEXT_ALIGN_LEFT,
  center = LV_TEXT_ALIGN_CENTER,
  right = LV_TEXT_ALIGN_RIGHT
};

enum class BorderSide {
  none = LV_BORDER_SIDE_NONE,
  bottom = LV_BORDER_SIDE_BOTTOM,
  top = LV_BORDER_SIDE_TOP,
  left = LV_BORDER_SIDE_LEFT,
  right = LV_BORDER_SIDE_RIGHT,
  full = LV_BORDER_SIDE_FULL,
  internal = LV_BORDER_SIDE_INTERNAL
};

enum class GradientDirection {
  none = LV_GRAD_DIR_NONE,
  horizontal = LV_GRAD_DIR_HOR,
  vertical = LV_GRAD_DIR_VER
};

enum class BaseDirection {
  auto_ = LV_BASE_DIR_AUTO,
  left_to_right = LV_BASE_DIR_LTR,
  right_to_left = LV_BASE_DIR_RTL,
  neutral = LV_BASE_DIR_NEUTRAL,
  weak = LV_BASE_DIR_WEAK
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

API_OR_ENUM_CLASS(Direction)

enum class Alignment {
  default_ = LV_ALIGN_DEFAULT, top_left = LV_ALIGN_TOP_LEFT,
  top_middle = LV_ALIGN_TOP_MID, top_right = LV_ALIGN_TOP_RIGHT,
  bottom_left = LV_ALIGN_BOTTOM_LEFT, bottom_middle = LV_ALIGN_BOTTOM_MID,
  bottom_right = LV_ALIGN_BOTTOM_RIGHT, left_middle = LV_ALIGN_LEFT_MID,
  right_middle = LV_ALIGN_RIGHT_MID, center = LV_ALIGN_CENTER,

  out_top_left = LV_ALIGN_OUT_TOP_LEFT, out_top_mid = LV_ALIGN_OUT_TOP_MID,
  out_top_right = LV_ALIGN_OUT_TOP_RIGHT,
  out_bottom_left = LV_ALIGN_OUT_BOTTOM_LEFT,
  out_bottom_middle = LV_ALIGN_OUT_BOTTOM_MID,
  out_bottom_right = LV_ALIGN_OUT_BOTTOM_RIGHT,
  out_left_top = LV_ALIGN_OUT_LEFT_TOP, out_left_middle = LV_ALIGN_OUT_LEFT_MID,
  out_left_bottom = LV_ALIGN_OUT_LEFT_BOTTOM,
  out_right_top = LV_ALIGN_OUT_RIGHT_TOP,
  out_right_middle = LV_ALIGN_OUT_RIGHT_MID,
  out_right_bottom = LV_ALIGN_OUT_RIGHT_BOTTOM
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

  shadow_width = LV_STYLE_SHADOW_WIDTH,
  shadow_ofs_x = LV_STYLE_SHADOW_OFS_X,
  shadow_ofs_y = LV_STYLE_SHADOW_OFS_Y,
  shadow_spread = LV_STYLE_SHADOW_SPREAD,
  shadow_color = LV_STYLE_SHADOW_COLOR,
  shadow_color_filtered = LV_STYLE_SHADOW_COLOR_FILTERED,
  shadow_opa = LV_STYLE_SHADOW_OPA,

  img_opa = LV_STYLE_IMG_OPA,
  img_recolor = LV_STYLE_IMG_RECOLOR,
  img_recolor_filtered = LV_STYLE_IMG_RECOLOR_FILTERED,
  img_recolor_opa = LV_STYLE_IMG_RECOLOR_OPA,

  line_width = LV_STYLE_LINE_WIDTH,
  line_dash_width = LV_STYLE_LINE_DASH_WIDTH,
  line_dash_gap = LV_STYLE_LINE_DASH_GAP,
  line_rounded = LV_STYLE_LINE_ROUNDED,
  line_color = LV_STYLE_LINE_COLOR,
  line_color_filtered = LV_STYLE_LINE_COLOR_FILTERED,
  line_opa = LV_STYLE_LINE_OPA,

  arc_width = LV_STYLE_ARC_WIDTH,
  arc_rounded = LV_STYLE_ARC_ROUNDED,
  arc_color = LV_STYLE_ARC_COLOR,
  arc_color_filtered = LV_STYLE_ARC_COLOR_FILTERED,
  arc_opa = LV_STYLE_ARC_OPA,
  arc_img_src = LV_STYLE_ARC_IMG_SRC,

  text_color = LV_STYLE_TEXT_COLOR,
  text_color_filtered = LV_STYLE_TEXT_COLOR_FILTERED,
  text_opa = LV_STYLE_TEXT_OPA,
  text_font = LV_STYLE_TEXT_FONT,
  text_letter_space = LV_STYLE_TEXT_LETTER_SPACE,
  text_line_space = LV_STYLE_TEXT_LINE_SPACE,
  text_decor = LV_STYLE_TEXT_DECOR,
  text_align = LV_STYLE_TEXT_ALIGN,

  radius = LV_STYLE_RADIUS,
  clip_corner = LV_STYLE_CLIP_CORNER,
  opa = LV_STYLE_OPA,
  color_filter_dsc = LV_STYLE_COLOR_FILTER_DSC,
  color_filter_opa = LV_STYLE_COLOR_FILTER_OPA,
  animation_time = LV_STYLE_ANIM_TIME,
  animation_speed = LV_STYLE_ANIM_SPEED,
  transition = LV_STYLE_TRANSITION,
  blend_mode = LV_STYLE_BLEND_MODE,
  layout = LV_STYLE_LAYOUT,
  base_dir = LV_STYLE_BASE_DIR,

  any = LV_STYLE_PROP_ANY

};

enum class FlexFlow {
  row = LV_FLEX_FLOW_ROW,
  column = LV_FLEX_FLOW_COLUMN,
  row_wrap = LV_FLEX_FLOW_ROW_WRAP,
  row_reverse = LV_FLEX_FLOW_ROW_REVERSE,
  row_wrap_reverse = LV_FLEX_FLOW_ROW_WRAP_REVERSE,
  column_wrap = LV_FLEX_FLOW_COLUMN_WRAP,
  column_reverse = LV_FLEX_FLOW_COLUMN_REVERSE,
  column_wrap_reverse = LV_FLEX_FLOW_COLUMN_WRAP_REVERSE
};

enum class FlexAlign {
  start = LV_FLEX_ALIGN_START,
  end = LV_FLEX_ALIGN_END,
  center = LV_FLEX_ALIGN_CENTER,
  space_evenly = LV_FLEX_ALIGN_SPACE_EVENLY,
  space_around = LV_FLEX_ALIGN_SPACE_AROUND,
  space_between = LV_FLEX_ALIGN_SPACE_BETWEEN
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

enum class BlendMode {
  normal = LV_BLEND_MODE_NORMAL,
  additive = LV_BLEND_MODE_ADDITIVE,
  subtractive = LV_BLEND_MODE_SUBTRACTIVE
};

enum class Opacity {
  transparent = LV_OPA_TRANSP,
  x0 = LV_OPA_0,
  x10 = LV_OPA_10,
  x20 = LV_OPA_20,
  x30 = LV_OPA_30,
  x40 = LV_OPA_40,
  x50 = LV_OPA_50,
  x60 = LV_OPA_60,
  x70 = LV_OPA_70,
  x80 = LV_OPA_80,
  x90 = LV_OPA_90,
  x100 = LV_OPA_100,
  cover = LV_OPA_COVER,
  opaque = LV_OPA_COVER
};

enum class MixRatio {
  x0 = LV_OPA_0,
  x10 = LV_OPA_10,
  x20 = LV_OPA_20,
  x30 = LV_OPA_30,
  x40 = LV_OPA_40,
  x50 = LV_OPA_50,
  x60 = LV_OPA_60,
  x70 = LV_OPA_70,
  x80 = LV_OPA_80,
  x90 = LV_OPA_90,
  x100 = LV_OPA_100
};


inline constexpr lv_coord_t operator"" _percent(unsigned long long value) {
  return LV_PCT(value);
}

}


#endif // LVGLAPI_LVGL_TYPES_HPP
