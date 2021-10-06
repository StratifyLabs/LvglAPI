#ifndef LVGLAPI_LVGL_STYLE_HPP
#define LVGLAPI_LVGL_STYLE_HPP

#include <api/api.hpp>
#include <chrono/MicroTime.hpp>

#include <lvgl.h>
#include <lvgl_api.h>

#include "Color.hpp"

namespace lvgl {

class Font;

class Style : public Api {
public:
  Style() { api()->style_init(&m_style); }
  ~Style() { api()->style_reset(&m_style); }

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

  Style &set_align(Alignment value) {
    lv_style_value_t v = {.num = lv_align_t(value)};
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

  Style &set_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OPA, v);
    return *this;
  }

  Style &set_color_filter_descriptor(const lv_color_filter_dsc_t *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_COLOR_FILTER_DSC, v);
    return *this;
  }

  Style &set_color_filter_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_COLOR_FILTER_OPA, v);
    return *this;
  }

  Style &set_animation_time(uint32_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ANIM_TIME, v);
    return *this;
  }

  Style &set_animation_speed(uint32_t value) {
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

  Style &set_flex_layout() { return set_layout(*api()->layout_flex); }

  Style &set_flex_flow(FlexFlow value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_FLEX_FLOW, v);
    return set_flex_layout();
  }

  Style &set_flex_grow(u8 value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_FLEX_GROW, v);
    return *this;
  }


  Style &set_flex_align(const SetFlexAlign &value) {
    const lv_style_value_t main = {.num = static_cast<int32_t>(value.main())};
    const lv_style_value_t cross = {.num = static_cast<int32_t>(value.cross())};
    const lv_style_value_t track_cross = {
      .num = static_cast<int32_t>(value.track_cross())};
    api()->style_set_prop(&m_style, LV_STYLE_FLEX_MAIN_PLACE, main);
    api()->style_set_prop(&m_style, LV_STYLE_FLEX_CROSS_PLACE, cross);
    api()->style_set_prop(&m_style, LV_STYLE_FLEX_TRACK_PLACE, track_cross);
    return *this;
  }

  Style &set_base_dir(BaseDirection value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BASE_DIR, v);
    return *this;
  }

  Style &set_background_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_COLOR, v);
    return *this;
  }

  Style &set_background_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_background_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_OPA, v);
    return *this;
  }

  Style &set_background_gradient_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_COLOR, v);
    return *this;
  }

  Style &set_background_gradient_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_background_gradient_direction(GradientDirection value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_DIR, v);
    return *this;
  }

  Style &set_background_main_stop(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_MAIN_STOP, v);
    return *this;
  }

  Style &set_background_gradient_stop(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_GRAD_STOP, v);
    return *this;
  }

  Style &set_background_image_source(const void *value) {
    lv_style_value_t v = {.ptr = value};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_SRC, v);
    return *this;
  }

  Style &set_background_image_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_OPA, v);
    return *this;
  }

  Style &set_background_image_recolor(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR, v);
    return *this;
  }

  Style &set_background_image_recolor_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR_FILTERED, v);
    return *this;
  }

  Style &set_background_image_recolor_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_RECOLOR_OPA, v);
    return *this;
  }

  Style &set_background_image_tiled(bool value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_BG_IMG_TILED, v);
    return *this;
  }

  Style &set_border_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_COLOR, v);
    return *this;
  }

  Style &set_border_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_BORDER_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_border_opacity(lv_opa_t value) {
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

  Style &set_text_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_COLOR, v);
    return *this;
  }

  Style &set_text_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_text_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_OPA, v);
    return *this;
  }

  Style &set_text_font(const Font &value);

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

  Style &set_text_alignment(TextAlignment value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_TEXT_ALIGN, v);
    return *this;
  }

  Style &set_image_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_OPA, v);
    return *this;
  }

  Style &set_image_recolor(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR, v);
    return *this;
  }

  Style &set_image_recolor_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR_FILTERED, v);
    return *this;
  }

  Style &set_image_recolor_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_IMG_RECOLOR_OPA, v);
    return *this;
  }

  Style &set_outline_width(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_WIDTH, v);
    return *this;
  }

  Style &set_outline_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_COLOR, v);
    return *this;
  }

  Style &set_outline_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_OUTLINE_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_outline_opacity(lv_opa_t value) {
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

  Style &set_shadow_x_offset(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OFS_X, v);
    return *this;
  }

  Style &set_shadow_y_offset(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OFS_Y, v);
    return *this;
  }

  Style &set_shadow_spread(lv_coord_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_SPREAD, v);
    return *this;
  }

  Style &set_shadow_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_COLOR, v);
    return *this;
  }

  Style &set_shadow_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_shadow_opacity(lv_opa_t value) {
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

  Style &set_line_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_COLOR, v);
    return *this;
  }

  Style &set_line_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_LINE_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_line_opacity(lv_opa_t value) {
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

  Style &set_arc_color(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_COLOR, v);
    return *this;
  }

  Style &set_arc_color_filtered(Color value) {
    lv_style_value_t v = {.color = value.get_color()};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_COLOR_FILTERED, v);
    return *this;
  }

  Style &set_arc_opacity(lv_opa_t value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_ARC_OPA, v);
    return *this;
  }

  Style &set_arc_image_src(const void *value) {
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

} // namespace lvgl

#endif // LVGLAPI_LVGL_STYLE_HPP
