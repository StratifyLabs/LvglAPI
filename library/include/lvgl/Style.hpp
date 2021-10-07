#ifndef LVGLAPI_LVGL_STYLE_HPP
#define LVGLAPI_LVGL_STYLE_HPP

#include <api/api.hpp>
#include <chrono/MicroTime.hpp>

#include <lvgl.h>
#include <lvgl_api.h>

#include "Color.hpp"

namespace lvgl {

class Font;

class PropertyValue {
public:
  PropertyValue() = default;
  explicit PropertyValue(lv_style_value_t value) : m_value(value) {}
  PropertyValue(lv_coord_t coord) { m_value.num = coord; }
  PropertyValue(s32 number) { m_value.num = number; }
  PropertyValue(bool value) { m_value.num = value; }
  PropertyValue(lv_opa_t value) { m_value.num = value; }
  explicit PropertyValue(const void *pointer) { m_value.ptr = pointer; }
  PropertyValue(Color color) { m_value.color = color.get_color(); }

  u32 number() const { return m_value.num; }

  const void *pointer() const { return m_value.ptr; }

  Color color() const { return Color(m_value.color); }

private:
  friend class Object;
  friend class Style;
  lv_style_value_t m_value = {};
};

class Style : public Api {
public:
  Style() { api()->style_init(&m_style); }
  ~Style() { api()->style_reset(&m_style); }

  static const char * to_cstring(Property property);
  static Property property_from_cstring(const char * value);

  PropertyValue get_property_value(Property property) const {
    PropertyValue result;
    api()->style_get_prop(
      const_cast<lv_style_t *>(&m_style), lv_style_prop_t(property), &result.m_value);
    return result;
  }

  Style & set_property(Property property, PropertyValue value){
    api()->style_set_prop(&m_style, lv_style_prop_t(property), value.m_value);
    return *this;
  }

  Style &set_width(lv_coord_t value) {
    return set_property(Property::width, value);
  }

  Style &set_minimum_width(lv_coord_t value) {
    return set_property(Property::minimum_width, value);
  }

  Style &set_maximum_width(lv_coord_t value) {
    return set_property(Property::maximum_width, value);
  }

  Style &set_height(lv_coord_t value) {
    return set_property(Property::height, value);
  }

  Style &set_minimum_height(lv_coord_t value) {
    return set_property(Property::minimum_height, value);
  }

  Style &set_maximum_height(lv_coord_t value) {
    return set_property(Property::maximum_height, value);
  }

  Style &set_x(lv_coord_t value) {
    return set_property(Property::x, value);
  }

  Style &set_y(lv_coord_t value) {
    return set_property(Property::y, value);
  }

  Style &set_alignment(Alignment value) {
    return set_property(Property::alignment, s32(value));
  }

  Style &set_transform_width(lv_coord_t value) {
    return set_property(Property::transform_width, value);
  }

  Style &set_transform_height(lv_coord_t value) {
    return set_property(Property::transform_height, value);
  }

  Style &set_translate_x(lv_coord_t value) {
    return set_property(Property::translate_x, value);
  }

  Style &set_translate_y(lv_coord_t value) {
    return set_property(Property::translate_y, value);
  }

  Style &set_transform_zoom(lv_coord_t value) {
    return set_property(Property::transform_zoom, value);
  }

  Style &set_transform_angle(lv_coord_t value) {
    return set_property(Property::transform_angle, value);
  }

  Style &set_top_padding(lv_coord_t value) {
    return set_property(Property::top_padding, value);
  }

  Style &set_bottom_padding(lv_coord_t value) {
    return set_property(Property::bottom_padding, value);
  }

  Style &set_left_padding(lv_coord_t value) {
    return set_property(Property::left_padding, value);
  }

  Style &set_right_padding(lv_coord_t value) {
    return set_property(Property::right_padding, value);
  }

  Style &set_row_padding(lv_coord_t value) {
    return set_property(Property::row_padding, value);
  }

  Style &set_column_padding(lv_coord_t value) {
    return set_property(Property::column_padding, value);
  }

  Style &set_radius(lv_coord_t value) {
    return set_property(Property::radius, value);
  }

  Style &set_clip_corner(bool value) {
    return set_property(Property::clip_corner, value);
  }

  Style &set_opacity(lv_opa_t value) {
    return set_property(Property::opacity, value);
  }

  Style &set_color_filter_descriptor(const lv_color_filter_dsc_t *value) {
    return set_property(Property::color_filter_dsc, PropertyValue(value));
  }

  Style &set_color_filter_opacity(lv_opa_t value) {
    return set_property(Property::color_filter_opacity, value);
  }

  Style &set_animation_time(s32 value) {
    return set_property(Property::animation_time, value);
  }

  Style &set_animation_speed(s32 value) {
    return set_property(Property::animation_speed, value);
  }

  Style &set_transition(const lv_style_transition_dsc_t *value) {
    return set_property(Property::transition, PropertyValue(value));
  }

  Style &set_blend_mode(lv_blend_mode_t value) {
    return set_property(Property::blend_mode, value);
  }

  Style &set_layout(uint16_t value) {
    return set_property(Property::layout, s32(value));
  }

  Style &set_flex_layout() { return set_layout(*api()->layout_flex); }

  Style &set_flex_flow(FlexFlow value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, *api()->style_flex_flow, v);
    return set_flex_layout();
  }

  Style &set_flex_grow(u8 value) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, *api()->style_flex_grow, v);
    return *this;
  }

  Style &set_flex_align(const SetFlexAlign &value) {
    const lv_style_value_t main = {.num = static_cast<int32_t>(value.main())};
    const lv_style_value_t cross = {.num = static_cast<int32_t>(value.cross())};
    const lv_style_value_t track_cross = {
      .num = static_cast<int32_t>(value.track_cross())};
    api()->style_set_prop(&m_style, *api()->style_flex_main_place, main);
    api()->style_set_prop(&m_style, *api()->style_flex_cross_place, cross);
    api()->style_set_prop(&m_style, *api()->style_flex_track_place, track_cross);
    return *this;
  }

  Style &set_base_dir(BaseDirection value) {
    return set_property(Property::base_direction, s32(value));
  }

  Style &set_background_color(Color value) {
    return set_property(Property::background_color, value);
  }

  Style &set_background_color_filtered(Color value) {
    return set_property(Property::background_color_filtered, value);
  }

  Style &set_background_opacity(lv_opa_t value) {
    return set_property(Property::background_opacity, value);
  }

  Style &set_background_gradient_color(Color value) {
    return set_property(Property::background_gradient_color, value);
  }

  Style &set_background_gradient_color_filtered(Color value) {
    return set_property(Property::background_gradient_color_filtered, value);
  }

  Style &set_background_gradient_direction(GradientDirection value) {
    return set_property(Property::background_gradient_direction, s32(value));
  }

  Style &set_background_main_stop(lv_coord_t value) {
    return set_property(Property::background_main_stop, value);
  }

  Style &set_background_gradient_stop(lv_coord_t value) {
    return set_property(Property::background_gradient_stop, value);
  }

  Style &set_background_image_source(const void *value) {
    return set_property(Property::background_image_source, PropertyValue(value));
  }

  Style &set_background_image_opacity(lv_opa_t value) {
    return set_property(Property::background_image_opacity, value);
  }

  Style &set_background_image_recolor(Color value) {
    return set_property(Property::background_image_recolor, value);
  }

  Style &set_background_image_recolor_filtered(Color value) {
    return set_property(Property::background_image_recolor_filtered, value);
  }

  Style &set_background_image_recolor_opacity(lv_opa_t value) {
    return set_property(Property::background_image_opacity, value);
  }

  Style &set_background_image_tiled(bool value) {
    return set_property(Property::background_image_tiled, value);
  }

  Style &set_border_color(Color value) {
    return set_property(Property::border_color, value);
  }

  Style &set_border_color_filtered(Color value) {
    return set_property(Property::border_color_filtered, value);
  }

  Style &set_border_opacity(lv_opa_t value) {
    return set_property(Property::border_opacity, value);
  }

  Style &set_border_width(lv_coord_t value) {
    return set_property(Property::border_width, value);
  }

  Style &set_border_side(BorderSide value) {
    return set_property(Property::border_side, s32(value));
  }

  Style &set_border_post(bool value) {
    return set_property(Property::border_post, value);
  }

  Style &set_text_color(Color value) {
    return set_property(Property::text_color, value);
  }

  Style &set_text_color_filtered(Color value) {
    return set_property(Property::text_color_filtered, value);
  }

  Style &set_text_opacity(lv_opa_t value) {
    return set_property(Property::text_opacity, value);
  }

  Style &set_text_font(const Font &value);

  Style &set_text_letter_space(lv_coord_t value) {
    return set_property(Property::text_letter_spacing, value);
  }

  Style &set_text_line_space(lv_coord_t value) {
    return set_property(Property::text_line_spacing, value);
  }

  Style &set_text_decoration(TextDecoration value) {
    return set_property(Property::text_decoration, s32(value));
  }

  Style &set_text_alignment(TextAlignment value) {
    return set_property(Property::text_alignment, s32(value));
  }

  Style &set_image_opacity(lv_opa_t value) {
    return set_property(Property::image_opacity, value);
  }

  Style &set_image_recolor(Color value) {
    return set_property(Property::image_recolor, value);
  }

  Style &set_image_recolor_filtered(Color value) {
    return set_property(Property::image_recolor_filtered, value);
  }

  Style &set_image_recolor_opacity(lv_opa_t value) {
    return set_property(Property::image_recolor_opacity, value);
  }

  Style &set_outline_width(lv_coord_t value) {
    return set_property(Property::outline_width, value);
  }

  Style &set_outline_color(Color value) {
    return set_property(Property::outline_color, value);
  }

  Style &set_outline_color_filtered(Color value) {
    return set_property(Property::outline_color_filtered, value);
  }

  Style &set_outline_opacity(lv_opa_t value) {
    return set_property(Property::outline_opacity, value);
  }

  Style &set_outline_pad(lv_coord_t value) {
    return set_property(Property::outline_padding, value);
  }

  Style &set_shadow_width(lv_coord_t value) {
    return set_property(Property::shadow_width, value);
  }

  Style &set_shadow_x_offset(lv_coord_t value) {
    return set_property(Property::shadow_x_offset, value);
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OFS_X, v);
    return *this;
  }

  Style &set_shadow_y_offset(lv_coord_t value) {
    return set_property(Property::shadow_y_offset, value);
  }

  Style &set_shadow_spread(lv_coord_t value) {
    return set_property(Property::shadow_spread, value);
  }

  Style &set_shadow_color(Color value) {
    return set_property(Property::shadow_color, value);
  }

  Style &set_shadow_color_filtered(Color value) {
    return set_property(Property::shadow_color_filtered, value);
  }

  Style &set_shadow_opacity(lv_opa_t value) {
    return set_property(Property::shadow_opacity, value);
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->style_set_prop(&m_style, LV_STYLE_SHADOW_OPA, v);
    return *this;
  }

  Style &set_line_width(lv_coord_t value) {
    return set_property(Property::line_width, value);
  }

  Style &set_line_dash_width(lv_coord_t value) {
    return set_property(Property::line_dash_width, value);
  }

  Style &set_line_dash_gap(lv_coord_t value) {
    return set_property(Property::line_dash_gap, value);
  }

  Style &set_line_rounded(lv_coord_t value) {
    return set_property(Property::line_rounded, value);
  }

  Style &set_line_color(Color value) {
    return set_property(Property::line_color, value);
  }

  Style &set_line_color_filtered(Color value) {
    return set_property(Property::line_color_filtered, value);
  }

  Style &set_line_opacity(lv_opa_t value) {
    return set_property(Property::line_opacity, value);
  }

  Style &set_arc_width(lv_coord_t value) {
    return set_property(Property::arc_width, value);
  }

  Style &set_arc_rounded(lv_coord_t value) {
    return set_property(Property::arc_rounded, value);
  }

  Style &set_arc_color(Color value) {
    return set_property(Property::arc_color, value);
  }

  Style &set_arc_color_filtered(Color value) {
    return set_property(Property::arc_color_filtered, value);
  }

  Style &set_arc_opacity(lv_opa_t value) {
    return set_property(Property::arc_opacity, value);
  }

  Style &set_arc_image_source(const void *value) {
    return set_property(Property::arc_image_source, PropertyValue(value));
  }

  lv_style_t *style() { return &m_style; }
  const lv_style_t *style() const { return &m_style; }

private:
  friend class Object;
  lv_style_t m_style;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_STYLE_HPP
