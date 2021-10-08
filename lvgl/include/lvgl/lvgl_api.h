#ifndef LVGL_LVGL_API_H
#define LVGL_LVGL_API_H

#include <sdk/api.h>

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LVGL_API_VERSION 8

typedef struct {
  const char *name;
  const lv_font_t * font;
} lvgl_api_font_descriptor_t;

typedef struct {
  api_t sos_api;

  uint32_t (*timer_handler)();
  void (*tick_inc)(uint32_t);

  //events
  lv_res_t (*event_send)(struct _lv_obj_t * obj, lv_event_code_t event_code, void * param);
  lv_res_t (*obj_event_base)(const lv_obj_class_t * class_p, lv_event_t * e);
  struct _lv_obj_t * (*event_get_target)(lv_event_t * e);
  struct _lv_obj_t * (*event_get_current_target)(lv_event_t * e);
  lv_event_code_t (*event_get_code)(lv_event_t * e);
  void * (*event_get_param)(lv_event_t * e);
  void * (*event_get_user_data)(lv_event_t * e);
  uint32_t (*event_register_id)(void);
  struct _lv_event_dsc_t * (*obj_add_event_cb)(struct _lv_obj_t * obj, lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data);
  bool (*obj_remove_event_cb)(struct _lv_obj_t * obj, lv_event_cb_t event_cb);
  bool (*obj_remove_event_dsc)(struct _lv_obj_t * obj, struct _lv_event_dsc_t * event_dsc);
  lv_indev_t * (*event_get_indev)(lv_event_t * e);
  lv_obj_draw_part_dsc_t * (*event_get_draw_part_dsc)(lv_event_t * e);
  const lv_area_t * (*event_get_clip_area)(lv_event_t * e);
  const lv_area_t * (*event_get_old_size)(lv_event_t * e);
  uint32_t (*event_get_key)(lv_event_t * e);
  void (*event_set_ext_draw_size)(lv_event_t * e, lv_coord_t size);
  lv_point_t * (*event_get_self_size_info)(lv_event_t * e);
  lv_hit_test_info_t * (*event_get_hit_test_info)(lv_event_t * e);
  const lv_area_t * (*event_get_cover_area)(lv_event_t * e);
  void (*event_set_cover_res)(lv_event_t * e, lv_cover_res_t res);

  // object
  lv_obj_t *(*obj_create)(lv_obj_t *parent);
  void (*obj_add_flag)(lv_obj_t *obj, lv_obj_flag_t f);
  void (*obj_clear_flag)(lv_obj_t *obj, lv_obj_flag_t f);
  void (*obj_add_state)(lv_obj_t *obj, lv_state_t state);
  void (*obj_clear_state)(lv_obj_t *obj, lv_state_t state);
  bool (*obj_has_flag)(const lv_obj_t *obj, lv_obj_flag_t f);
  bool (*obj_has_flag_any)(const lv_obj_t *obj, lv_obj_flag_t f);
  lv_state_t (*obj_get_state)(const lv_obj_t *obj);
  bool (*obj_has_state)(const lv_obj_t *obj, lv_state_t state);
  void *(*obj_get_group)(const lv_obj_t *obj);
  void (*obj_allocate_spec_attr)(lv_obj_t *obj);
  bool (*obj_check_type)(const lv_obj_t *obj, const lv_obj_class_t *class_p);
  bool (*obj_has_class)(const lv_obj_t *obj, const lv_obj_class_t *class_p);
  const lv_obj_class_t *(*obj_get_class)(const lv_obj_t *obj);
  bool (*obj_is_valid)(const lv_obj_t *obj);

  //obj pos
  void (*obj_set_pos)(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y);
  void (*obj_set_x)(struct _lv_obj_t * obj, lv_coord_t x);
  void (*obj_set_y)(struct _lv_obj_t * obj, lv_coord_t y);
  void (*obj_set_size)(struct _lv_obj_t * obj, lv_coord_t w, lv_coord_t h);
  bool (*obj_refr_size)(struct _lv_obj_t * obj);
  void (*obj_set_width)(struct _lv_obj_t * obj, lv_coord_t w);
  void (*obj_set_height)(struct _lv_obj_t * obj, lv_coord_t h);
  void (*obj_set_content_width)(struct _lv_obj_t * obj, lv_coord_t w);
  void (*obj_set_content_height)(struct _lv_obj_t * obj, lv_coord_t h);
  void (*obj_set_layout)(struct _lv_obj_t * obj, uint32_t layout);
  bool (*obj_is_layout_positioned)(const struct _lv_obj_t * obj);
  void (*obj_mark_layout_as_dirty)(struct _lv_obj_t * obj);
  void (*obj_update_layout)(const struct _lv_obj_t * obj);
  uint32_t (*layout_register)(lv_layout_update_cb_t cb, void * user_data);
  void (*obj_set_align)(struct _lv_obj_t * obj, lv_align_t align);
  void (*obj_align)(struct _lv_obj_t * obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
  void (*obj_align_to)(struct _lv_obj_t * obj, const struct _lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
  void (*obj_get_coords)(const struct _lv_obj_t * obj, lv_area_t * coords);
  lv_coord_t (*obj_get_x)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_x2)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_y)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_y2)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_width)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_height)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_content_width)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_content_height)(const struct _lv_obj_t * obj);
  void (*obj_get_content_coords)(const struct _lv_obj_t * obj, lv_area_t * area);
  lv_coord_t (*obj_get_self_width)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_self_height)(const struct _lv_obj_t * obj);
  bool (*obj_refresh_self_size)(struct _lv_obj_t * obj);
  void (*obj_refr_pos)(struct _lv_obj_t * obj);
  void (*obj_move_to)(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y);
  void (*obj_move_children_by)(struct _lv_obj_t * obj, lv_coord_t x_diff, lv_coord_t y_diff, bool ignore_floating);
  void (*obj_invalidate_area)(const struct _lv_obj_t * obj, const lv_area_t * area);
  void (*obj_invalidate)(const struct _lv_obj_t * obj);
  bool (*obj_area_is_visible)(const struct _lv_obj_t * obj, lv_area_t * area);
  bool (*obj_is_visible)(const struct _lv_obj_t * obj);
  void (*obj_set_ext_click_area)(struct _lv_obj_t * obj, lv_coord_t size);
  void (*obj_get_click_area)(const struct _lv_obj_t * obj, lv_area_t * area);
  bool (*obj_hit_test)(struct _lv_obj_t * obj, const lv_point_t * point);
  lv_coord_t (*clamp_width)(lv_coord_t width, lv_coord_t min_width, lv_coord_t max_width, lv_coord_t ref_width);
  lv_coord_t (*clamp_height)(lv_coord_t height, lv_coord_t min_height, lv_coord_t max_height, lv_coord_t ref_height);

  //built-in layouts
  uint32_t *layout_flex;
  lv_style_prop_t *style_flex_flow;
  lv_style_prop_t *style_flex_main_place;
  lv_style_prop_t *style_flex_cross_place;
  lv_style_prop_t *style_flex_track_place;
  lv_style_prop_t *style_flex_grow;

  //obj scroll
  void (*obj_set_scrollbar_mode)(struct _lv_obj_t * obj, lv_scrollbar_mode_t mode);
  void (*obj_set_scroll_dir)(struct _lv_obj_t * obj, lv_dir_t dir);
  void (*obj_set_scroll_snap_x)(struct _lv_obj_t * obj, lv_scroll_snap_t align);
  void (*obj_set_scroll_snap_y)(struct _lv_obj_t * obj, lv_scroll_snap_t align);
  lv_scrollbar_mode_t (*obj_get_scrollbar_mode)(const struct _lv_obj_t * obj);
  lv_dir_t (*obj_get_scroll_dir)(const struct _lv_obj_t * obj);
  lv_scroll_snap_t (*obj_get_scroll_snap_x)(const struct _lv_obj_t * obj);
  lv_scroll_snap_t (*obj_get_scroll_snap_y)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_x)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_y)(const struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_top)(struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_bottom)(struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_left)(struct _lv_obj_t * obj);
  lv_coord_t (*obj_get_scroll_right)(struct _lv_obj_t * obj);
  void (*obj_get_scroll_end)(struct _lv_obj_t  * obj, lv_point_t * end);
  void (*obj_scroll_by)(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);
  void (*obj_scroll_to)(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);
  void (*obj_scroll_to_x)(struct _lv_obj_t * obj, lv_coord_t x, lv_anim_enable_t anim_en);
  void (*obj_scroll_to_y)(struct _lv_obj_t * obj, lv_coord_t y, lv_anim_enable_t anim_en);
  void (*obj_scroll_to_view)(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);
  void (*obj_scroll_to_view_recursive)(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);
  bool (*obj_is_scrolling)(const struct _lv_obj_t * obj);
  void (*obj_update_snap)(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);
  void (*obj_get_scrollbar_area)(struct _lv_obj_t * obj, lv_area_t * hor, lv_area_t * ver);
  void (*obj_scrollbar_invalidate)(struct _lv_obj_t * obj);

  //obj style
  void (*obj_add_style)(struct _lv_obj_t * obj, lv_style_t * style, lv_style_selector_t selector);
  void (*obj_remove_style)(struct _lv_obj_t * obj, lv_style_t * style, lv_style_selector_t selector);
  void (*obj_report_style_change)(lv_style_t * style);
  void (*obj_refresh_style)(struct _lv_obj_t * obj, lv_part_t part, lv_style_prop_t prop);
  void (*obj_enable_style_refresh)(bool en);
  lv_style_value_t (*obj_get_style_prop)(const struct _lv_obj_t * obj, lv_part_t part, lv_style_prop_t prop);
  void (*obj_set_local_style_prop)(struct _lv_obj_t * obj, lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector);
  lv_res_t (*obj_get_local_style_prop)(struct _lv_obj_t * obj, lv_style_prop_t prop, lv_style_value_t * value, lv_style_selector_t selector);
  bool (*obj_remove_local_style_prop)(struct _lv_obj_t * obj, lv_style_prop_t prop, lv_style_selector_t selector);
  void (*obj_fade_in)(struct _lv_obj_t * obj, uint32_t time, uint32_t delay);
  void (*obj_fade_out)(struct _lv_obj_t * obj, uint32_t time, uint32_t delay);
  lv_state_t (*obj_style_get_selector_state)(lv_style_selector_t selector);
  lv_part_t (*obj_style_get_selector_part)(lv_style_selector_t selector);

  //obj tree
  void (*obj_del)(struct _lv_obj_t * obj);
  void (*obj_clean)(struct _lv_obj_t * obj);
  void (*obj_del_anim_ready_cb)(lv_anim_t * a);
  void (*obj_del_async)(struct _lv_obj_t * obj);
  void (*obj_set_parent)(struct _lv_obj_t * obj, struct _lv_obj_t * parent);
  void (*obj_move_foreground)(struct _lv_obj_t * obj);
  void (*obj_move_background)(struct _lv_obj_t * obj);
  struct _lv_obj_t * (*obj_get_screen)(const struct _lv_obj_t * obj);
  lv_disp_t * (*obj_get_disp)(const struct _lv_obj_t * obj);
  struct _lv_obj_t * (*obj_get_parent)(const struct _lv_obj_t * obj);
  struct _lv_obj_t * (*obj_get_child)(const struct _lv_obj_t * obj, int32_t id);
  uint32_t (*obj_get_child_cnt)(const struct _lv_obj_t * obj);
  uint32_t (*obj_get_child_id)(const struct _lv_obj_t * obj);
  void (*obj_tree_walk)(struct _lv_obj_t * start_obj, lv_obj_tree_walk_cb_t cb, void * user_data);

  //obj class
  void (*obj_class_init_obj)(struct _lv_obj_t * obj);
  bool (*obj_is_editable)(struct _lv_obj_t * obj);
  bool (*obj_is_group_def)(struct _lv_obj_t * obj);


  //group
  lv_group_t * (*group_create)(void);
  void (*group_del)(lv_group_t * group);
  void (*group_set_default)(lv_group_t * group);
  lv_group_t * (*group_get_default)(void);
  void (*group_add_obj)(lv_group_t * group, struct _lv_obj_t * obj);
  void (*group_remove_obj)(lv_obj_t * obj);
  void (*group_remove_all_objs)(lv_group_t * group);
  void (*group_focus_obj)(lv_obj_t * obj);
  void (*group_focus_next)(lv_group_t * group);
  void (*group_focus_prev)(lv_group_t * group);
  void (*group_focus_freeze)(lv_group_t * group, bool en);
  lv_res_t (*group_send_data)(lv_group_t * group, uint32_t c);
  void (*group_set_focus_cb)(lv_group_t * group, lv_group_focus_cb_t focus_cb);
  void (*group_set_refocus_policy)(lv_group_t * group, lv_group_refocus_policy_t policy);
  void (*group_set_editing)(lv_group_t * group, bool edit);
  void (*group_set_wrap)(lv_group_t * group, bool en);
  struct _lv_obj_t * (*group_get_focused)(const lv_group_t * group);
  lv_group_focus_cb_t (*group_get_focus_cb)(const lv_group_t * group);
  bool (*group_get_editing)(const lv_group_t * group);
  bool (*group_get_wrap)(lv_group_t * group);
  uint32_t (*group_get_obj_count)(lv_group_t * group);

  //indev
  void (*indev_read_timer_cb)(lv_timer_t * timer);
  void (*indev_enable)(lv_indev_t * indev, bool en);
  lv_indev_t * (*indev_get_act)(void);
  lv_indev_type_t (*indev_get_type)(const lv_indev_t * indev);
  void (*indev_reset)(lv_indev_t * indev, lv_obj_t * obj);
  void (*indev_reset_long_press)(lv_indev_t * indev);
  void (*indev_set_cursor)(lv_indev_t * indev, lv_obj_t * cur_obj);
  void (*indev_set_group)(lv_indev_t * indev, lv_group_t * group);
  void (*indev_set_button_points)(lv_indev_t * indev, const lv_point_t points[]);
  void (*indev_get_point)(const lv_indev_t * indev, lv_point_t * point);
  lv_dir_t (*indev_get_gesture_dir)(const lv_indev_t * indev);
  uint32_t (*indev_get_key)(const lv_indev_t * indev);
  lv_dir_t (*indev_get_scroll_dir)(const lv_indev_t * indev);
  lv_obj_t * (*indev_get_scroll_obj)(const lv_indev_t * indev);
  void (*indev_get_vect)(const lv_indev_t * indev, lv_point_t * point);
  void (*indev_wait_release)(lv_indev_t * indev);
  lv_obj_t * (*indev_get_obj_act)(void);
  lv_timer_t * (*indev_get_read_timer)(lv_disp_t * indev);
  lv_obj_t * (*indev_search_obj)(lv_obj_t * obj, lv_point_t * point);

  //misc
  //misc/anim
  void (*anim_init)(lv_anim_t * a);
  lv_anim_t * (*anim_start)(const lv_anim_t * a);
  bool (*anim_del)(void * var, lv_anim_exec_xcb_t exec_cb);
  void (*anim_del_all)(void);
  lv_anim_t * (*anim_get)(void * var, lv_anim_exec_xcb_t exec_cb);
  uint16_t (*anim_count_running)(void);
  uint32_t (*anim_speed_to_time)(uint32_t speed, int32_t start, int32_t end);
  void (*anim_refr_now)(void);
  int32_t (*anim_path_linear)(const lv_anim_t * a);
  int32_t (*anim_path_ease_in)(const lv_anim_t * a);
  int32_t (*anim_path_ease_out)(const lv_anim_t * a);
  int32_t (*anim_path_ease_in_out)(const lv_anim_t * a);
  int32_t (*anim_path_overshoot)(const lv_anim_t * a);
  int32_t (*anim_path_bounce)(const lv_anim_t * a);
  int32_t (*anim_path_step)(const lv_anim_t * a);
  //misc/area
  void (*area_set_width)(lv_area_t * area_p, lv_coord_t w);
  void (*area_set_height)(lv_area_t * area_p, lv_coord_t h);
  uint32_t (*area_get_size)(const lv_area_t * area_p);
  void (*area_increase)(lv_area_t * area, lv_coord_t w_extra, lv_coord_t h_extra);
  void (*area_move)(lv_area_t * area, lv_coord_t x_ofs, lv_coord_t y_ofs);
  void (*area_align)(const lv_area_t * base, lv_area_t * to_align, lv_align_t align, lv_coord_t ofs_x, lv_coord_t ofs_y);
  //misc/color
  void (*color_fill)(lv_color_t * buf, lv_color_t color, uint32_t px_num);
  lv_color_t (*color_lighten)(lv_color_t c, lv_opa_t lvl);
  lv_color_t (*color_darken)(lv_color_t c, lv_opa_t lvl);
  lv_color_t (*color_change_lightness)(lv_color_t c, lv_opa_t lvl);
  lv_color_t (*color_hsv_to_rgb)(uint16_t h, uint8_t s, uint8_t v);
  lv_color_hsv_t (*color_rgb_to_hsv)(uint8_t r8, uint8_t g8, uint8_t b8);
  lv_color_hsv_t (*color_to_hsv)(lv_color_t color);
  lv_color_t (*palette_main)(lv_palette_t p);
  lv_color_t (*palette_lighten)(lv_palette_t p, uint8_t lvl);
  lv_color_t (*palette_darken)(lv_palette_t p, uint8_t lvl);
  //misc/fs
  void (*fs_drv_init)(lv_fs_drv_t * drv);
  void (*fs_drv_register)(lv_fs_drv_t * drv_p);
  lv_fs_drv_t * (*fs_get_drv)(char letter);
  bool (*fs_is_ready)(char letter);
  lv_fs_res_t (*fs_open)(lv_fs_file_t * file_p, const char * path, lv_fs_mode_t mode);
  lv_fs_res_t (*fs_close)(lv_fs_file_t * file_p);
  lv_fs_res_t (*fs_read)(lv_fs_file_t * file_p, void * buf, uint32_t btr, uint32_t * br);
  lv_fs_res_t (*fs_write)(lv_fs_file_t * file_p, const void * buf, uint32_t btw, uint32_t * bw);
  lv_fs_res_t (*fs_seek)(lv_fs_file_t * file_p, uint32_t pos, lv_fs_whence_t whence);
  lv_fs_res_t (*fs_tell)(lv_fs_file_t * file_p, uint32_t * pos);
  lv_fs_res_t (*fs_dir_open)(lv_fs_dir_t * rddir_p, const char * path);
  lv_fs_res_t (*fs_dir_read)(lv_fs_dir_t * rddir_p, char * fn);
  lv_fs_res_t (*fs_dir_close)(lv_fs_dir_t * rddir_p);
  char * (*fs_get_letters)(char * buf);
  const char * (*fs_get_ext)(const char * fn);
  char * (*fs_up)(char * path);
  const char * (*fs_get_last)(const char * path);
  //misc/math
  uint32_t (*bezier3)(uint32_t t, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
  uint16_t (*atan2)(int x, int y);
  void (*sqrt)(uint32_t x, lv_sqrt_res_t * q, uint32_t mask);
  int64_t (*pow)(int64_t base, int8_t exp);
  int32_t (*map)(int32_t x, int32_t min_in, int32_t max_in, int32_t min, int32_t max);
  uint32_t (*rand)(uint32_t min, uint32_t max);
  //misc/mem
  void (*mem_init)(void);
  void (*mem_deinit)(void);
  void * (*_mem_alloc)(size_t size);
  void (*mem_free)(void * data);
  void * (*mem_realloc)(void * data_p, size_t new_size);
  lv_res_t (*mem_test)(void);
  void (*mem_monitor)(lv_mem_monitor_t * mon_p);
  void * (*mem_buf_get)(uint32_t size);
  void (*mem_buf_release)(void * p);
  void (*mem_buf_free_all)(void);
  //misc/style
  void (*style_init)(lv_style_t * style);
  void (*style_reset)(lv_style_t * style);
  lv_style_prop_t (*style_register_prop)(void);
  bool (*style_remove_prop)(lv_style_t * style, lv_style_prop_t prop);
  void (*style_set_prop)(lv_style_t * style, lv_style_prop_t prop, lv_style_value_t value);
  lv_res_t (*style_get_prop)(lv_style_t * style, lv_style_prop_t prop, lv_style_value_t * value);
  void (*style_transition_dsc_init)(lv_style_transition_dsc_t * tr, const lv_style_prop_t props[], lv_anim_path_cb_t path_cb, uint32_t time, uint32_t delay, void * user_data);
  lv_style_value_t (*style_prop_get_default)(lv_style_prop_t prop);
  bool (*style_is_empty)(const lv_style_t * style);
  //misc/timer
  lv_timer_t *(*timer_create_basic)(void);
  lv_timer_t *(*timer_create)(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data);
  void(*timer_del)(lv_timer_t * timer);
  void(*timer_pause)(lv_timer_t * timer);
  void(*timer_resume)(lv_timer_t * timer);
  void(*timer_set_cb)(lv_timer_t * timer, lv_timer_cb_t timer_cb);
  void(*timer_set_period)(lv_timer_t * timer, uint32_t period);
  void(*timer_ready)(lv_timer_t * timer);
  void(*timer_set_repeat_count)(lv_timer_t * timer, int32_t repeat_count);
  void(*timer_reset)(lv_timer_t * timer);
  void(*timer_enable)(bool en);
  uint8_t(*timer_get_idle)(void);
  lv_timer_t *(*timer_get_next)(lv_timer_t * timer);

  //refresh
  void (*refr_now)(lv_disp_t * disp);

  //disp
  lv_obj_t * (*disp_get_scr_act)(lv_disp_t * disp);
  lv_obj_t * (*disp_get_scr_prev)(lv_disp_t * disp);
  void (*disp_load_scr)(lv_obj_t * scr);
  lv_obj_t * (*disp_get_layer_top)(lv_disp_t * disp);
  lv_obj_t * (*disp_get_layer_sys)(lv_disp_t * disp);
  void (*disp_set_theme)(lv_disp_t * disp, lv_theme_t * th);
  lv_theme_t * (*disp_get_theme)(lv_disp_t * disp);
  void (*disp_set_bg_color)(lv_disp_t * disp, lv_color_t color);
  void (*disp_set_bg_image)(lv_disp_t * disp, const void  * img_src);
  void (*disp_set_bg_opa)(lv_disp_t * disp, lv_opa_t opa);
  void (*scr_load_anim)(lv_obj_t * scr, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del);
  uint32_t (*disp_get_inactive_time)(const lv_disp_t * disp);
  void (*disp_trig_activity)(lv_disp_t * disp);
  void (*disp_clean_dcache)(lv_disp_t * disp);
  //theme
  lv_theme_t * (*theme_get_from_obj)(lv_obj_t * obj);
  void (*theme_apply)(lv_obj_t * obj);
  void (*theme_set_parent)(lv_theme_t * new_theme, lv_theme_t * parent);
  void (*theme_set_apply_cb)(lv_theme_t * theme, lv_theme_apply_cb_t apply_cb);
  const lv_font_t * (*theme_get_font_small)(lv_obj_t * obj);
  const lv_font_t * (*theme_get_font_normal)(lv_obj_t * obj);
  const lv_font_t * (*theme_get_font_large)(lv_obj_t * obj);
  lv_color_t (*theme_get_color_primary)(lv_obj_t * obj);
  lv_color_t (*theme_get_color_secondary)(lv_obj_t * obj);

  //font
  const uint8_t * (*font_get_glyph_bitmap)(const lv_font_t * font_p, uint32_t letter);
  bool (*font_get_glyph_dsc)(const lv_font_t * font_p, lv_font_glyph_dsc_t * dsc_out, uint32_t letter,
                             uint32_t letter_next);
  uint16_t (*font_get_glyph_width)(const lv_font_t * font, uint32_t letter, uint32_t letter_next);

  //font loader
  lv_font_t * (*font_load)(const char * fontName);
  void (*font_free)(lv_font_t * font);

  //font fmt txt
  const uint8_t * (*font_get_bitmap_fmt_txt)(const lv_font_t * font, uint32_t letter);
  bool (*font_get_glyph_dsc_fmt_txt)(const lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter,
                                     uint32_t unicode_letter_next);

  //widgets

  //arc
  lv_obj_t * (*arc_create)(lv_obj_t * parent);
  void (*arc_set_start_angle)(lv_obj_t * arc, uint16_t start);
  void (*arc_set_end_angle)(lv_obj_t * arc, uint16_t end);
  void (*arc_set_angles)(lv_obj_t * arc, uint16_t start, uint16_t end);
  void (*arc_set_bg_start_angle)(lv_obj_t * arc, uint16_t start);
  void (*arc_set_bg_end_angle)(lv_obj_t * arc, uint16_t end);
  void (*arc_set_bg_angles)(lv_obj_t * arc, uint16_t start, uint16_t end);
  void (*arc_set_rotation)(lv_obj_t * arc, uint16_t rotation);
  void (*arc_set_mode)(lv_obj_t * arc, lv_arc_mode_t type);
  void (*arc_set_value)(lv_obj_t * arc, int16_t value);
  void (*arc_set_range)(lv_obj_t * arc, int16_t min, int16_t max);
  void (*arc_set_change_rate)(lv_obj_t * arc, uint16_t rate);
  uint16_t (*arc_get_angle_start)(lv_obj_t * obj);
  uint16_t (*arc_get_angle_end)(lv_obj_t * obj);
  uint16_t (*arc_get_bg_angle_start)(lv_obj_t * obj);
  uint16_t (*arc_get_bg_angle_end)(lv_obj_t * obj);
  int16_t (*arc_get_value)(const lv_obj_t * obj);
  int16_t (*arc_get_min_value)(const lv_obj_t * obj);
  int16_t (*arc_get_max_value)(const lv_obj_t * obj);
  lv_arc_mode_t (*arc_get_mode)(const lv_obj_t * obj);

  //button
  lv_obj_t * (*btn_create)(lv_obj_t * parent);

  //img
  lv_obj_t * (*img_create)(lv_obj_t * parent);
  void (*img_set_src)(lv_obj_t * obj, const void * src);
  void (*img_set_offset_x)(lv_obj_t * obj, lv_coord_t x);
  void (*img_set_offset_y)(lv_obj_t * obj, lv_coord_t y);
  void (*img_set_angle)(lv_obj_t * obj, int16_t angle);
  void (*img_set_pivot)(lv_obj_t * obj, lv_coord_t x, lv_coord_t y);
  void (*img_set_zoom)(lv_obj_t * obj, uint16_t zoom);
  void (*img_set_antialias)(lv_obj_t * obj, bool antialias);
  const void * (*img_get_src)(lv_obj_t * obj);
  lv_coord_t (*img_get_offset_x)(lv_obj_t * obj);
  lv_coord_t (*img_get_offset_y)(lv_obj_t * obj);
  uint16_t (*img_get_angle)(lv_obj_t * obj);
  void (*img_get_pivot)(lv_obj_t * obj, lv_point_t * pivot);
  uint16_t (*img_get_zoom)(lv_obj_t * obj);
  bool (*img_get_antialias)(lv_obj_t * obj);

  //label
  lv_obj_t * (*label_create)(lv_obj_t * parent);
  void (*label_set_text)(lv_obj_t * obj, const char * text);
  void (*label_set_text_fmt)(lv_obj_t * obj, const char * fmt, ...);
  void (*label_set_text_static)(lv_obj_t * obj, const char * text);
  void (*label_set_long_mode)(lv_obj_t * obj, lv_label_long_mode_t long_mode);
  void (*label_set_recolor)(lv_obj_t * obj, bool en);
  void (*label_set_text_sel_start)(lv_obj_t * obj, uint32_t index);
  void (*label_set_text_sel_end)(lv_obj_t * obj, uint32_t index);
  char * (*label_get_text)(const lv_obj_t * obj);
  lv_label_long_mode_t (*label_get_long_mode)(const lv_obj_t * obj);
  bool (*label_get_recolor)(const lv_obj_t * obj);
  void (*label_get_letter_pos)(const lv_obj_t * obj, uint32_t char_id, lv_point_t * pos);
  uint32_t (*label_get_letter_on)(const lv_obj_t * obj, lv_point_t * pos_in);
  bool (*label_is_char_under_pos)(const lv_obj_t * obj, lv_point_t * pos);
  uint32_t (*label_get_text_selection_start)(const lv_obj_t * obj);
  uint32_t (*label_get_text_selection_end)(const lv_obj_t * obj);
  void (*label_ins_text)(lv_obj_t * obj, uint32_t pos, const char * txt);
  void (*label_cut_text)(lv_obj_t * obj, uint32_t pos, uint32_t cnt);

  //line
  lv_obj_t * (*line_create)(lv_obj_t * parent);
  void (*line_set_points)(lv_obj_t * obj, const lv_point_t points[], uint16_t point_num);
  void (*line_set_y_invert)(lv_obj_t * obj, bool en);
  bool (*line_get_y_invert)(const lv_obj_t * obj);

  //table
  lv_obj_t * (*table_create)(lv_obj_t * parent);
  void (*table_set_cell_value)(lv_obj_t * obj, uint16_t row, uint16_t col, const char * txt);
  void (*table_set_cell_value_fmt)(lv_obj_t * obj, uint16_t row, uint16_t col, const char * fmt, ...);
  void (*table_set_row_cnt)(lv_obj_t * obj, uint16_t row_cnt);
  void (*table_set_col_cnt)(lv_obj_t * obj, uint16_t col_cnt);
  void (*table_set_col_width)(lv_obj_t * obj, uint16_t col_id, lv_coord_t w);
  void (*table_add_cell_ctrl)(lv_obj_t * obj, uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);
  void (*table_clear_cell_ctrl)(lv_obj_t * obj, uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);
  const char * (*table_get_cell_value)(lv_obj_t * obj, uint16_t row, uint16_t col);
  uint16_t (*table_get_row_cnt)(lv_obj_t * obj);
  uint16_t (*table_get_col_cnt)(lv_obj_t * obj);
  lv_coord_t (*table_get_col_width)(lv_obj_t * obj, uint16_t col);
  bool (*table_has_cell_ctrl)(lv_obj_t * obj, uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);
  void (*table_get_selected_cell)(lv_obj_t * obj, uint16_t * row, uint16_t * col);

  //checkbox
  lv_obj_t * (*checkbox_create)(lv_obj_t * parent);
  void (*checkbox_set_text)(lv_obj_t * obj, const char * txt);
  void (*checkbox_set_text_static)(lv_obj_t * obj, const char * txt);
  const char * (*checkbox_get_text)(const lv_obj_t * obj);

  //bar
  lv_obj_t * (*bar_create)(lv_obj_t * parent);
  void (*bar_set_value)(lv_obj_t * obj, int32_t value, lv_anim_enable_t anim);
  void (*bar_set_start_value)(lv_obj_t * obj, int32_t start_value, lv_anim_enable_t anim);
  void (*bar_set_range)(lv_obj_t * obj, int32_t min, int32_t max);
  void (*bar_set_mode)(lv_obj_t * obj, lv_bar_mode_t mode);
  int32_t (*bar_get_value)(const lv_obj_t * obj);
  int32_t (*bar_get_start_value)(const lv_obj_t * obj);
  int32_t (*bar_get_min_value)(const lv_obj_t * obj);
  int32_t (*bar_get_max_value)(const lv_obj_t * obj);
  lv_bar_mode_t (*bar_get_mode)(lv_obj_t * obj);

  //slider
  lv_obj_t * (*slider_create)(lv_obj_t * parent);
  bool (*slider_is_dragged)(const lv_obj_t * obj);

  //btnmatrix
  lv_obj_t * (*btnmatrix_create)(lv_obj_t * parent);
  void (*btnmatrix_set_map)(lv_obj_t * obj, const char * map[]);
  void (*btnmatrix_set_ctrl_map)(lv_obj_t * obj, const lv_btnmatrix_ctrl_t ctrl_map[]);
  void (*btnmatrix_set_selected_btn)(lv_obj_t * obj, uint16_t btn_id);
  void (*btnmatrix_set_btn_ctrl)(lv_obj_t * obj, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
  void (*btnmatrix_clear_btn_ctrl)(const lv_obj_t * obj, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
  void (*btnmatrix_set_btn_ctrl_all)(lv_obj_t * obj, lv_btnmatrix_ctrl_t ctrl);
  void (*btnmatrix_clear_btn_ctrl_all)(lv_obj_t * obj, lv_btnmatrix_ctrl_t ctrl);
  void (*btnmatrix_set_btn_width)(lv_obj_t * obj, uint16_t btn_id, uint8_t width);
  void (*btnmatrix_set_one_checked)(lv_obj_t * obj, bool en);
  const char ** (*btnmatrix_get_map)(const lv_obj_t * obj);
  uint16_t (*btnmatrix_get_selected_btn)(const lv_obj_t * obj);
  const char * (*btnmatrix_get_btn_text)(const lv_obj_t * obj, uint16_t btn_id);
  bool (*btnmatrix_has_btn_ctrl)(lv_obj_t * obj, uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);
  bool (*btnmatrix_get_one_checked)(const lv_obj_t * obj);

  //dropdown
  lv_obj_t * (*dropdown_create)(lv_obj_t * parent);
  void (*dropdown_set_text)(lv_obj_t * obj, const char * txt);
  void (*dropdown_set_options)(lv_obj_t * obj, const char * options);
  void (*dropdown_set_options_static)(lv_obj_t * obj, const char * options);
  void (*dropdown_add_option)(lv_obj_t * obj, const char * option, uint32_t pos);
  void (*dropdown_clear_options)(lv_obj_t * obj);
  void (*dropdown_set_selected)(lv_obj_t * obj, uint16_t sel_opt);
  void (*dropdown_set_dir)(lv_obj_t * obj, lv_dir_t dir);
  void (*dropdown_set_symbol)(lv_obj_t * obj, const void * symbol);
  void (*dropdown_set_selected_highlight)(lv_obj_t * obj, bool en);
  lv_obj_t * (*dropdown_get_list)(lv_obj_t * obj);
  const char * (*dropdown_get_text)(lv_obj_t * obj);
  const char * (*dropdown_get_options)(const lv_obj_t * obj);
  uint16_t (*dropdown_get_selected)(const lv_obj_t * obj);
  uint16_t (*dropdown_get_option_cnt)(const lv_obj_t * obj);
  void (*dropdown_get_selected_str)(const lv_obj_t * obj, char * buf, uint32_t buf_size);
  const char * (*dropdown_get_symbol)(lv_obj_t * obj);
  bool (*dropdown_get_selected_highlight)(lv_obj_t * obj);
  lv_dir_t (*dropdown_get_dir)(const lv_obj_t * obj);
  void (*dropdown_open)(lv_obj_t * dropdown_obj);
  void (*dropdown_close)(lv_obj_t * obj);

  lv_obj_t * (*roller_create)(lv_obj_t * parent);
  void (*roller_set_options)(lv_obj_t * obj, const char * options, lv_roller_mode_t mode);
  void (*roller_set_selected)(lv_obj_t * obj, uint16_t sel_opt, lv_anim_enable_t anim);
  void (*roller_set_visible_row_count)(lv_obj_t * obj, uint8_t row_cnt);
  uint16_t (*roller_get_selected)(const lv_obj_t * obj);
  void (*roller_get_selected_str)(const lv_obj_t * obj, char * buf, uint32_t buf_size);
  const char * (*roller_get_options)(const lv_obj_t * obj);
  uint16_t (*roller_get_option_cnt)(const lv_obj_t * obj);

  //textarea
  lv_obj_t * (*textarea_create)(lv_obj_t * parent);
  void (*textarea_add_char)(lv_obj_t * obj, uint32_t c);
  void (*textarea_add_text)(lv_obj_t * obj, const char * txt);
  void (*textarea_del_char)(lv_obj_t * obj);
  void (*textarea_del_char_forward)(lv_obj_t * obj);
  void (*textarea_set_text)(lv_obj_t * obj, const char * txt);
  void (*textarea_set_placeholder_text)(lv_obj_t * obj, const char * txt);
  void (*textarea_set_cursor_pos)(lv_obj_t * obj, int32_t pos);
  void (*textarea_set_cursor_click_pos)(lv_obj_t * obj, bool en);
  void (*textarea_set_password_mode)(lv_obj_t * obj, bool en);
  void (*textarea_set_one_line)(lv_obj_t * obj, bool en);
  void (*textarea_set_accepted_chars)(lv_obj_t * obj, const char * list);
  void (*textarea_set_max_length)(lv_obj_t * obj, uint32_t num);
  void (*textarea_set_insert_replace)(lv_obj_t * obj, const char * txt);
  void (*textarea_set_text_selection)(lv_obj_t * obj, bool en);
  void (*textarea_set_password_show_time)(lv_obj_t * obj, uint16_t time);
  void (*textarea_set_align)(lv_obj_t * obj, lv_text_align_t align);
  const char * (*textarea_get_text)(const lv_obj_t * obj);
  const char * (*textarea_get_placeholder_text)(lv_obj_t * obj);
  lv_obj_t * (*textarea_get_label)(const lv_obj_t * obj);
  uint32_t (*textarea_get_cursor_pos)(const lv_obj_t * obj);
  bool (*textarea_get_cursor_click_pos)(lv_obj_t * obj);
  bool (*textarea_get_password_mode)(const lv_obj_t * obj);
  bool (*textarea_get_one_line)(const lv_obj_t * obj);
  const char * (*textarea_get_accepted_chars)(lv_obj_t * obj);
  uint32_t (*textarea_get_max_length)(lv_obj_t * obj);
  bool (*textarea_text_is_selected)(const lv_obj_t * obj);
  bool (*textarea_get_text_selection)(lv_obj_t * obj);
  uint16_t (*textarea_get_password_show_time)(lv_obj_t * obj);
  void (*textarea_clear_selection)(lv_obj_t * obj);
  void (*textarea_cursor_right)(lv_obj_t * obj);
  void (*textarea_cursor_left)(lv_obj_t * obj);
  void (*textarea_cursor_down)(lv_obj_t * obj);
  void (*textarea_cursor_up)(lv_obj_t * obj);

  //canvas
  lv_obj_t * (*canvas_create)(lv_obj_t * parent);
  void (*canvas_set_buffer)(lv_obj_t * canvas, void * buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf);
  void (*canvas_set_px)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_color_t c);
  void (*canvas_set_palette)(lv_obj_t * canvas, uint8_t id, lv_color_t c);
  lv_color_t (*canvas_get_px)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y);
  lv_img_dsc_t * (*canvas_get_img)(lv_obj_t * canvas);
  void (*canvas_copy_buf)(lv_obj_t * canvas, const void * to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w,
                          lv_coord_t h);
  void (*canvas_transform)(lv_obj_t * canvas, lv_img_dsc_t * img, int16_t angle, uint16_t zoom, lv_coord_t offset_x,
                           lv_coord_t offset_y,
                           int32_t pivot_x, int32_t pivot_y, bool antialias);
  void (*canvas_blur_hor)(lv_obj_t * canvas, const lv_area_t * area, uint16_t r);
  void (*canvas_blur_ver)(lv_obj_t * canvas, const lv_area_t * area, uint16_t r);
  void (*canvas_fill_bg)(lv_obj_t * canvas, lv_color_t color, lv_opa_t opa);
  void (*canvas_draw_rect)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                           const lv_draw_rect_dsc_t * draw_dsc);
  void (*canvas_draw_text)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_coord_t max_w,
                           lv_draw_label_dsc_t * draw_dsc, const char * txt);
  void (*canvas_draw_img)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, const void * src,
                          const lv_draw_img_dsc_t * draw_dsc);
  void (*canvas_draw_line)(lv_obj_t * canvas, const lv_point_t points[], uint32_t point_cnt,
                           const lv_draw_line_dsc_t * draw_dsc);
  void (*canvas_draw_polygon)(lv_obj_t * canvas, const lv_point_t points[], uint32_t point_cnt,
                              const lv_draw_rect_dsc_t * draw_dsc);
  void (*canvas_draw_arc)(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle,
                          int32_t end_angle, const lv_draw_arc_dsc_t * draw_dsc);

  //switch
  lv_obj_t * (*switch_create)(lv_obj_t * parent);

  //extra
  void (*extra_init)(void);

  //extra widgets
  //calendar
  lv_obj_t * (*calendar_create)(lv_obj_t * parent);
  void (*calendar_set_today_date)(lv_obj_t * obj, uint32_t year, uint32_t month, uint32_t day);
  void (*calendar_set_showed_date)(lv_obj_t * obj, uint32_t year, uint32_t month);
  void (*calendar_set_highlighted_dates)(lv_obj_t * obj, lv_calendar_date_t highlighted[], uint16_t date_num);
  void (*calendar_set_day_names)(lv_obj_t * obj, const char ** day_names);
  const lv_calendar_date_t * (*calendar_get_today_date)(const lv_obj_t * calendar);
  const lv_calendar_date_t * (*calendar_get_showed_date)(const lv_obj_t * calendar);
  lv_calendar_date_t * (*calendar_get_highlighted_dates)(const lv_obj_t * calendar);
  uint16_t (*calendar_get_highlighted_dates_num)(const lv_obj_t * calendar);
  lv_res_t (*calendar_get_pressed_date)(const lv_obj_t * calendar, lv_calendar_date_t * date);
  lv_obj_t * (*calendar_header_arrow_create)(lv_obj_t * parent, lv_obj_t * calendar, lv_coord_t btn_size);
  lv_obj_t * (*calendar_header_dropdown_create)(lv_obj_t * parent, lv_obj_t * calendar);

  //chart
  lv_obj_t * (*chart_create)(lv_obj_t * parent);
  void (*chart_set_type)(lv_obj_t * obj, lv_chart_type_t type);
  void (*chart_set_point_count)(lv_obj_t * obj, uint16_t cnt);
  void (*chart_set_range)(lv_obj_t * obj, lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max);
  void (*chart_set_update_mode)(lv_obj_t * obj, lv_chart_update_mode_t update_mode);
  void (*chart_set_div_line_count)(lv_obj_t * obj, uint8_t hdiv, uint8_t vdiv);
  void (*chart_set_zoom_x)(lv_obj_t * obj, uint16_t zoom_x);
  void (*chart_set_zoom_y)(lv_obj_t * obj, uint16_t zoom_y);
  uint16_t (*chart_get_zoom_x)(const lv_obj_t * obj);
  uint16_t (*chart_get_zoom_y)(const lv_obj_t * obj);
  void (*chart_set_axis_tick)(lv_obj_t * obj, lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len, lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en, lv_coord_t draw_size);
  lv_chart_type_t (*chart_get_type)(const lv_obj_t * obj);
  uint16_t (*chart_get_point_count)(const lv_obj_t * obj);
  uint16_t (*chart_get_x_start_point)(const lv_obj_t * obj, lv_chart_series_t * ser);
  void (*chart_get_point_pos_by_id)(lv_obj_t * obj, lv_chart_series_t * ser, uint16_t id, lv_point_t * p_out);
  void (*chart_refresh)(lv_obj_t * obj);
  lv_chart_series_t * (*chart_add_series)(lv_obj_t * obj, lv_color_t color, lv_chart_axis_t axis);
  void (*chart_remove_series)(lv_obj_t * obj, lv_chart_series_t * series);
  void (*chart_hide_series)(lv_obj_t * chart, lv_chart_series_t * series, bool hide);
  void (*chart_set_series_color)(lv_obj_t * chart, lv_chart_series_t * series, lv_color_t color);
  void (*chart_set_x_start_point)(lv_obj_t * obj, lv_chart_series_t * ser, uint16_t id);
  lv_chart_series_t * (*chart_get_series_next)(const lv_obj_t * chart, const lv_chart_series_t * ser);
  lv_chart_cursor_t  * (*chart_add_cursor)(lv_obj_t * obj, lv_color_t color, lv_dir_t dir);
  void (*chart_set_cursor_pos)(lv_obj_t * chart, lv_chart_cursor_t * cursor, lv_point_t * pos);
  void (*chart_set_cursor_point)(lv_obj_t * chart, lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t point_id);
  lv_point_t(*chart_get_cursor_point)(lv_obj_t * chart, lv_chart_cursor_t * cursor);
  void (*chart_set_all_value)(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t value);
  void (*chart_set_next_value)(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t value);
  void (*chart_set_next_value2)(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t x_value, lv_coord_t y_value);
  void (*chart_set_value_by_id)(lv_obj_t * obj, lv_chart_series_t * ser, uint16_t id, lv_coord_t value);
  void (*chart_set_value_by_id2)(lv_obj_t * obj, lv_chart_series_t * ser, uint16_t id, lv_coord_t x_value, lv_coord_t y_value);
  void (*chart_set_ext_y_array)(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t array[]);
  void (*chart_set_ext_x_array)(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t array[]);
  lv_coord_t * (*chart_get_y_array)(const lv_obj_t * obj, lv_chart_series_t * ser);
  lv_coord_t * (*chart_get_x_array)(const lv_obj_t * obj, lv_chart_series_t * ser);
  uint32_t (*chart_get_pressed_point)(const lv_obj_t * obj);

  //keyboard
  lv_obj_t * (*keyboard_create)(lv_obj_t * parent);
  void (*keyboard_set_textarea)(lv_obj_t * kb, lv_obj_t * ta);
  void (*keyboard_set_mode)(lv_obj_t * kb, lv_keyboard_mode_t mode);
  void (*keyboard_set_map)(lv_obj_t * kb, lv_keyboard_mode_t mode, const char * map[], const lv_btnmatrix_ctrl_t ctrl_map[]);
  lv_obj_t * (*keyboard_get_textarea)(const lv_obj_t * kb);
  lv_keyboard_mode_t (*keyboard_get_mode)(const lv_obj_t * kb);
  void (*keyboard_def_event_cb)(lv_event_t * e);

  //list
  lv_obj_t * (*list_create)(lv_obj_t * parent);
  lv_obj_t * (*list_add_text)(lv_obj_t * list, const char * txt);
  lv_obj_t * (*list_add_btn)(lv_obj_t * list, const char * icon, const char * txt);
  const char * (*list_get_btn_text)(lv_obj_t * list, lv_obj_t * btn);

  //messagebox
  lv_obj_t * (*msgbox_create)(lv_obj_t * parent, const char * title, const char * txt, const char * btn_txts[], bool add_close_btn);
  lv_obj_t * (*msgbox_get_title)(lv_obj_t * mbox);
  lv_obj_t * (*msgbox_get_close_btn)(lv_obj_t * mbox);
  lv_obj_t * (*msgbox_get_text)(lv_obj_t * mbox);
  lv_obj_t * (*msgbox_get_btns)(lv_obj_t * mbox);
  const char * (*msgbox_get_active_btn_text)(lv_obj_t * mbox);
  void (*msgbox_close)(lv_obj_t * mbox);

  //meter
  lv_obj_t * (*meter_create)(lv_obj_t * parent);
  lv_meter_scale_t * (*meter_add_scale)(lv_obj_t * obj);
  void (*meter_set_scale_ticks)(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t cnt, uint16_t width, uint16_t len, lv_color_t color);
  void (*meter_set_scale_major_ticks)(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t nth, uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap);
  void (*meter_set_scale_range)(lv_obj_t * obj, lv_meter_scale_t * scale, int32_t min, int32_t max, uint32_t angle_range, uint32_t rotation);
  lv_meter_indicator_t * (*meter_add_needle_line)(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t width, lv_color_t color, int16_t r_mod);
  lv_meter_indicator_t * (*meter_add_needle_img)(lv_obj_t * obj, lv_meter_scale_t * scale, const void * src, lv_coord_t pivot_x, lv_coord_t pivot_y);
  lv_meter_indicator_t * (*meter_add_arc)(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t width, lv_color_t color, int16_t r_mod);
  lv_meter_indicator_t * (*meter_add_scale_lines)(lv_obj_t * obj, lv_meter_scale_t * scale, lv_color_t color_start, lv_color_t color_end, bool local, int16_t width_mod);
  void (*meter_set_indicator_value)(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value);
  void (*meter_set_indicator_start_value)(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value);
  void (*meter_set_indicator_end_value)(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value);

  //spinbox
  void (*spinbox_set_value)(lv_obj_t * obj, int32_t i);
  void (*spinbox_set_rollover)(lv_obj_t * obj, bool b);
  void (*spinbox_set_digit_format)(lv_obj_t * obj, uint8_t digit_count, uint8_t separator_position);
  void (*spinbox_set_step)(lv_obj_t * obj, uint32_t step);
  void (*spinbox_set_range)(lv_obj_t * obj, int32_t range_min, int32_t range_max);
  bool (*spinbox_get_rollover)(lv_obj_t * obj);
  int32_t (*spinbox_get_value)(lv_obj_t * obj);
  int32_t (*spinbox_get_step)(lv_obj_t * obj);
  void (*spinbox_step_next)(lv_obj_t * obj);
  void (*spinbox_step_prev)(lv_obj_t * obj);
  void (*spinbox_increment)(lv_obj_t * obj);
  void (*spinbox_decrement)(lv_obj_t * obj);

  //spinner
  lv_obj_t * (*spinner_create)(lv_obj_t * parent, uint32_t time, uint32_t arc_length);

  //tabview
  lv_obj_t * (*tabview_create)(lv_obj_t * parent, lv_dir_t tab_pos, lv_coord_t tab_size);
  lv_obj_t * (*tabview_add_tab)(lv_obj_t * tv, const char * name);
  lv_obj_t * (*tabview_get_content)(lv_obj_t * tv);
  lv_obj_t * (*tabview_get_tab_btns)(lv_obj_t * tv);
  void (*tabview_set_act)(lv_obj_t * obj, uint32_t id, lv_anim_enable_t anim_en);
  uint16_t (*tabview_get_tab_act)(lv_obj_t * tv);

  //tileview
  lv_obj_t * (*tileview_create)(lv_obj_t * parent);
  lv_obj_t * (*tileview_add_tile)(lv_obj_t * tv, uint8_t row_id, uint8_t col_id, lv_dir_t dir);
  void (*obj_set_tile)(lv_obj_t * tv, lv_obj_t * tile_obj, lv_anim_enable_t anim_en);
  void (*obj_set_tile_id)(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en);
  lv_obj_t * (*tileview_get_tile_act)(lv_obj_t * obj);

  //win
  lv_obj_t * (*win_create)(lv_obj_t * parent, lv_coord_t header_height);
  lv_obj_t * (*win_add_title)(lv_obj_t * win, const char * txt);
  lv_obj_t * (*win_add_btn)(lv_obj_t * win, const void * icon, lv_coord_t btn_w);
  lv_obj_t * (*win_get_header)(lv_obj_t * win);
  lv_obj_t * (*win_get_content)(lv_obj_t * win);

  //colorwheel
  lv_obj_t * (*colorwheel_create)(lv_obj_t * parent, bool knob_recolor);
  bool (*colorwheel_set_hsv)(lv_obj_t * obj, lv_color_hsv_t hsv);
  bool (*colorwheel_set_rgb)(lv_obj_t * obj, lv_color_t color);
  void (*colorwheel_set_mode)(lv_obj_t * obj, lv_colorwheel_mode_t mode);
  void (*colorwheel_set_mode_fixed)(lv_obj_t * obj, bool fixed);
  lv_color_hsv_t (*colorwheel_get_hsv)(lv_obj_t * obj);
  lv_color_t (*colorwheel_get_rgb)(lv_obj_t * obj);
  lv_colorwheel_mode_t (*colorwheel_get_color_mode)(lv_obj_t * obj);
  bool (*colorwheel_get_color_mode_fixed)(lv_obj_t * obj);

  //led
  lv_obj_t * (*led_create)(lv_obj_t * parent);
  void (*led_set_color)(lv_obj_t * led, lv_color_t color);
  void (*led_set_brightness)(lv_obj_t * led, uint8_t bright);
  void (*led_on)(lv_obj_t * led);
  void (*led_off)(lv_obj_t * led);
  void (*led_toggle)(lv_obj_t * led);
  uint8_t (*led_get_brightness)(const lv_obj_t * obj);

  //imgbtn
  lv_obj_t * (*imgbtn_create)(lv_obj_t * parent);
  void (*imgbtn_set_src)(lv_obj_t * imgbtn, lv_imgbtn_state_t state, const void * src_left, const void * src_mid,
                         const void * src_right);
  const void * (*imgbtn_get_src_left)(lv_obj_t * imgbtn, lv_imgbtn_state_t state);
  const void * (*imgbtn_get_src_middle)(lv_obj_t * imgbtn, lv_imgbtn_state_t state);
  const void * (*imgbtn_get_src_right)(lv_obj_t * imgbtn, lv_imgbtn_state_t state);

  //span
  lv_obj_t * (*spangroup_create)(lv_obj_t * par);
  lv_span_t * (*spangroup_new_span)(lv_obj_t * obj);
  void (*spangroup_del_span)(lv_obj_t * obj, lv_span_t * span);
  void (*span_set_text)(lv_span_t * span, const char * text);
  void (*span_set_text_static)(lv_span_t * span, const char * text);
  void (*spangroup_set_align)(lv_obj_t * obj, lv_text_align_t align);
  void (*spangroup_set_overflow)(lv_obj_t * obj, lv_span_overflow_t overflow);
  void (*spangroup_set_indent)(lv_obj_t * obj, lv_coord_t indent);
  void (*spangroup_set_mode)(lv_obj_t * obj, lv_span_mode_t mode);
  lv_text_align_t (*spangroup_get_align)(lv_obj_t * obj);
  lv_span_overflow_t (*spangroup_get_overflow)(lv_obj_t * obj);
  lv_coord_t (*spangroup_get_indent)(lv_obj_t * obj);
  lv_span_mode_t (*spangroup_get_mode)(lv_obj_t * obj);
  lv_coord_t (*spangroup_get_max_line_h)(lv_obj_t * obj);
  lv_coord_t (*spangroup_get_expand_width)(lv_obj_t * obj);
  lv_coord_t (*spangroup_get_expand_height)(lv_obj_t * obj, lv_coord_t width);
  void (*spangroup_refr_mode)(lv_obj_t * obj);


  //extra layouts
  //flex
  void (*flex_init)(void);
  void (*obj_set_flex_flow)(lv_obj_t * obj, lv_flex_flow_t flow);
  void (*obj_set_flex_align)(lv_obj_t * obj, lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place);
  void (*obj_set_flex_grow)(lv_obj_t * obj, uint8_t grow);
  void (*style_set_flex_flow)(lv_style_t * style, lv_flex_flow_t value);
  void (*style_set_flex_main_place)(lv_style_t * style, lv_flex_align_t value);
  void (*style_set_flex_cross_place)(lv_style_t * style, lv_flex_align_t value);
  void (*style_set_flex_track_place)(lv_style_t * style, lv_flex_align_t value);
  void (*style_set_flex_grow)(lv_style_t * style, uint8_t value);
  void (*obj_set_style_flex_flow)(lv_obj_t * obj, lv_flex_flow_t value, lv_style_selector_t selector);
  void (*obj_set_style_flex_main_place)(lv_obj_t * obj, lv_flex_align_t value, lv_style_selector_t selector);
  void (*obj_set_style_flex_cross_place)(lv_obj_t * obj, lv_flex_align_t value, lv_style_selector_t selector);
  void (*obj_set_style_flex_track_place)(lv_obj_t * obj, lv_flex_align_t value, lv_style_selector_t selector);
  void (*obj_set_style_flex_grow)(lv_obj_t * obj, uint8_t value, lv_style_selector_t selector);
  //grid
  void (*grid_init)(void);
  void (*obj_set_grid_dsc_array)(lv_obj_t * obj, const lv_coord_t col_dsc[], const lv_coord_t row_dsc[]);
  void (*obj_set_grid_align)(lv_obj_t * obj, lv_grid_align_t column_align, lv_grid_align_t row_align);
  void (*obj_set_grid_cell)(lv_obj_t * obj, lv_grid_align_t column_align, uint8_t col_pos, uint8_t col_span,
                            lv_grid_align_t row_align, uint8_t row_pos, uint8_t row_span);

  void (*style_set_grid_row_dsc_array)(lv_style_t * style, const lv_coord_t value[]);
  void (*style_set_grid_column_dsc_array)(lv_style_t * style, const lv_coord_t value[]);
  void (*style_set_grid_row_align)(lv_style_t * style, lv_grid_align_t value);
  void (*style_set_grid_column_align)(lv_style_t * style, lv_grid_align_t value);
  void (*style_set_grid_cell_column_pos)(lv_style_t * style, lv_coord_t value);
  void (*style_set_grid_cell_column_span)(lv_style_t * style, lv_coord_t value);
  void (*style_set_grid_cell_row_pos)(lv_style_t * style, lv_coord_t value);
  void (*style_set_grid_cell_row_span)(lv_style_t * style, lv_coord_t value);
  void (*style_set_grid_cell_x_align)(lv_style_t * style, lv_coord_t value);
  void (*style_set_grid_cell_y_align)(lv_style_t * style, lv_coord_t value);

  void (*obj_set_style_grid_row_dsc_array)(lv_obj_t * obj, const lv_coord_t value[], lv_style_selector_t selector);
  void (*obj_set_style_grid_column_dsc_array)(lv_obj_t * obj, const lv_coord_t value[], lv_style_selector_t selector);
  void (*obj_set_style_grid_row_align)(lv_obj_t * obj, lv_grid_align_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_column_align)(lv_obj_t * obj, lv_grid_align_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_column_pos)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_column_span)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_row_pos)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_row_span)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_x_align)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);
  void (*obj_set_style_grid_cell_y_align)(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector);


  //extra themes
  lv_theme_t * (*theme_default_init)(lv_disp_t * disp, lv_color_t color_primary, lv_color_t color_secondary, bool dark, const lv_font_t * font);
  lv_theme_t * (*theme_mono_init)(lv_disp_t * disp, bool dark_bg, const lv_font_t * font);
  lv_theme_t * (*theme_basic_init)(lv_disp_t * disp);

  //system
  const lvgl_api_font_descriptor_t * (*get_font)(int offset);

  const lv_obj_class_t * obj_class;
  const lv_obj_class_t * animation_image_class;
  const lv_obj_class_t * calendar_class;
  const lv_obj_class_t * calendar_header_arrow_class;
  const lv_obj_class_t * calendar_header_dropdown_class;
  const lv_obj_class_t * chart_class;
  const lv_obj_class_t * colorwheel_class;
  const lv_obj_class_t * dropdown_class;
  const lv_obj_class_t * image_button_class;
  const lv_obj_class_t * keyboard_class;
  const lv_obj_class_t * led_class;
  const lv_obj_class_t * list_class;
  const lv_obj_class_t * list_text_class;
  const lv_obj_class_t * list_button_class;
  const lv_obj_class_t * meter_class;
  const lv_obj_class_t * spangroup_class;
  const lv_obj_class_t * spinbox_class;
  const lv_obj_class_t * spinner_class;
  const lv_obj_class_t * tabview_class;
  const lv_obj_class_t * tileview_class;
  const lv_obj_class_t * tileview_tile_class;
  const lv_obj_class_t * window_class;
  const lv_obj_class_t * arc_class;
  const lv_obj_class_t * bar_class;
  const lv_obj_class_t * button_class;
  const lv_obj_class_t * button_matrix_class;
  const lv_obj_class_t * canvas_class;
  const lv_obj_class_t * checkbox_class;
  const lv_obj_class_t * image_class;
  const lv_obj_class_t * line_class;
  const lv_obj_class_t * label_class;
  const lv_obj_class_t * message_box_class;
  //const lv_obj_class_t * templ_class;
  const lv_obj_class_t * roller_class;
  const lv_obj_class_t * slider_class;
  const lv_obj_class_t * switch_class;
  const lv_obj_class_t * table_class;
  const lv_obj_class_t * textarea_class;


} lvgl_api_t;

extern const lvgl_api_t lvgl_api;

void lvgl_api_initialize_filesystem();

#if _LVGL_HAS_STRATIFY_OS
void lvgl_api_mount_asset_filesystem(const void * assetfs, lv_fs_drv_t* drv, char letter);
#endif

#if defined __link
#define LVGL_API_REQUEST (&lvgl_api)
void lvgl_api_set_font_callback(const lvgl_api_font_descriptor_t * (*callback)(int));
#else
#define LVGL_API_REQUEST MCU_API_REQUEST_CODE('l', 'v', 'g', 'l')
#define LVGL_REQUEST_START MCU_API_REQUEST_CODE('l', 'v', 'g', 'o')
#define LVGL_REQUEST_STOP MCU_API_REQUEST_CODE('l', 's', 't', 'p')
#define LVGL_REQUEST_GET_FONT MCU_API_REQUEST_CODE('l', 'f', 'n', 't')

typedef struct {
  u16 offset;
  const lvgl_api_font_descriptor_t * descriptor;
} lvgl_api_font_request_t;



#endif

#ifdef __cplusplus
}
#endif

#endif // LVGL_LVGL_API_H
