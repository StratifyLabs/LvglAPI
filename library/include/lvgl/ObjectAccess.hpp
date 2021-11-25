#ifndef LVGLAPI_LVGL_OBJECTACCESS_HPP
#define LVGLAPI_LVGL_OBJECTACCESS_HPP

#include <var/StringView.hpp>

#include "Color.hpp"
#include "Object.hpp"
#include "Group.hpp"

namespace lvgl {

template <class Derived> class ObjectAccess : public Object {
public:

  Derived& add_to_group(Group & group){
    group.add(*this);
    return static_cast<Derived &>(*this);
  }


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

  Derived &fill_width() { return set_width(100_percent); }

  Derived &fill_height() { return set_height(100_percent); }

  Derived &fill() { return fill_width().fill_height(); }

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

  Derived &set_flex_layout() {
    api()->obj_set_layout(m_object, *api()->layout_flex);
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

  Derived &center() {
    api()->obj_set_align(m_object, static_cast<lv_align_t>(Alignment::center));
    return static_cast<Derived &>(*this);
  }

  Derived &set_alignment(Alignment alignment) {
    api()->obj_set_align(m_object, static_cast<lv_align_t>(alignment));
    return static_cast<Derived &>(*this);
  }

  Derived &set_alignment(Alignment alignment, const Point &offset) {
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
      is_ignore_floating == IsIgnoreFloating::yes);
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
      m_object, position.x(), position.y(), lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to(const Point &position, IsAnimate is_animate) {
    api()->obj_scroll_to(
      m_object, position.x(), position.y(), lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_x(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_x(m_object, value, lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_y(lv_coord_t value, IsAnimate is_animate) {
    api()->obj_scroll_to_y(m_object, value, lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view(IsAnimate is_animate) {
    api()->obj_scroll_to_view(m_object, lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &scroll_to_view_recursive(IsAnimate is_animate) {
    api()->obj_scroll_to_view_recursive(m_object, lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &update_snap(IsAnimate is_animate) {
    api()->obj_update_snap(m_object, lv_anim_enable_t(is_animate));
    return static_cast<Derived &>(*this);
  }

  Derived &invalidate_scrollbar() {
    api()->obj_scrollbar_invalidate(m_object);
    return static_cast<Derived &>(*this);
  }

  Derived &add_style(const Style &style, Selector selector = Selector()) {
    api()->obj_add_style(m_object, (lv_style_t *)style.style(), selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(const Style &style, Selector selector = Selector()) {
    api()->obj_remove_style(m_object, style.style(), selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(Selector selector) {
    api()->obj_remove_style(m_object, nullptr, selector.value());
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

  Derived &
  add_event_callback(EventCode event_code, void (*event_callback)(lv_event_t *)) {
    api()->obj_add_event_cb(
      m_object, event_callback, static_cast<lv_event_code_t>(event_code), nullptr);
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_flow(FlexFlow value) {
    api()->obj_set_flex_flow(m_object, static_cast<lv_flex_flow_t>(value));
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_grow(u8 value = 1) {
    api()->obj_set_flex_grow(m_object, value);
    return static_cast<Derived &>(*this);
  }

  Derived &set_flex_align(const SetFlexAlign &options) {
    api()->obj_set_flex_align(
      m_object, static_cast<lv_flex_align_t>(options.main()),
      static_cast<lv_flex_align_t>(options.cross()),
      static_cast<lv_flex_align_t>(options.track_cross()));
    return static_cast<Derived &>(*this);
  }

  Derived &set_minimum_width(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MIN_WIDTH, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_maximum_width(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MAX_WIDTH, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_minimum_height(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MIN_HEIGHT, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_maximum_height(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MAX_HEIGHT, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_align(Alignment value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = lv_align_t(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ALIGN, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_width(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_TRANSFORM_WIDTH, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_height(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_TRANSFORM_HEIGHT, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_translate_x(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSLATE_X, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_translate_y(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSLATE_Y, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_zoom(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_TRANSFORM_ZOOM, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_angle(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_TRANSFORM_ANGLE, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_top_padding(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_TOP, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_bottom_padding(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_BOTTOM, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_vertical_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_top_padding(value, selector).set_bottom_padding(value, selector);
  }

  Derived &set_left_padding(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_LEFT, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_right_padding(lv_coord_t value, Selector selector = Selector()) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_RIGHT, v, selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_horizontal_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_left_padding(value, selector).set_right_padding(value, selector);
  }

  Derived &set_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_vertical_padding(value, selector).set_horizontal_padding(value, selector);
  }

  Derived &
  set_property(Property property, PropertyValue value, Selector selector = Selector()) {
    api()->obj_set_local_style_prop(
      m_object, lv_style_prop_t(property), *value.style_value(), selector.value());
    return static_cast<Derived &>(*this);
  }

  Derived &set_row_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::row_padding, value, selector);
  }

  Derived &set_column_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::column_padding, value, selector);
  }

  Derived &set_radius(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::radius, value, selector);
  }

  Derived &set_clip_corner(bool value, Selector selector = Selector()) {
    return set_property(Property::clip_corner, value, selector);
  }

  Derived &set_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::opacity, lv_opa_t(value), selector);
  }

  Derived &set_color_filter_descriptor(
    const lv_color_filter_dsc_t *value,
    Selector selector = Selector()) {
    return set_property(
      Property::color_filter_descriptor, PropertyValue(value), selector);
  }

  Derived &set_color_filter_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::color_filter_opacity, lv_opa_t(value), selector);
  }

  Derived &
  set_animation_time(const chrono::MicroTime value, Selector selector = Selector()) {
    return set_property(Property::animation_time, s32(value.milliseconds()), selector);
  }

  Derived &set_animation_speed(uint32_t value, Selector selector = Selector()) {
    return set_property(Property::animation_speed, value, selector);
  }

  Derived &
  set_transition(const lv_style_transition_dsc_t *value, Selector selector = Selector()) {
    return set_property(Property::transition, value, selector);
  }

  Derived &set_blend_mode(lv_blend_mode_t value, Selector selector = Selector()) {
    return set_property(Property::blend_mode, value, selector);
  }

  Derived &set_layout(uint16_t value, Selector selector) {
    return set_property(Property::layout, value, selector);
  }

  Derived &set_base_dir(BaseDirection value, Selector selector = Selector()) {
    return set_property(Property::base_direction, value, selector);
  }

  Derived &set_background_color(const Color &value, Selector selector = Selector()) {
    return set_property(Property::background_color, value, selector);
  }

  Derived &
  set_background_color_filtered(const Color &value, Selector selector = Selector()) {
    return set_property(Property::background_color_filtered, value, selector);
  }

  Derived &set_background_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::background_opacity, lv_opa_t(value), selector);
  }

  Derived &
  set_background_gradient_color(const Color &value, Selector selector = Selector()) {
    return set_property(Property::background_gradient_color, value, selector);
  }

  Derived &set_background_gradient_color_filtered(
    const Color &value,
    Selector selector = Selector()) {
    return set_property(Property::background_gradient_color_filtered, value, selector);
  }

  Derived &set_background_gradient_direction(
    GradientDirection value,
    Selector selector = Selector()) {
    return set_property(Property::background_gradient_direction, value, selector);
  }

  Derived &set_background_main_stop(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::background_main_stop, value, selector);
  }

  Derived &
  set_background_gradient_stop(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::background_gradient_stop, value, selector);
  }

  Derived &
  set_background_image_source(const void *value, Selector selector = Selector()) {
    return set_property(Property::background_image_source, value, selector);
  }

  Derived &set_background_image_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::background_image_opacity, lv_opa_t(value), selector);
  }

  Derived &set_background_image_recolor(Color value, Selector selector = Selector()) {
    return set_property(Property::background_image_recolor, value, selector);
  }

  Derived &
  set_background_image_recolor_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::background_image_recolor_filtered, value, selector);
  }

  Derived &
  set_background_image_recolor_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(
      Property::background_image_recolor_opacity, lv_opa_t(value), selector);
  }

  Derived &set_background_image_tiled(bool value, Selector selector = Selector()) {
    return set_property(Property::background_image_tiled, value, selector);
  }

  Derived &set_border_color(Color value, Selector selector = Selector()) {
    return set_property(Property::border_color, value, selector);
  }

  Derived &set_border_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::border_color_filtered, value, selector);
  }

  Derived &set_border_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::border_opacity, lv_opa_t(value), selector);
  }

  Derived &set_border_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::border_width, value, selector);
  }

  Derived &set_border_side(BorderSide value, Selector selector = Selector()) {
    return set_property(Property::border_side, s32(value), selector);
  }

  Derived &set_border_post(bool value, Selector selector = Selector()) {
    return set_property(Property::border_post, value, selector);
  }

  Derived &set_text_color(Color value, Selector selector = Selector()) {
    return set_property(Property::text_color, value, selector);
  }

  Derived &set_text_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::text_color_filtered, value, selector);
  }

  Derived &set_text_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::text_opacity, lv_opa_t(value), selector);
  }

  Derived &set_text_font(const Font &value, Selector selector = Selector()) {
    return set_property(Property::text_font, PropertyValue(value.font()), selector);
  }

  Derived &set_text_font(const Font::Info &value, Selector selector = Selector()) {
    return set_text_font(value.get_font(), selector);
  }

  Derived &set_text_letter_space(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::text_letter_spacing, value, selector);
  }

  Derived &set_text_line_space(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::text_line_spacing, value, selector);
  }

  Derived &set_text_decor(TextDecoration value, Selector selector = Selector()) {
    return set_property(Property::text_decoration, value, selector);
  }

  Derived &set_text_alignment(TextAlignment value, Selector selector = Selector()) {
    return set_property(Property::text_alignment, s32(value), selector);
  }

  Derived &set_image_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::image_opacity, lv_opa_t(value), selector);
  }

  Derived &set_image_recolor(Color value, Selector selector = Selector()) {
    return set_property(Property::image_recolor, value, selector);
  }

  Derived &set_image_recolor_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::image_recolor_filtered, value, selector);
  }

  Derived &set_image_recolor_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::image_recolor_opacity, lv_opa_t(value), selector);
  }

  Derived &set_outline_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::outline_width, value, selector);
  }

  Derived &set_outline_color(Color value, Selector selector = Selector()) {
    return set_property(Property::outline_color, value, selector);
  }

  Derived &set_outline_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::outline_color_filtered, value, selector);
  }

  Derived &set_outline_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::outline_opacity, lv_opa_t(value), selector);
  }

  Derived &set_outline_padding(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::outline_padding, value, selector);
  }

  Derived &set_shadow_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::shadow_width, value, selector);
  }

  Derived &set_shadow_x_offset(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::shadow_x_offset, value, selector);
  }

  Derived &set_shadow_y_offset(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::shadow_y_offset, value, selector);
  }

  Derived &set_shadow_spread(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::shadow_spread, value, selector);
  }

  Derived &set_shadow_color(Color value, Selector selector = Selector()) {
    return set_property(Property::shadow_color, value, selector);
  }

  Derived &set_shadow_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::shadow_color_filtered, value, selector);
  }

  Derived &set_shadow_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::shadow_opacity, lv_opa_t(value), selector);
  }

  Derived &set_line_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::line_width, value, selector);
  }

  Derived &set_line_dash_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::line_dash_width, value, selector);
  }

  Derived &set_line_dash_gap(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::line_dash_gap, value, selector);
  }

  Derived &set_line_rounded(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::line_rounded, value, selector);
  }

  Derived &set_line_color(Color value, Selector selector = Selector()) {
    return set_property(Property::line_color, value, selector);
  }

  Derived &set_line_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::line_color_filtered, value, selector);
  }

  Derived &set_line_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::line_opacity, lv_opa_t(value), selector);
  }

  Derived &set_arc_width(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::arc_width, value, selector);
  }

  Derived &set_arc_rounded(lv_coord_t value, Selector selector = Selector()) {
    return set_property(Property::arc_rounded, value, selector);
  }

  Derived &set_arc_color(Color value, Selector selector = Selector()) {
    return set_property(Property::arc_color, value, selector);
  }

  Derived &set_arc_color_filtered(Color value, Selector selector = Selector()) {
    return set_property(Property::arc_color_filtered, value, selector);
  }

  Derived &set_arc_opacity(Opacity value, Selector selector = Selector()) {
    return set_property(Property::arc_opacity, lv_opa_t(value), selector);
  }

  Derived &set_arc_image_source(const void *value, Selector selector = Selector()) {
    return set_property(Property::arc_image_source, value, selector);
  }

  template <typename ChildClass> Derived &add(const ChildClass &child) {
    api()->obj_set_parent(child.object(), m_object);
    auto setup = child.get_setup();
    if (setup) {
      setup(child);
    }
    return static_cast<Derived &>(*this);
  }

  Derived &setup(void (*configure)(Derived)) {
    m_setup = configure;
    // configure(Derived(m_object));
    return static_cast<Derived &>(*this);
  }

  Derived &send_alert(Object receiver) {
    api()->event_send(receiver.object(), LV_EVENT_READY, this);
    return static_cast<Derived &>(*this);
  }

  const Derived &send_alert(Object receiver) const {
    api()->event_send(receiver.object(), LV_EVENT_READY, this);
    return static_cast<const Derived &>(*this);
  }

  Derived &remove_children() {
    const auto child_count = get_child_count();
    for (s32 i = 0; i < child_count; i++) {
      get_child(i).remove();
    }
    return static_cast<Derived &>(*this);
  }

  using Callback = void (*)(Derived);

  Callback get_setup() const { return m_setup; }

private:
  Callback m_setup = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_OBJECTACCESS_HPP
