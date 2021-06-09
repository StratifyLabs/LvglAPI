#ifndef LVGLAPI_LVGL_STYLE_HPP
#define LVGLAPI_LVGL_STYLE_HPP

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

class Point {
public:
  Point() = default;
  Point(lv_coord_t x, lv_coord_t y) : m_point{x, y} {}

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

class Style : public Api {
public:
  class Value {
  public:
    lv_style_value_t value() const { return m_value; }

  private:
    lv_style_value_t m_value;
  };

  Style() { api()->style_init(&m_style); }

  Style &set_width(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_WIDTH, v);
    return *this;
  }

  Style &set_min_width(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_MIN_WIDTH, v);
    return *this;
  }

  Style &set_max_width(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_MAX_WIDTH, v);
    return *this;
  }

  Style &set_height(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_HEIGHT, v);
    return *this;
  }

  Style &set_min_height(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_MIN_HEIGHT, v);
    return *this;
  }

  Style &set_max_height(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_MAX_HEIGHT, v);
    return *this;
  }

  Style &set_x(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_X, v);
    return *this;
  }

  Style &set_y(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_Y, v);
    return *this;
  }

  Style &set_align(lv_align_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_ALIGN, v);
    return *this;
  }

  Style &set_transform_width(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSFORM_WIDTH, v);
    return *this;
  }

  Style &set_transform_height(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSFORM_HEIGHT, v);
    return *this;
  }

  Style &set_translate_x(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSLATE_X, v);
    return *this;
  }

  Style &set_translate_y(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSLATE_Y, v);
    return *this;
  }

  Style &set_transform_zoom(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSFORM_ZOOM, v);
    return *this;
  }

  Style &set_transform_angle(lv_coord_t value) {
    lv_style_value_t v = {.num = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSFORM_ANGLE, v);
    return *this;
  }

  Style &set_top_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_TOP, v);
    return *this;
  }

  Style &set_bottom_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_BOTTOM, v);
    return *this;
  }

  Style &set_left_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_LEFT, v);
    return *this;
  }

  Style &set_right_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_RIGHT, v);
    return *this;
  }

  Style &set_row_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_ROW, v);
    return *this;
  }

  Style &set_column_padding(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_PAD_COLUMN, v);
    return *this;
  }

  Style &set_radius(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_RADIUS, v);
    return *this;
  }

  Style &set_clip_corner(bool value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_CLIP_CORNER, v);
    return *this;
  }

  Style &set_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OPA, v);
    return *this;
  }

  Style &set_color_filter_descriptor(const lv_color_filter_dsc_t *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_COLOR_FILTER_DSC, v);
    return *this;
  }

  Style &set_color_filter_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_COLOR_FILTER_OPA, v);
    return *this;
  }

  Style &set_anim_time(uint32_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ANIM_TIME, v);
    return *this;
  }

  Style &set_anim_speed(uint32_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ANIM_SPEED, v);
    return *this;
  }

  Style &set_transition(const lv_style_transition_dsc_t *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_TRANSITION, v);
    return *this;
  }

  Style &set_blend_mode(lv_blend_mode_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BLEND_MODE, v);
    return *this;
  }

  Style &set_layout(uint16_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LAYOUT, v);
    return *this;
  }

  Style &set_base_dir(BaseDirection value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BASE_DIR, v);
    return *this;
  }

  Style &set_bg_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_COLOR, v);
    return *this;
  }

  Style &set_bg_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_bg_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_OPA, v);
    return *this;
  }

  Style &set_bg_grad_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_COLOR, v);
    return *this;
  }

  Style &set_bg_grad_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_bg_grad_dir(GradientDirection value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_DIR, v);
    return *this;
  }

  Style &set_bg_main_stop(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_MAIN_STOP, v);
    return *this;
  }

  Style &set_bg_grad_stop(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_STOP, v);
    return *this;
  }

  Style &set_background_image_source(const void *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_SRC, v);
    return *this;
  }

  Style &set_background_image_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_OPA, v);
    return *this;
  }

  Style &set_background_image_recolor(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR, v);
    return *this;
  }

  Style &set_background_image_recolor_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR_FILTERED, v);
    return *this;
  }

  Style &set_background_image_recolor_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR_OPA, v);
    return *this;
  }

  Style &set_background_image_tiled(bool value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_TILED, v);
    return *this;
  }

  Style &set_border_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_COLOR, v);
    return *this;
  }

  Style &set_border_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_border_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_OPA, v);
    return *this;
  }

  Style &set_border_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_WIDTH, v);
    return *this;
  }

  Style &set_border_side(BorderSide value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_SIDE, v);
    return *this;
  }

  Style &set_border_post(bool value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_POST, v);
    return *this;
  }

  Style &set_text_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_COLOR, v);
    return *this;
  }

  Style &set_text_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_text_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_OPA, v);
    return *this;
  }

  Style &set_text_font(const lv_font_t *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_FONT, v);
    return *this;
  }

  Style &set_text_letter_space(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_LETTER_SPACE, v);
    return *this;
  }

  Style &set_text_line_space(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_LINE_SPACE, v);
    return *this;
  }

  Style &set_text_decor(TextDecoration value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_DECOR, v);
    return *this;
  }

  Style &set_text_align(TextAlignment value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_ALIGN, v);
    return *this;
  }

  Style &set_img_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_OPA, v);
    return *this;
  }

  Style &set_img_recolor(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR, v);
    return *this;
  }

  Style &set_img_recolor_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR_FILTERED, v);
    return *this;
  }

  Style &set_img_recolor_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR_OPA, v);
    return *this;
  }

  Style &set_outline_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_WIDTH, v);
    return *this;
  }

  Style &set_outline_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_COLOR, v);
    return *this;
  }

  Style &set_outline_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_outline_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_OPA, v);
    return *this;
  }

  Style &set_outline_pad(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_PAD, v);
    return *this;
  }

  Style &set_shadow_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_WIDTH, v);
    return *this;
  }

  Style &set_shadow_ofs_x(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OFS_X, v);
    return *this;
  }

  Style &set_shadow_ofs_y(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OFS_Y, v);
    return *this;
  }

  Style &set_shadow_spread(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_SPREAD, v);
    return *this;
  }

  Style &set_shadow_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_COLOR, v);
    return *this;
  }

  Style &set_shadow_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_shadow_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OPA, v);
    return *this;
  }

  Style &set_line_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_WIDTH, v);
    return *this;
  }

  Style &set_line_dash_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_DASH_WIDTH, v);
    return *this;
  }

  Style &set_line_dash_gap(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_DASH_GAP, v);
    return *this;
  }

  Style &set_line_rounded(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_ROUNDED, v);
    return *this;
  }

  Style &set_line_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_COLOR, v);
    return *this;
  }

  Style &set_line_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_line_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_OPA, v);
    return *this;
  }

  Style &set_arc_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_WIDTH, v);
    return *this;
  }

  Style &set_arc_rounded(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_ROUNDED, v);
    return *this;
  }

  Style &set_arc_color(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_COLOR, v);
    return *this;
  }

  Style &set_arc_color_filtered(lv_color_t value) {
    lv_style_value_t v = {.color = value};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_arc_opa(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_OPA, v);
    return *this;
  }

  Style &set_arc_img_src(const void *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_IMG_SRC, v);
    return *this;
  }

  lv_style_t *style() { return &m_style; }
  const lv_style_t *style() const { return &m_style; }

private:
  friend class Object;
  lv_style_t m_style;
};

} // namespace lv

#endif // LVGLAPI_LVGL_STYLE_HPP
