#include "lvgl/Animation.hpp"

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
    }
    return api()->anim_path_linear;
  }();

  lv_anim_set_path_cb(&m_anim, callback);
  return *this;
}
