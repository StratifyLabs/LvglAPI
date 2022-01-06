#include "lvgl.h"
#include "lvgl_api.h"

const lvgl_api_font_descriptor_t *lvgl_api_get_font(int offset);
const lvgl_api_image_descriptor_t *lvgl_api_get_image(int offset);
const lvgl_api_theme_descriptor_t *lvgl_api_get_theme(int offset);

const lvgl_api_t lvgl_api = {
  .sos_api =
    {
      .name = "lvgl",
      .version = LVGL_API_VERSION,
      .git_hash = SOS_GIT_HASH,
    },

  .timer_handler = lv_timer_handler,
  .tick_inc = lv_tick_inc,

  .event_send = lv_event_send,
  .obj_event_base = lv_obj_event_base,
  .event_get_target = lv_event_get_target,
  .event_get_current_target = lv_event_get_current_target,
  .event_get_code = lv_event_get_code,
  .event_get_param = lv_event_get_param,
  .event_get_user_data = lv_event_get_user_data,
  .event_register_id = lv_event_register_id,
  .obj_add_event_cb = lv_obj_add_event_cb,
  .obj_remove_event_cb = lv_obj_remove_event_cb,
  .obj_remove_event_dsc = lv_obj_remove_event_dsc,
  .event_get_indev = lv_event_get_indev,
  .event_get_draw_part_dsc = lv_event_get_draw_part_dsc,
  .event_get_clip_area = lv_event_get_clip_area,
  .event_get_old_size = lv_event_get_old_size,
  .event_get_key = lv_event_get_key,
  .event_set_ext_draw_size = lv_event_set_ext_draw_size,
  .event_get_self_size_info = lv_event_get_self_size_info,
  .event_get_hit_test_info = lv_event_get_hit_test_info,
  .event_get_cover_area = lv_event_get_cover_area,
  .event_set_cover_res = lv_event_set_cover_res,

  .obj_create = lv_obj_create,
  .obj_add_flag = lv_obj_add_flag,
  .obj_clear_flag = lv_obj_clear_flag,
  .obj_add_state = lv_obj_add_state,
  .obj_clear_state = lv_obj_clear_state,
  .obj_has_flag = lv_obj_has_flag,
  .obj_has_flag_any = lv_obj_has_flag_any,
  .obj_get_state = lv_obj_get_state,
  .obj_has_state = lv_obj_has_state,
  .obj_get_group = lv_obj_get_group,
  .obj_allocate_spec_attr = lv_obj_allocate_spec_attr,
  .obj_check_type = lv_obj_check_type,
  .obj_has_class = lv_obj_has_class,
  .obj_get_class = lv_obj_get_class,
  .obj_is_valid = lv_obj_is_valid,

  // obj pos
  .obj_set_pos = lv_obj_set_pos,
  .obj_set_x = lv_obj_set_x,
  .obj_set_y = lv_obj_set_y,
  .obj_set_size = lv_obj_set_size,
  .obj_refr_size = lv_obj_refr_size,
  .obj_set_width = lv_obj_set_width,
  .obj_set_height = lv_obj_set_height,
  .obj_set_content_width = lv_obj_set_content_width,
  .obj_set_content_height = lv_obj_set_content_height,
  .obj_set_layout = lv_obj_set_layout,
  .obj_is_layout_positioned = lv_obj_is_layout_positioned,
  .obj_mark_layout_as_dirty = lv_obj_mark_layout_as_dirty,
  .obj_update_layout = lv_obj_update_layout,
  .layout_register = lv_layout_register,
  .obj_set_align = lv_obj_set_align,
  .obj_align = lv_obj_align,
  .obj_align_to = lv_obj_align_to,
  .obj_get_coords = lv_obj_get_coords,
  .obj_get_x = lv_obj_get_x,
  .obj_get_x2 = lv_obj_get_x2,
  .obj_get_y = lv_obj_get_y,
  .obj_get_y2 = lv_obj_get_y2,
  .obj_get_width = lv_obj_get_width,
  .obj_get_height = lv_obj_get_height,
  .obj_get_content_width = lv_obj_get_content_width,
  .obj_get_content_height = lv_obj_get_content_height,
  .obj_get_content_coords = lv_obj_get_content_coords,
  .obj_get_self_width = lv_obj_get_self_width,
  .obj_get_self_height = lv_obj_get_self_height,
  .obj_refresh_self_size = lv_obj_refresh_self_size,
  .obj_refr_pos = lv_obj_refr_pos,
  .obj_move_to = lv_obj_move_to,
  .obj_move_children_by = lv_obj_move_children_by,
  .obj_invalidate_area = lv_obj_invalidate_area,
  .obj_invalidate = lv_obj_invalidate,
  .obj_area_is_visible = lv_obj_area_is_visible,
  .obj_is_visible = lv_obj_is_visible,
  .obj_set_ext_click_area = lv_obj_set_ext_click_area,
  .obj_get_click_area = lv_obj_get_click_area,
  .obj_hit_test = lv_obj_hit_test,
  .clamp_width = lv_clamp_width,
  .clamp_height = lv_clamp_height,

  .layout_flex = &LV_LAYOUT_FLEX,
  .style_flex_flow = &LV_STYLE_FLEX_FLOW,
  .style_flex_main_place = &LV_STYLE_FLEX_MAIN_PLACE,
  .style_flex_cross_place = &LV_STYLE_FLEX_CROSS_PLACE,
  .style_flex_track_place = &LV_STYLE_FLEX_TRACK_PLACE,
  .style_flex_grow = &LV_STYLE_FLEX_GROW,

  // obj scroll
  .obj_set_scrollbar_mode = lv_obj_set_scrollbar_mode,
  .obj_set_scroll_dir = lv_obj_set_scroll_dir,
  .obj_set_scroll_snap_x = lv_obj_set_scroll_snap_x,
  .obj_set_scroll_snap_y = lv_obj_set_scroll_snap_y,
  .obj_get_scrollbar_mode = lv_obj_get_scrollbar_mode,
  .obj_get_scroll_dir = lv_obj_get_scroll_dir,
  .obj_get_scroll_snap_x = lv_obj_get_scroll_snap_x,
  .obj_get_scroll_snap_y = lv_obj_get_scroll_snap_y,
  .obj_get_scroll_x = lv_obj_get_scroll_x,
  .obj_get_scroll_y = lv_obj_get_scroll_y,
  .obj_get_scroll_top = lv_obj_get_scroll_top,
  .obj_get_scroll_bottom = lv_obj_get_scroll_bottom,
  .obj_get_scroll_left = lv_obj_get_scroll_bottom,
  .obj_get_scroll_right = lv_obj_get_scroll_right,
  .obj_get_scroll_end = lv_obj_get_scroll_end,
  .obj_scroll_by = lv_obj_scroll_by,
  .obj_scroll_to = lv_obj_scroll_to,
  .obj_scroll_to_x = lv_obj_scroll_to_x,
  .obj_scroll_to_y = lv_obj_scroll_to_y,
  .obj_scroll_to_view = lv_obj_scroll_to_view,
  .obj_scroll_to_view_recursive = lv_obj_scroll_to_view_recursive,
  .obj_is_scrolling = lv_obj_is_scrolling,
  .obj_update_snap = lv_obj_update_snap,
  .obj_get_scrollbar_area = lv_obj_get_scrollbar_area,
  .obj_scrollbar_invalidate = lv_obj_scrollbar_invalidate,

  // obj style
  .obj_add_style = lv_obj_add_style,
  .obj_remove_style = lv_obj_remove_style,
  .obj_report_style_change = lv_obj_report_style_change,
  .obj_refresh_style = lv_obj_refresh_style,
  .obj_enable_style_refresh = lv_obj_enable_style_refresh,
  .obj_get_style_prop = lv_obj_get_style_prop,
  .obj_set_local_style_prop = lv_obj_set_local_style_prop,
  .obj_get_local_style_prop = lv_obj_get_local_style_prop,
  .obj_remove_local_style_prop = lv_obj_remove_local_style_prop,
  .obj_fade_in = lv_obj_fade_in,
  .obj_fade_out = lv_obj_fade_out,
  .obj_style_get_selector_state = lv_obj_style_get_selector_state,
  .obj_style_get_selector_part = lv_obj_style_get_selector_part,

  // obj tree
  .obj_del = lv_obj_del,
  .obj_clean = lv_obj_clean,
  .obj_del_anim_ready_cb = lv_obj_del_anim_ready_cb,
  .obj_del_async = lv_obj_del_async,
  .obj_del_delayed = lv_obj_del_delayed,
  .obj_set_parent = lv_obj_set_parent,
  .obj_move_foreground = lv_obj_move_foreground,
  .obj_move_background = lv_obj_move_background,
  .obj_get_screen = lv_obj_get_screen,
  .obj_get_disp = lv_obj_get_disp,
  .obj_get_parent = lv_obj_get_parent,
  .obj_get_child = lv_obj_get_child,
  .obj_get_child_cnt = lv_obj_get_child_cnt,
  .obj_get_index = lv_obj_get_index,
  .obj_tree_walk = lv_obj_tree_walk,

  // obj class
  .obj_class_init_obj = lv_obj_class_init_obj,
  .obj_is_editable = lv_obj_is_editable,
  .obj_is_group_def = lv_obj_is_group_def,

  // group
  .group_create = lv_group_create,
  .group_del = lv_group_del,
  .group_set_default = lv_group_set_default,
  .group_get_default = lv_group_get_default,
  .group_add_obj = lv_group_add_obj,
  .group_remove_obj = lv_group_remove_obj,
  .group_remove_all_objs = lv_group_remove_all_objs,
  .group_focus_obj = lv_group_focus_obj,
  .group_focus_next = lv_group_focus_next,
  .group_focus_prev = lv_group_focus_prev,
  .group_focus_freeze = lv_group_focus_freeze,
  .group_send_data = lv_group_send_data,
  .group_set_focus_cb = lv_group_set_focus_cb,
  .group_set_refocus_policy = lv_group_set_refocus_policy,
  .group_set_editing = lv_group_set_editing,
  .group_set_wrap = lv_group_set_wrap,
  .group_get_focused = lv_group_get_focused,
  .group_get_focus_cb = lv_group_get_focus_cb,
  .group_get_editing = lv_group_get_editing,
  .group_get_wrap = lv_group_get_wrap,
  .group_get_obj_count = lv_group_get_obj_count,

  // indev
  .indev_read_timer_cb = lv_indev_read_timer_cb,
  .indev_enable = lv_indev_enable,
  .indev_get_act = lv_indev_get_act,
  .indev_get_type = lv_indev_get_type,
  .indev_reset = lv_indev_reset,
  .indev_reset_long_press = lv_indev_reset_long_press,
  .indev_set_cursor = lv_indev_set_cursor,
  .indev_set_group = lv_indev_set_group,
  .indev_set_button_points = lv_indev_set_button_points,
  .indev_get_point = lv_indev_get_point,
  .indev_get_gesture_dir = lv_indev_get_gesture_dir,
  .indev_get_key = lv_indev_get_key,
  .indev_get_scroll_dir = lv_indev_get_scroll_dir,
  .indev_get_scroll_obj = lv_indev_get_scroll_obj,
  .indev_get_vect = lv_indev_get_vect,
  .indev_wait_release = lv_indev_wait_release,
  .indev_get_obj_act = lv_indev_get_obj_act,
  .indev_get_read_timer = lv_indev_get_read_timer,
  .indev_search_obj = lv_indev_search_obj,

  // misc
  // misc/anim
  .anim_init = lv_anim_init,
  .anim_start = lv_anim_start,
  .anim_del = lv_anim_del,
  .anim_del_all = lv_anim_del_all,
  .anim_get = lv_anim_get,
  .anim_count_running = lv_anim_count_running,
  .anim_speed_to_time = lv_anim_speed_to_time,
  .anim_refr_now = lv_anim_refr_now,
  .anim_path_linear = lv_anim_path_linear,
  .anim_path_ease_in = lv_anim_path_ease_in,
  .anim_path_ease_out = lv_anim_path_ease_out,
  .anim_path_ease_in_out = lv_anim_path_ease_in_out,
  .anim_path_overshoot = lv_anim_path_overshoot,
  .anim_path_bounce = lv_anim_path_bounce,
  .anim_path_step = lv_anim_path_step,
  // misc/area
  .area_set_width = lv_area_set_width,
  .area_set_height = lv_area_set_height,
  .area_get_size = lv_area_get_size,
  .area_increase = lv_area_increase,
  .area_move = lv_area_move,
  .area_align = lv_area_align,
  // misc/color
  .color_fill = lv_color_fill,
  .color_lighten = lv_color_lighten,
  .color_darken = lv_color_darken,
  .color_change_lightness = lv_color_change_lightness,
  .color_hsv_to_rgb = lv_color_hsv_to_rgb,
  .color_rgb_to_hsv = lv_color_rgb_to_hsv,
  .color_to_hsv = lv_color_to_hsv,
  .palette_main = lv_palette_main,
  .palette_lighten = lv_palette_lighten,
  .palette_darken = lv_palette_darken,
  // misc/fs
  .fs_drv_init = lv_fs_drv_init,
  .fs_drv_register = lv_fs_drv_register,
  .fs_get_drv = lv_fs_get_drv,
  .fs_is_ready = lv_fs_is_ready,
  .fs_open = lv_fs_open,
  .fs_close = lv_fs_close,
  .fs_read = lv_fs_read,
  .fs_write = lv_fs_write,
  .fs_seek = lv_fs_seek,
  .fs_tell = lv_fs_tell,
  .fs_dir_open = lv_fs_dir_open,
  .fs_dir_read = lv_fs_dir_read,
  .fs_dir_close = lv_fs_dir_close,
  .fs_get_letters = lv_fs_get_letters,
  .fs_get_ext = lv_fs_get_ext,
  .fs_up = lv_fs_up,
  .fs_get_last = lv_fs_get_last,
  // misc/math
  .bezier3 = lv_bezier3,
  .atan2 = lv_atan2,
  .sqrt = lv_sqrt,
  .pow = lv_pow,
  .map = lv_map,
  .rand = lv_rand,
  // misc/mem
  .mem_init = lv_mem_init,
  .mem_deinit = lv_mem_deinit,
  ._mem_alloc = 0,
  .mem_free = lv_mem_free,
  .mem_realloc = lv_mem_realloc,
  .mem_test = lv_mem_test,
  .mem_monitor = lv_mem_monitor,
  .mem_buf_get = lv_mem_buf_get,
  .mem_buf_release = lv_mem_buf_release,
  .mem_buf_free_all = lv_mem_buf_free_all,
  // misc/style
  .style_init = lv_style_init,
  .style_reset = lv_style_reset,
  .style_register_prop = lv_style_register_prop,
  .style_remove_prop = lv_style_remove_prop,
  .style_set_prop = lv_style_set_prop,
  .style_get_prop = lv_style_get_prop,
  .style_transition_dsc_init = lv_style_transition_dsc_init,
  .style_prop_get_default = lv_style_prop_get_default,
  .style_is_empty = lv_style_is_empty,
  // misc/timer
  .timer_create_basic = lv_timer_create_basic,
  .timer_create = lv_timer_create,
  .timer_del = lv_timer_del,
  .timer_pause = lv_timer_pause,
  .timer_resume = lv_timer_resume,
  .timer_set_cb = lv_timer_set_cb,
  .timer_set_period = lv_timer_set_period,
  .timer_ready = lv_timer_ready,
  .timer_set_repeat_count = lv_timer_set_repeat_count,
  .timer_reset = lv_timer_reset,
  .timer_enable = lv_timer_enable,
  .timer_get_idle = lv_timer_get_idle,
  .timer_get_next = lv_timer_get_next,

  // refresh
  .refr_now = lv_refr_now,

  // disp
  .disp_get_scr_act = lv_disp_get_scr_act,
  .disp_get_scr_prev = lv_disp_get_scr_prev,
  .disp_load_scr = lv_disp_load_scr,
  .disp_get_layer_top = lv_disp_get_layer_top,
  .disp_get_layer_sys = lv_disp_get_layer_sys,
  .disp_set_theme = lv_disp_set_theme,
  .disp_get_theme = lv_disp_get_theme,
  .disp_set_bg_color = lv_disp_set_bg_color,
  .disp_set_bg_image = lv_disp_set_bg_image,
  .disp_set_bg_opa = lv_disp_set_bg_opa,
  .scr_load_anim = lv_scr_load_anim,
  .disp_get_inactive_time = lv_disp_get_inactive_time,
  .disp_trig_activity = lv_disp_trig_activity,
  .disp_clean_dcache = lv_disp_clean_dcache,

  .disp_drv_update = lv_disp_drv_update,
  .disp_remove = lv_disp_remove,
  .disp_set_default = lv_disp_set_default,
  .disp_get_default = lv_disp_get_default,
  .disp_get_hor_res = lv_disp_get_hor_res,
  .disp_get_ver_res = lv_disp_get_ver_res,
  .disp_get_antialiasing = lv_disp_get_antialiasing,
  .disp_get_dpi = lv_disp_get_dpi,
  .disp_set_rotation = lv_disp_set_rotation,
  .disp_get_rotation = lv_disp_get_rotation,

  // theme
  .theme_get_from_obj = lv_theme_get_from_obj,
  .theme_apply = lv_theme_apply,
  .theme_set_parent = lv_theme_set_parent,
  .theme_set_apply_cb = lv_theme_set_apply_cb,
  .theme_get_font_small = lv_theme_get_font_small,
  .theme_get_font_normal = lv_theme_get_font_normal,
  .theme_get_font_large = lv_theme_get_font_large,
  .theme_get_color_primary = lv_theme_get_color_primary,
  .theme_get_color_secondary = lv_theme_get_color_secondary,

  // font
  .font_get_glyph_bitmap = lv_font_get_glyph_bitmap,
  .font_get_glyph_dsc = lv_font_get_glyph_dsc,
  .font_get_glyph_width = lv_font_get_glyph_width,

  // font loader
  .font_load = lv_font_load,
  .font_free = lv_font_free,

  // font fmt txt
  .font_get_bitmap_fmt_txt = lv_font_get_bitmap_fmt_txt,
  .font_get_glyph_dsc_fmt_txt = lv_font_get_glyph_dsc_fmt_txt,

  // widgets

  // arc
  .arc_create = lv_arc_create,
  .arc_set_start_angle = lv_arc_set_start_angle,
  .arc_set_end_angle = lv_arc_set_end_angle,
  .arc_set_angles = lv_arc_set_angles,
  .arc_set_bg_start_angle = lv_arc_set_bg_start_angle,
  .arc_set_bg_end_angle = lv_arc_set_bg_end_angle,
  .arc_set_bg_angles = lv_arc_set_bg_angles,
  .arc_set_rotation = lv_arc_set_rotation,
  .arc_set_mode = lv_arc_set_mode,
  .arc_set_value = lv_arc_set_value,
  .arc_set_range = lv_arc_set_range,
  .arc_set_change_rate = lv_arc_set_change_rate,
  .arc_get_angle_start = lv_arc_get_angle_start,
  .arc_get_angle_end = lv_arc_get_angle_end,
  .arc_get_bg_angle_start = lv_arc_get_bg_angle_start,
  .arc_get_bg_angle_end = lv_arc_get_bg_angle_end,
  .arc_get_value = lv_arc_get_value,
  .arc_get_min_value = lv_arc_get_min_value,
  .arc_get_max_value = lv_arc_get_max_value,
  .arc_get_mode = lv_arc_get_mode,

  // button
  .btn_create = lv_btn_create,

  // img
  .img_create = lv_img_create,
  .img_set_src = lv_img_set_src,
  .img_set_offset_x = lv_img_set_offset_x,
  .img_set_offset_y = lv_img_set_offset_y,
  .img_set_angle = lv_img_set_angle,
  .img_set_pivot = lv_img_set_pivot,
  .img_set_zoom = lv_img_set_zoom,
  .img_set_antialias = lv_img_set_antialias,
  .img_get_src = lv_img_get_src,
  .img_get_offset_x = lv_img_get_offset_x,
  .img_get_offset_y = lv_img_get_offset_y,
  .img_get_angle = lv_img_get_angle,
  .img_get_pivot = lv_img_get_pivot,
  .img_get_zoom = lv_img_get_zoom,
  .img_get_antialias = lv_img_get_antialias,

  // label
  .label_create = lv_label_create,
  .label_set_text = lv_label_set_text,
  .label_set_text_fmt = lv_label_set_text_fmt,
  .label_set_text_static = lv_label_set_text_static,
  .label_set_long_mode = lv_label_set_long_mode,
  .label_set_recolor = lv_label_set_recolor,
  .label_set_text_sel_start = lv_label_set_text_sel_start,
  .label_set_text_sel_end = lv_label_set_text_sel_end,
  .label_get_text = lv_label_get_text,
  .label_get_long_mode = lv_label_get_long_mode,
  .label_get_recolor = lv_label_get_recolor,
  .label_get_letter_pos = lv_label_get_letter_pos,
  .label_get_letter_on = lv_label_get_letter_on,
  .label_is_char_under_pos = lv_label_is_char_under_pos,
  .label_get_text_selection_start = lv_label_get_text_selection_start,
  .label_get_text_selection_end = lv_label_get_text_selection_end,
  .label_ins_text = lv_label_ins_text,
  .label_cut_text = lv_label_cut_text,

  // line
  .line_create = lv_line_create,
  .line_set_points = lv_line_set_points,
  .line_set_y_invert = lv_line_set_y_invert,
  .line_get_y_invert = lv_line_get_y_invert,

  // table
  .table_create = lv_table_create,
  .table_set_cell_value = lv_table_set_cell_value,
  .table_set_cell_value_fmt = lv_table_set_cell_value_fmt,
  .table_set_row_cnt = lv_table_set_row_cnt,
  .table_set_col_cnt = lv_table_set_col_cnt,
  .table_set_col_width = lv_table_set_col_width,
  .table_add_cell_ctrl = lv_table_add_cell_ctrl,
  .table_clear_cell_ctrl = lv_table_clear_cell_ctrl,
  .table_get_cell_value = lv_table_get_cell_value,
  .table_get_row_cnt = lv_table_get_row_cnt,
  .table_get_col_cnt = lv_table_get_col_cnt,
  .table_get_col_width = lv_table_get_col_width,
  .table_has_cell_ctrl = lv_table_has_cell_ctrl,
  .table_get_selected_cell = lv_table_get_selected_cell,

  // checkbox
  .checkbox_create = lv_checkbox_create,
  .checkbox_set_text = lv_checkbox_set_text,
  .checkbox_set_text_static = lv_checkbox_set_text_static,
  .checkbox_get_text = lv_checkbox_get_text,

  // bar
  .bar_create = lv_bar_create,
  .bar_set_value = lv_bar_set_value,
  .bar_set_start_value = lv_bar_set_start_value,
  .bar_set_range = lv_bar_set_range,
  .bar_set_mode = lv_bar_set_mode,
  .bar_get_value = lv_bar_get_value,
  .bar_get_start_value = lv_bar_get_start_value,
  .bar_get_min_value = lv_bar_get_min_value,
  .bar_get_max_value = lv_bar_get_max_value,
  .bar_get_mode = lv_bar_get_mode,

  // slider
  .slider_create = lv_slider_create,
  .slider_is_dragged = lv_slider_is_dragged,

  // btnmatrix
  .btnmatrix_create = lv_btnmatrix_create,
  .btnmatrix_set_map = lv_btnmatrix_set_map,
  .btnmatrix_set_ctrl_map = lv_btnmatrix_set_ctrl_map,
  .btnmatrix_set_selected_btn = lv_btnmatrix_set_selected_btn,
  .btnmatrix_set_btn_ctrl = lv_btnmatrix_set_btn_ctrl,
  .btnmatrix_clear_btn_ctrl = lv_btnmatrix_clear_btn_ctrl,
  .btnmatrix_set_btn_ctrl_all = lv_btnmatrix_set_btn_ctrl_all,
  .btnmatrix_clear_btn_ctrl_all = lv_btnmatrix_clear_btn_ctrl_all,
  .btnmatrix_set_btn_width = lv_btnmatrix_set_btn_width,
  .btnmatrix_set_one_checked = lv_btnmatrix_set_one_checked,
  .btnmatrix_get_map = lv_btnmatrix_get_map,
  .btnmatrix_get_selected_btn = lv_btnmatrix_get_selected_btn,
  .btnmatrix_get_btn_text = lv_btnmatrix_get_btn_text,
  .btnmatrix_has_btn_ctrl = lv_btnmatrix_has_btn_ctrl,
  .btnmatrix_get_one_checked = lv_btnmatrix_get_one_checked,

  // dropdown
  .dropdown_create = lv_dropdown_create,
  .dropdown_set_text = lv_dropdown_set_text,
  .dropdown_set_options = lv_dropdown_set_options,
  .dropdown_set_options_static = lv_dropdown_set_options_static,
  .dropdown_add_option = lv_dropdown_add_option,
  .dropdown_clear_options = lv_dropdown_clear_options,
  .dropdown_set_selected = lv_dropdown_set_selected,
  .dropdown_set_dir = lv_dropdown_set_dir,
  .dropdown_set_symbol = lv_dropdown_set_symbol,
  .dropdown_set_selected_highlight = lv_dropdown_set_selected_highlight,
  .dropdown_get_list = lv_dropdown_get_list,
  .dropdown_get_text = lv_dropdown_get_text,
  .dropdown_get_options = lv_dropdown_get_options,
  .dropdown_get_selected = lv_dropdown_get_selected,
  .dropdown_get_option_cnt = lv_dropdown_get_option_cnt,
  .dropdown_get_selected_str = lv_dropdown_get_selected_str,
  .dropdown_get_symbol = lv_dropdown_get_symbol,
  .dropdown_get_selected_highlight = lv_dropdown_get_selected_highlight,
  .dropdown_get_dir = lv_dropdown_get_dir,
  .dropdown_open = lv_dropdown_open,
  .dropdown_close = lv_dropdown_close,

  .roller_create = lv_roller_create,
  .roller_set_options = lv_roller_set_options,
  .roller_set_selected = lv_roller_set_selected,
  .roller_set_visible_row_count = lv_roller_set_visible_row_count,
  .roller_get_selected = lv_roller_get_selected,
  .roller_get_selected_str = lv_roller_get_selected_str,
  .roller_get_options = lv_roller_get_options,
  .roller_get_option_cnt = lv_roller_get_option_cnt,

  // textarea
  .textarea_create = lv_textarea_create,
  .textarea_add_char = lv_textarea_add_char,
  .textarea_add_text = lv_textarea_add_text,
  .textarea_del_char = lv_textarea_del_char,
  .textarea_del_char_forward = lv_textarea_del_char_forward,
  .textarea_set_text = lv_textarea_set_text,
  .textarea_set_placeholder_text = lv_textarea_set_placeholder_text,
  .textarea_set_cursor_pos = lv_textarea_set_cursor_pos,
  .textarea_set_cursor_click_pos = lv_textarea_set_cursor_click_pos,
  .textarea_set_password_mode = lv_textarea_set_password_mode,
  .textarea_set_one_line = lv_textarea_set_one_line,
  .textarea_set_accepted_chars = lv_textarea_set_accepted_chars,
  .textarea_set_max_length = lv_textarea_set_max_length,
  .textarea_set_insert_replace = lv_textarea_set_insert_replace,
  .textarea_set_text_selection = lv_textarea_set_text_selection,
  .textarea_set_password_show_time = lv_textarea_set_password_show_time,
  .textarea_set_align = lv_textarea_set_align,
  .textarea_get_text = lv_textarea_get_text,
  .textarea_get_placeholder_text = lv_textarea_get_placeholder_text,
  .textarea_get_label = lv_textarea_get_label,
  .textarea_get_cursor_pos = lv_textarea_get_cursor_pos,
  .textarea_get_cursor_click_pos = lv_textarea_get_cursor_click_pos,
  .textarea_get_password_mode = lv_textarea_get_password_mode,
  .textarea_get_one_line = lv_textarea_get_one_line,
  .textarea_get_accepted_chars = lv_textarea_get_accepted_chars,
  .textarea_get_max_length = lv_textarea_get_max_length,
  .textarea_text_is_selected = lv_textarea_text_is_selected,
  .textarea_get_text_selection = lv_textarea_get_text_selection,
  .textarea_get_password_show_time = lv_textarea_get_password_show_time,
  .textarea_clear_selection = lv_textarea_clear_selection,
  .textarea_cursor_right = lv_textarea_cursor_right,
  .textarea_cursor_left = lv_textarea_cursor_left,
  .textarea_cursor_down = lv_textarea_cursor_down,
  .textarea_cursor_up = lv_textarea_cursor_up,

  // canvas
  .canvas_create = lv_canvas_create,
  .canvas_set_buffer = lv_canvas_set_buffer,
  .canvas_set_px = lv_canvas_set_px,
  .canvas_set_palette = lv_canvas_set_palette,
  .canvas_get_px = lv_canvas_get_px,
  .canvas_get_img = lv_canvas_get_img,
  .canvas_copy_buf = lv_canvas_copy_buf,
  .canvas_transform = lv_canvas_transform,
  .canvas_blur_hor = lv_canvas_blur_hor,
  .canvas_blur_ver = lv_canvas_blur_ver,
  .canvas_fill_bg = lv_canvas_fill_bg,
  .canvas_draw_rect = lv_canvas_draw_rect,
  .canvas_draw_text = lv_canvas_draw_text,
  .canvas_draw_img = lv_canvas_draw_img,
  .canvas_draw_line = lv_canvas_draw_line,
  .canvas_draw_polygon = lv_canvas_draw_polygon,
  .canvas_draw_arc = lv_canvas_draw_arc,

  // switch
  .switch_create = lv_switch_create,

  // extra
  .extra_init = lv_extra_init,

  // extra widgets
  // calendar
  .calendar_create = lv_calendar_create,
  .calendar_set_today_date = lv_calendar_set_today_date,
  .calendar_set_showed_date = lv_calendar_set_showed_date,
  .calendar_set_highlighted_dates = lv_calendar_set_highlighted_dates,
  .calendar_set_day_names = lv_calendar_set_day_names,
  .calendar_get_today_date = lv_calendar_get_today_date,
  .calendar_get_showed_date = lv_calendar_get_showed_date,
  .calendar_get_highlighted_dates = lv_calendar_get_highlighted_dates,
  .calendar_get_highlighted_dates_num = lv_calendar_get_highlighted_dates_num,
  .calendar_get_pressed_date = lv_calendar_get_pressed_date,
  .calendar_header_arrow_create = lv_calendar_header_arrow_create,
  .calendar_header_dropdown_create = lv_calendar_header_dropdown_create,

  // chart
  .chart_create = lv_chart_create,
  .chart_set_type = lv_chart_set_type,
  .chart_set_point_count = lv_chart_set_point_count,
  .chart_set_range = lv_chart_set_range,
  .chart_set_update_mode = lv_chart_set_update_mode,
  .chart_set_div_line_count = lv_chart_set_div_line_count,
  .chart_set_zoom_x = lv_chart_set_zoom_x,
  .chart_set_zoom_y = lv_chart_set_zoom_y,
  .chart_get_zoom_x = lv_chart_get_zoom_x,
  .chart_get_zoom_y = lv_chart_get_zoom_y,
  .chart_set_axis_tick = lv_chart_set_axis_tick,
  .chart_get_type = lv_chart_get_type,
  .chart_get_point_count = lv_chart_get_point_count,
  .chart_get_x_start_point = lv_chart_get_x_start_point,
  .chart_get_point_pos_by_id = lv_chart_get_point_pos_by_id,
  .chart_refresh = lv_chart_refresh,
  .chart_add_series = lv_chart_add_series,
  .chart_remove_series = lv_chart_remove_series,
  .chart_hide_series = lv_chart_hide_series,
  .chart_set_series_color = lv_chart_set_series_color,
  .chart_set_x_start_point = lv_chart_set_x_start_point,
  .chart_get_series_next = lv_chart_get_series_next,
  .chart_add_cursor = lv_chart_add_cursor,
  .chart_set_cursor_pos = lv_chart_set_cursor_pos,
  .chart_set_cursor_point = lv_chart_set_cursor_point,
  .chart_get_cursor_point = lv_chart_get_cursor_point,
  .chart_set_all_value = lv_chart_set_all_value,
  .chart_set_next_value = lv_chart_set_next_value,
  .chart_set_next_value2 = lv_chart_set_next_value2,
  .chart_set_value_by_id = lv_chart_set_value_by_id,
  .chart_set_value_by_id2 = lv_chart_set_value_by_id2,
  .chart_set_ext_y_array = lv_chart_set_ext_y_array,
  .chart_set_ext_x_array = lv_chart_set_ext_x_array,
  .chart_get_y_array = lv_chart_get_y_array,
  .chart_get_x_array = lv_chart_get_x_array,
  .chart_get_pressed_point = lv_chart_get_pressed_point,

  // keyboard
  .keyboard_create = lv_keyboard_create,
  .keyboard_set_textarea = lv_keyboard_set_textarea,
  .keyboard_set_mode = lv_keyboard_set_mode,
  .keyboard_set_map = lv_keyboard_set_map,
  .keyboard_get_textarea = lv_keyboard_get_textarea,
  .keyboard_get_mode = lv_keyboard_get_mode,
  .keyboard_def_event_cb = lv_keyboard_def_event_cb,

  // list
  .list_create = lv_list_create,
  .list_add_text = lv_list_add_text,
  .list_add_btn = lv_list_add_btn,
  .list_get_btn_text = lv_list_get_btn_text,

  // messagebox
  .msgbox_create = lv_msgbox_create,
  .msgbox_get_title = lv_msgbox_get_title,
  .msgbox_get_close_btn = lv_msgbox_get_close_btn,
  .msgbox_get_text = lv_msgbox_get_text,
  .msgbox_get_btns = lv_msgbox_get_btns,
  .msgbox_get_active_btn_text = lv_msgbox_get_active_btn_text,
  .msgbox_close = lv_msgbox_close,

  // meter
  .meter_create = lv_meter_create,
  .meter_add_scale = lv_meter_add_scale,
  .meter_set_scale_ticks = lv_meter_set_scale_ticks,
  .meter_set_scale_major_ticks = lv_meter_set_scale_major_ticks,
  .meter_set_scale_range = lv_meter_set_scale_range,
  .meter_add_needle_line = lv_meter_add_needle_line,
  .meter_add_needle_img = lv_meter_add_needle_img,
  .meter_add_arc = lv_meter_add_arc,
  .meter_add_scale_lines = lv_meter_add_scale_lines,
  .meter_set_indicator_value = lv_meter_set_indicator_value,
  .meter_set_indicator_start_value = lv_meter_set_indicator_start_value,
  .meter_set_indicator_end_value = lv_meter_set_indicator_end_value,

  // spinbox
  .spinbox_create = lv_spinbox_create,
  .spinbox_set_value = lv_spinbox_set_value,
  .spinbox_set_rollover = lv_spinbox_set_rollover,
  .spinbox_set_digit_format = lv_spinbox_set_digit_format,
  .spinbox_set_step = lv_spinbox_set_step,
  .spinbox_set_range = lv_spinbox_set_range,
  .spinbox_get_rollover = lv_spinbox_get_rollover,
  .spinbox_get_value = lv_spinbox_get_value,
  .spinbox_get_step = lv_spinbox_get_step,
  .spinbox_step_next = lv_spinbox_step_next,
  .spinbox_step_prev = lv_spinbox_step_prev,
  .spinbox_increment = lv_spinbox_increment,
  .spinbox_decrement = lv_spinbox_decrement,

  // spinner
  .spinner_create = lv_spinner_create,

  // tabview
  .tabview_create = lv_tabview_create,
  .tabview_add_tab = lv_tabview_add_tab,
  .tabview_get_content = lv_tabview_get_content,
  .tabview_get_tab_btns = lv_tabview_get_tab_btns,
  .tabview_set_act = lv_tabview_set_act,
  .tabview_get_tab_act = lv_tabview_get_tab_act,

  // tileview
  .tileview_create = lv_tileview_create,
  .tileview_add_tile = lv_tileview_add_tile,
  .obj_set_tile = lv_obj_set_tile,
  .obj_set_tile_id = lv_obj_set_tile_id,
  .tileview_get_tile_act = lv_tileview_get_tile_act,

  // win
  .win_create = lv_win_create,
  .win_add_title = lv_win_add_title,
  .win_add_btn = lv_win_add_btn,
  .win_get_header = lv_win_get_header,
  .win_get_content = lv_win_get_content,

  // colorwheel
  .colorwheel_create = lv_colorwheel_create,
  .colorwheel_set_hsv = lv_colorwheel_set_hsv,
  .colorwheel_set_rgb = lv_colorwheel_set_rgb,
  .colorwheel_set_mode = lv_colorwheel_set_mode,
  .colorwheel_set_mode_fixed = lv_colorwheel_set_mode_fixed,
  .colorwheel_get_hsv = lv_colorwheel_get_hsv,
  .colorwheel_get_rgb = lv_colorwheel_get_rgb,
  .colorwheel_get_color_mode = lv_colorwheel_get_color_mode,
  .colorwheel_get_color_mode_fixed = lv_colorwheel_get_color_mode_fixed,

  // led
  .led_create = lv_led_create,
  .led_set_color = lv_led_set_color,
  .led_set_brightness = lv_led_set_brightness,
  .led_on = lv_led_on,
  .led_off = lv_led_off,
  .led_toggle = lv_led_toggle,
  .led_get_brightness = lv_led_get_brightness,

  // imgbtn
  .imgbtn_create = lv_imgbtn_create,
  .imgbtn_set_src = lv_imgbtn_set_src,
  .imgbtn_get_src_left = lv_imgbtn_get_src_left,
  .imgbtn_get_src_middle = lv_imgbtn_get_src_middle,
  .imgbtn_get_src_right = lv_imgbtn_get_src_right,

  // span
  .spangroup_create = lv_spangroup_create,
  .spangroup_new_span = lv_spangroup_new_span,
  .spangroup_del_span = lv_spangroup_del_span,
  .span_set_text = lv_span_set_text,
  .span_set_text_static = lv_span_set_text_static,
  .spangroup_set_align = lv_spangroup_set_align,
  .spangroup_set_overflow = lv_spangroup_set_overflow,
  .spangroup_set_indent = lv_spangroup_set_indent,
  .spangroup_set_mode = lv_spangroup_set_mode,
  .spangroup_get_align = lv_spangroup_get_align,
  .spangroup_get_overflow = lv_spangroup_get_overflow,
  .spangroup_get_indent = lv_spangroup_get_indent,
  .spangroup_get_mode = lv_spangroup_get_mode,
  .spangroup_get_max_line_h = lv_spangroup_get_max_line_h,
  .spangroup_get_expand_width = lv_spangroup_get_expand_width,
  .spangroup_get_expand_height = lv_spangroup_get_expand_height,
  .spangroup_refr_mode = lv_spangroup_refr_mode,

  // extra layouts
  // flex
  .flex_init = lv_flex_init,
  .obj_set_flex_flow = lv_obj_set_flex_flow,
  .obj_set_flex_align = lv_obj_set_flex_align,
  .obj_set_flex_grow = lv_obj_set_flex_grow,
  .style_set_flex_flow = lv_style_set_flex_flow,
  .style_set_flex_main_place = lv_style_set_flex_main_place,
  .style_set_flex_cross_place = lv_style_set_flex_cross_place,
  .style_set_flex_track_place = lv_style_set_flex_track_place,
  .style_set_flex_grow = lv_style_set_flex_grow,
  .obj_set_style_flex_flow = lv_obj_set_style_flex_flow,
  .obj_set_style_flex_main_place = lv_obj_set_style_flex_main_place,
  .obj_set_style_flex_cross_place = lv_obj_set_style_flex_cross_place,
  .obj_set_style_flex_track_place = lv_obj_set_style_flex_track_place,
  .obj_set_style_flex_grow = lv_obj_set_style_flex_grow,
  // grid
  .grid_init = lv_grid_init,
  .obj_set_grid_dsc_array = lv_obj_set_grid_dsc_array,
  .obj_set_grid_align = lv_obj_set_grid_align,
  .obj_set_grid_cell = lv_obj_set_grid_cell,
  .style_set_grid_row_dsc_array = lv_style_set_grid_row_dsc_array,
  .style_set_grid_column_dsc_array = lv_style_set_grid_column_dsc_array,
  .style_set_grid_row_align = lv_style_set_grid_row_align,
  .style_set_grid_column_align = lv_style_set_grid_column_align,
  .style_set_grid_cell_column_pos = lv_style_set_grid_cell_column_pos,
  .style_set_grid_cell_column_span = lv_style_set_grid_cell_column_span,
  .style_set_grid_cell_row_pos = lv_style_set_grid_cell_row_pos,
  .style_set_grid_cell_row_span = lv_style_set_grid_cell_row_span,
  .style_set_grid_cell_x_align = lv_style_set_grid_cell_x_align,
  .style_set_grid_cell_y_align = lv_style_set_grid_cell_y_align,

  .obj_set_style_grid_row_dsc_array = lv_obj_set_style_grid_row_dsc_array,
  .obj_set_style_grid_column_dsc_array = lv_obj_set_style_grid_column_dsc_array,
  .obj_set_style_grid_row_align = lv_obj_set_style_grid_row_align,
  .obj_set_style_grid_column_align = lv_obj_set_style_grid_column_align,
  .obj_set_style_grid_cell_column_pos = lv_obj_set_style_grid_cell_column_pos,
  .obj_set_style_grid_cell_column_span = lv_obj_set_style_grid_cell_column_span,
  .obj_set_style_grid_cell_row_pos = lv_obj_set_style_grid_cell_row_pos,
  .obj_set_style_grid_cell_row_span = lv_obj_set_style_grid_cell_row_span,
  .obj_set_style_grid_cell_x_align = lv_obj_set_style_grid_cell_x_align,
  .obj_set_style_grid_cell_y_align = lv_obj_set_style_grid_cell_y_align,

  // extra themes
  .theme_default_init = lv_theme_default_init,
  .theme_mono_init = lv_theme_mono_init,
  .theme_basic_init = lv_theme_basic_init,

  // system
  .get_font = lvgl_api_get_font,
  .get_image = lvgl_api_get_image,
  .get_theme = lvgl_api_get_theme,

  // class resolution
  .obj_class = &lv_obj_class,
  .animation_image_class = &lv_animimg_class,
  .calendar_class = &lv_calendar_class,
  .calendar_header_arrow_class = &lv_calendar_header_arrow_class,
  .calendar_header_dropdown_class = &lv_calendar_header_dropdown_class,
  .chart_class = &lv_chart_class,
  .colorwheel_class = &lv_colorwheel_class,
  .dropdown_class = &lv_dropdown_class,
  .image_button_class = &lv_imgbtn_class,
  .keyboard_class = &lv_keyboard_class,
  .led_class = &lv_led_class,
  .list_class = &lv_list_class,
  .list_text_class = &lv_list_text_class,
  .list_button_class = &lv_list_btn_class,
  .meter_class = &lv_meter_class,
  .spangroup_class = &lv_spangroup_class,
  .spinbox_class = &lv_spinbox_class,
  .spinner_class = &lv_spinner_class,
  .tabview_class = &lv_tabview_class,
  .tileview_class = &lv_tileview_class,
  .tileview_tile_class = &lv_tileview_tile_class,
  .window_class = &lv_win_class,
  .arc_class = &lv_arc_class,
  .bar_class = &lv_bar_class,
  .button_class = &lv_btn_class,
  .button_matrix_class = &lv_btnmatrix_class,
  .canvas_class = &lv_canvas_class,
  .checkbox_class = &lv_checkbox_class,
  .image_class = &lv_img_class,
  .line_class = &lv_line_class,
  .label_class = &lv_label_class,
  .message_box_class = &lv_msgbox_class,
  .roller_class = &lv_roller_class,
  .slider_class = &lv_slider_class,
  .switch_class = &lv_switch_class,
  .table_class = &lv_table_class,
  .textarea_class = &lv_textarea_class};

#if defined __StratifyOS__
#include <sos/sos.h>
#endif

#include <sdk/types.h>
#include <stdio.h>

#if defined __link
const lvgl_api_font_descriptor_t *(*lvgl_api_get_font_callback)(int) = NULL;
void lvgl_api_set_font_callback(const lvgl_api_font_descriptor_t *(*callback)(int)) {
  lvgl_api_get_font_callback = callback;
}

const lvgl_api_image_descriptor_t *(*lvgl_api_get_image_callback)(int) = NULL;
void lvgl_api_set_image_callback(const lvgl_api_image_descriptor_t *(*callback)(int)) {
  lvgl_api_get_image_callback = callback;
}

const lvgl_api_theme_descriptor_t *(*lvgl_api_get_theme_callback)(int) = NULL;
void lvgl_api_set_theme_callback(const lvgl_api_theme_descriptor_t *(*callback)(int)) {
  lvgl_api_get_theme_callback = callback;
}
#endif

const lvgl_api_font_descriptor_t *lvgl_api_get_font(int offset) {
#if defined __StratifyOS__
  lvgl_api_font_request_t request = {.offset = offset};
  kernel_request(LVGL_REQUEST_GET_FONT, &request);
  return request.descriptor;
#else
  if (lvgl_api_get_font_callback) {
    return lvgl_api_get_font_callback(offset);
  }
  return NULL;
#endif
}

const lvgl_api_image_descriptor_t *lvgl_api_get_image(int offset) {
#if defined __StratifyOS__
  lvgl_api_image_request_t request = {.offset = offset};
  kernel_request(LVGL_REQUEST_GET_IMAGE, &request);
  return request.descriptor;
#else
  if (lvgl_api_get_image_callback) {
    return lvgl_api_get_image_callback(offset);
  }
  return NULL;
#endif
}

const lvgl_api_theme_descriptor_t *lvgl_api_get_theme(int offset) {
#if defined __StratifyOS__
  lvgl_api_theme_request_t request = {.offset = offset};
  kernel_request(LVGL_REQUEST_GET_THEME, &request);
  return request.descriptor;
#else
  if (lvgl_api_get_theme_callback) {
    return lvgl_api_get_theme_callback(offset);
  }
  return NULL;
#endif
}

