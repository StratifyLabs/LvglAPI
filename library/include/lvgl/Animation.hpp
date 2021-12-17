#ifndef LVGLAPI_LVGL_ANIMATION_HPP
#define LVGLAPI_LVGL_ANIMATION_HPP

#include "Object.hpp"

namespace lvgl {

class Animation : public Api {
public:
  using Callback = void (*)(void *, s32);
  using ReadyCallback = void (*)(_lv_anim_t *);
  using GetValueCallback = s32 (*)(_lv_anim_t *);

  static constexpr u16 repeat_infinite = LV_ANIM_REPEAT_INFINITE;

  enum class Path {
    linear,
    step,
    ease_in,
    ease_out,
    ease_in_out,
    overshoot,
    bounce,
    invalid
  };

  static Path path_from_string(const var::StringView value);
  static const char * to_cstring(Path value);

  Animation() { api()->anim_init(&m_anim); }

  Animation &set_values(s32 start, s32 end) {
    lv_anim_set_values(&m_anim, start, end);
    return *this;
  }

  Animation &set_callback(void *context, Callback callback) {
    lv_anim_set_var(&m_anim, context);
    lv_anim_set_exec_cb(&m_anim, callback);
    return *this;
  }


  Animation &set_callback(Object object, Callback callback) {
    lv_anim_set_var(&m_anim, object.object());
    lv_anim_set_exec_cb(&m_anim, callback);
    return *this;
  }

  Animation & set_path(Path path);

  Animation &set_ready_callback(ReadyCallback callback) {
    lv_anim_set_ready_cb(&m_anim, callback);
    return *this;
  }

  Animation &set_get_value_callback(GetValueCallback callback) {
    lv_anim_set_get_value_cb(&m_anim, callback);
    return *this;
  }

  Animation &set_time(chrono::MicroTime duration) {
    lv_anim_set_time(&m_anim, duration.milliseconds());
    return *this;
  }

  Animation &set_repeat_delay(chrono::MicroTime duration) {
    lv_anim_set_repeat_delay(&m_anim, duration.milliseconds());
    return *this;
  }

  Animation &set_playback_delay(chrono::MicroTime duration) {
    lv_anim_set_playback_delay(&m_anim, duration.milliseconds());
    return *this;
  }

  Animation &set_repeat_count(u16 count) {
    lv_anim_set_repeat_count(&m_anim, count);
    return *this;
  }

  Animation &start() {
    m_active_anim = api()->anim_start(&m_anim);
    return *this;
  }

  static void refresh_now(){
    api()->anim_refr_now();
  }

private:
  lv_anim_t m_anim;
  lv_anim_t *m_active_anim;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_ANIMATION_HPP
