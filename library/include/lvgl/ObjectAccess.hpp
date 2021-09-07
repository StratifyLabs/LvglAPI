#ifndef LVGLAPI_LVGL_OBJECTACCESS_HPP
#define LVGLAPI_LVGL_OBJECTACCESS_HPP

#include <var/StringView.hpp>

#include "Object.hpp"

namespace lvgl {

template <class Derived> class ObjectAccess : public Object {
public:
  ObjectAccess<Derived>() = default;
  ObjectAccess<Derived>(u32 type) {}
  ObjectAccess<Derived>(const char *name) : m_initial_name(name) {}

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

  Derived &add_style(const Style &style, lv_style_selector_t style_selector = 0) {
    api()->obj_add_style(m_object, (lv_style_t *)style.style(), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(const Style &style, lv_style_selector_t style_selector) {
    api()->obj_remove_style(m_object, style.style(), style_selector);
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(Part part) {
    api()->obj_remove_style(m_object, nullptr, static_cast<lv_style_selector_t>(part));
    return static_cast<Derived &>(*this);
  }

  Derived &remove_style(lv_style_selector_t style_selector) {
    api()->obj_remove_style(m_object, nullptr, style_selector);
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

  Derived &set_flex_grow(u8 value) {
    api()->obj_set_flex_grow(m_object, value);
    return static_cast<Derived &>(*this);
  }

  class SetFlexAlign {
    API_AF(SetFlexAlign, FlexAlign, main, FlexAlign::space_around);
    API_AF(SetFlexAlign, FlexAlign, cross, FlexAlign::center);
    API_AF(SetFlexAlign, FlexAlign, track_cross, FlexAlign::space_around);
  };

  Derived &set_flex_align(const SetFlexAlign &options) {
    api()->obj_set_flex_align(
      m_object, static_cast<lv_flex_align_t>(options.main()),
      static_cast<lv_flex_align_t>(options.cross()),
      static_cast<lv_flex_align_t>(options.track_cross()));
    return static_cast<Derived &>(*this);
  }

  Derived &set_min_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MIN_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_max_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MAX_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_min_height(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MIN_HEIGHT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_max_height(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_MAX_HEIGHT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_align(Alignment value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = lv_align_t(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ALIGN, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSFORM_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_height(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSFORM_HEIGHT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_translate_x(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSLATE_X, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_translate_y(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSLATE_Y, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_zoom(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSFORM_ZOOM, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_transform_angle(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSFORM_ANGLE, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_top_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_TOP, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bottom_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_BOTTOM, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_vertical_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    return set_top_padding(value, selector).set_bottom_padding(value, selector);
  }

  Derived &set_left_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_LEFT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_right_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_RIGHT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_horizontal_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    return set_left_padding(value, selector).set_right_padding(value, selector);
  }

  Derived &set_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    return set_vertical_padding(value, selector).set_horizontal_padding(value, selector);
  }

  Derived &set_row_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_ROW, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_column_padding(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_PAD_COLUMN, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_radius(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_RADIUS, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_clip_corner(bool value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_CLIP_CORNER, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_color_filter_descriptor(
    const lv_color_filter_dsc_t *value,
    lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.ptr = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_COLOR_FILTER_DSC, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_color_filter_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_COLOR_FILTER_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_anim_time(uint32_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ANIM_TIME, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_anim_speed(uint32_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ANIM_SPEED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_transition(
    const lv_style_transition_dsc_t *value,
    lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.ptr = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TRANSITION, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_blend_mode(lv_blend_mode_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BLEND_MODE, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_layout(uint16_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LAYOUT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_base_dir(BaseDirection value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BASE_DIR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_grad_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_GRAD_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &
  set_bg_grad_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_BG_GRAD_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_grad_dir(GradientDirection value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_GRAD_DIR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_main_stop(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_MAIN_STOP, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_bg_grad_stop(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_GRAD_STOP, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &
  set_background_image_source(const void *value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.ptr = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_IMG_SRC, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_background_image_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_IMG_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &
  set_background_image_recolor(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_IMG_RECOLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_background_image_recolor_filtered(
    lv_color_t value,
    lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_BG_IMG_RECOLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &
  set_background_image_recolor_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_IMG_RECOLOR_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_background_image_tiled(bool value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BG_IMG_TILED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BORDER_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_BORDER_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BORDER_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BORDER_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_side(BorderSide value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BORDER_SIDE, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_border_post(bool value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_BORDER_POST, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_font(const Font &value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.ptr = value.font()};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_FONT, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_letter_space(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_LETTER_SPACE, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_line_space(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_LINE_SPACE, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_decor(TextDecoration value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_DECOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_text_align(TextAlignment value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_TEXT_ALIGN, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_img_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_IMG_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_img_recolor(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_IMG_RECOLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_img_recolor_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_IMG_RECOLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_IMG_RECOLOR_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_outline_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_OUTLINE_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_outline_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_OUTLINE_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &
  set_outline_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_OUTLINE_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_outline_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_OUTLINE_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_outline_pad(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_OUTLINE_PAD, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_ofs_x(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_OFS_X, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_ofs_y(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_OFS_Y, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_spread(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_SPREAD, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(
      m_object, LV_STYLE_SHADOW_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_shadow_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_SHADOW_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_dash_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_DASH_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_dash_gap(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_DASH_GAP, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_rounded(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_ROUNDED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_line_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_LINE_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_width(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_WIDTH, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_rounded(lv_coord_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_ROUNDED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_color(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_COLOR, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_color_filtered(lv_color_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.color = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_COLOR_FILTERED, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_opa(lv_opa_t value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.num = static_cast<int32_t>(value)};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_OPA, v, selector);
    return static_cast<Derived &>(*this);
  }

  Derived &set_arc_img_src(const void *value, lv_style_selector_t selector = 0) {
    lv_style_value_t v = {.ptr = value};
    api()->obj_set_local_style_prop(m_object, LV_STYLE_ARC_IMG_SRC, v, selector);
    return static_cast<Derived &>(*this);
  }

  template <typename ChildClass> Derived &add(const typename ChildClass::Create &create) {
    ChildClass child(*this, create);
    if (create.initialize()) {
      create.initialize()(child);
    }
    return static_cast<Derived &>(*this);
  }

  template <typename ChildClass> Derived &add(const ChildClass &child) {
    ChildClass new_child(*this, child);
    new_child.set_name(child.initial_name());
    if (child.initialize()) {
      child.initialize()(new_child);
    }
    return static_cast<Derived &>(*this);
  }

#if 0
  template <typename ChildClass> Derived &add(const ChildClass & child) {
    ChildClass new_child(*this, child);
    new_child.set_name(child.initial_name());
    if (child.initialize()) {
      child.initialize()(new_child);
    }
    return static_cast<Derived &>(*this);
  }
#endif

  static u32 object_type() { return reinterpret_cast<size_t>(object_type); }

  Derived &send_alert(Object receiver) {
    api()->event_send(receiver.object(), LV_EVENT_READY, this);
    return static_cast<Derived &>(*this);
  }

  const Derived &send_alert(Object receiver) const {
    api()->event_send(receiver.object(), LV_EVENT_READY, this);
    return static_cast<const Derived &>(*this);
  }

  using Callback = void (*)(Derived &);
  Callback initialize() const { return m_initialize; }

  Derived &configure(Callback callback) {
    m_initialize = callback;
    return static_cast<Derived &>(*this);
  }

  const char *initial_name() const { return m_initial_name; }

private:
  Callback m_initialize = nullptr;
  const char *m_initial_name = nullptr;
};

#define OBJECT_ACCESS_FORWARD_FRIENDS()                                                  \
  class Container;                                                                       \
  class Window;                                                                          \
  class Button;                                                                          \
  class MessageBox;                                                                          \
  class TileView

#define OBJECT_ACCESS_FRIENDS()                                                          \
  friend class ObjectAccess<Container>;                                                  \
  friend class ObjectAccess<Window>;                                                     \
  friend class ObjectAccess<TileView>;                                                   \
  friend class ObjectAccess<Button>;                                                     \
  friend class ObjectAccess<MessageBox>;                                                     \
  friend class Object;

} // namespace lvgl

#endif // LVGLAPI_LVGL_OBJECT_HPP
