#include "lvgl/Theme.hpp"

using namespace lvgl;

const lv_style_t *Theme::find(const var::StringView name) const {
  using Callback = lvgl_api_style_descriptor_t *(*)(int);
  Callback callback = reinterpret_cast<Callback>(native_value()->user_data);
  if( callback == nullptr ){
    return nullptr;
  }

  int offset = 0;
  lvgl_api_style_descriptor_t * descriptor;
  do {
    descriptor = callback(offset++);
    if( descriptor && (name == descriptor->name) ){
      return descriptor->style;
    }
  } while( descriptor != nullptr );

  return nullptr;

}