#ifndef LVGLAPI_LVGL_SCREEN_HPP
#define LVGLAPI_LVGL_SCREEN_HPP

#include "Event.hpp"
#include "Theme.hpp"

namespace lvgl {

class Screen : public Object {
public:

  Screen(const char *name);

  explicit Screen(lv_obj_t *value) { m_object = value; }

  enum class IsAutoRemove { no, yes };

  Screen &load() {
    api()->disp_load_scr(m_object);
    return *this;
  }

  Screen &load(
    LoadAnimation animation,
    chrono::MicroTime period,
    chrono::MicroTime delay,
    IsAutoRemove is_auto_remove) {
    execute_load(animation, period, delay, is_auto_remove);
    return *this;
  }

  struct Transition {
    API_PUBLIC_MEMBER_AZ(animation, Transition, LoadAnimation, LoadAnimation::none);
    API_PUBLIC_MEMBER_AZ(delay, Transition, chrono::MicroTime, chrono::MicroTime());
    API_PUBLIC_MEMBER_AZ(period, Transition, chrono::MicroTime, chrono::MicroTime());
  };

  Screen &
  load(const Transition &transition, IsAutoRemove is_auto_remove = IsAutoRemove::no) {
    execute_load(
      transition.animation, transition.period, transition.delay, is_auto_remove);
    return *this;
  }

  static void remove_screen(const char *name);
  static Screen find_screen(const char *name);

  static var::Vector<lv_obj_t *> &screen_list();

  static constexpr auto default_name = "default";

private:
  void execute_load(
    LoadAnimation animation,
    chrono::MicroTime period,
    chrono::MicroTime delay,
    IsAutoRemove is_auto_remove) {
    Event::send(Screen(api()->disp_get_scr_act(nullptr)), EventCode::exited);
    api()->scr_load_anim(
      m_object, lv_scr_load_anim_t(animation), period.milliseconds(),
      delay.milliseconds(), bool(is_auto_remove));
    Event::send(Screen(m_object), EventCode::entered);
  }
};

class Display : public Api {
public:
  explicit Display(lv_disp_t *value) : m_display(value) {}

  Screen get_active_screen() { return Screen(api()->disp_get_scr_act(m_display)); }
  Screen get_previous_screen() { return Screen(api()->disp_get_scr_prev(m_display)); }

  API_NO_DISCARD Object get_top_layer() const {
    return Object(api()->disp_get_layer_top(m_display));
  }

  API_NO_DISCARD Object get_system_layer() const {
    return Object(api()->disp_get_layer_sys(m_display));
  }

  API_NO_DISCARD chrono::MicroTime get_inactive_time() const {
    return chrono::MicroTime(api()->disp_get_inactive_time(m_display) * 1000);
  }

  Display &load(Screen value) {
    api()->disp_load_scr(value.object());
    return *this;
  }

  Display &trigger_activity() {
    api()->disp_trig_activity(m_display);
    return *this;
  }

  Display &clean_data_cache() {
    api()->disp_clean_dcache(m_display);
    return *this;
  }

  Display &set_background_color(Color value) {
    api()->disp_set_bg_color(m_display, value.get_color());
    return *this;
  }

  Display &set_background_image(const void *value) {
    api()->disp_set_bg_image(m_display, value);
    return *this;
  }

  Display &set_background_opacity(Opacity value) {
    api()->disp_set_bg_opa(m_display, lv_opa_t(value));
    return *this;
  }

  Display &set_theme(Theme value) {
    api()->disp_set_theme(m_display, value.native_value());
    return *this;
  }

  void remove() { api()->disp_remove(m_display); }

  Display &set_default() {
    api()->disp_set_default(m_display);
    return *this;
  }

  static Display get_default() { return Display(api()->disp_get_default()); }

  API_NO_DISCARD lv_coord_t get_horizontal_resolution() const {
    return api()->disp_get_hor_res(m_display);
  }

  API_NO_DISCARD lv_coord_t get_vertical_resolution() const {
    return api()->disp_get_ver_res(m_display);
  }

  API_NO_DISCARD bool is_antialiasing() const {
    return api()->disp_get_antialiasing(m_display);
  }

  API_NO_DISCARD lv_coord_t get_dots_per_inch() const {
    return api()->disp_get_dpi(m_display);
  }

  enum class Rotation {
    none = LV_DISP_ROT_NONE,
    x90 = LV_DISP_ROT_90,
    x180 = LV_DISP_ROT_180,
    x270 = LV_DISP_ROT_270
  };

  Display &set_rotation(Rotation value) {
    api()->disp_set_rotation(m_display, lv_disp_rot_t(value));
    return *this;
  }

  API_NO_DISCARD Rotation get_rotation() const {
    return Rotation(api()->disp_get_rotation(m_display));
  }

  API_NO_DISCARD Theme get_theme() const {
    return Theme(api()->disp_get_theme(m_display));
  }

private:
  lv_disp_t *m_display;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_SCREEN_HPP
