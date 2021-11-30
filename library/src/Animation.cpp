#include "lvgl/Animation.hpp"
#include "lvgl/macros.hpp"

using namespace lvgl;

Animation & Animation::set_path(Path path){
  const auto callback = [&](){
    switch(path){
    case Path::linear: return api()->anim_path_linear;
    case Path::ease_in: return api()->anim_path_ease_in;
    case Path::ease_out: return api()->anim_path_ease_out;
    case Path::ease_in_out: return api()->anim_path_ease_in_out;
    case Path::bounce: return api()->anim_path_bounce;
    case Path::overshoot: return api()->anim_path_overshoot;
    case Path::step: return api()->anim_path_step;
    case Path::invalid: return api()->anim_path_linear;
    }
    return api()->anim_path_linear;
  }();

  lv_anim_set_path_cb(&m_anim, callback);
  return *this;
}


Animation::Path Animation::path_from_cstring(const char * value){
  const var::StringView value_stringview = value;
  LVGL_PROPERTY_STRING_CASE(Path, linear);
  LVGL_PROPERTY_STRING_CASE(Path, step);
  LVGL_PROPERTY_STRING_CASE(Path, ease_in);
  LVGL_PROPERTY_STRING_CASE(Path, ease_out);
  LVGL_PROPERTY_STRING_CASE(Path, ease_in_out);
  LVGL_PROPERTY_STRING_CASE(Path, overshoot);
  LVGL_PROPERTY_STRING_CASE(Path, bounce);
  return Path::invalid;
}

const char * Animation::to_cstring(Path value){
  switch (value) {
    LVGL_PROPERTY_CASE(Path, linear);
    LVGL_PROPERTY_CASE(Path, step);
    LVGL_PROPERTY_CASE(Path, ease_in);
    LVGL_PROPERTY_CASE(Path, ease_out);
    LVGL_PROPERTY_CASE(Path, ease_in_out);
    LVGL_PROPERTY_CASE(Path, overshoot);
    LVGL_PROPERTY_CASE(Path, bounce);
    LVGL_PROPERTY_CASE(Path, invalid);
  }
}