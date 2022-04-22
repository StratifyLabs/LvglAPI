#include "lvgl/Screen.hpp"
#include "lvgl/macros.hpp"

using namespace lvgl;

var::Vector<lv_obj_t*> Screen::m_screen_list;

Screen::Screen(const char * name) {
  if( m_screen_list.count() == 0 ){
    //add the default screen
    auto active_screen = api()->disp_get_scr_act(nullptr);
    m_screen_list.push_back(active_screen);
    set_user_data(active_screen, "default");
  }

  m_object = api()->obj_create(nullptr);
  set_user_data(m_object, name);
  for(auto & entry: m_screen_list){
    if( entry == nullptr ){
      entry = m_object;
      return;
    }
  }
  m_screen_list.push_back(m_object);
}

void Screen::remove_screen(const char *name) {
  for(auto & entry: m_screen_list){
    if( entry != nullptr ){
      auto s = Screen(entry);
      const var::StringView s_name = s.name();
      if( s_name == name && s_name != "default"){
        s.async_remove();
        entry = nullptr;
        return;
      }
    }
  }
}

Screen Screen::find_screen(const char *name) {
  for(auto & entry: m_screen_list){
    if( entry != nullptr ){
      auto s = Screen(entry);
      if( var::StringView(s.name()) == name ){
        return s;
      }
    }
  }
  return Screen((lv_obj_t*)nullptr);
}


const char * Screen::to_cstring(LoadAnimation value){
  switch (value) {
    LVGL_PROPERTY_CASE(LoadAnimation, none);
    LVGL_PROPERTY_CASE(LoadAnimation, over_left);
    LVGL_PROPERTY_CASE(LoadAnimation, over_right);
    LVGL_PROPERTY_CASE(LoadAnimation, over_top);
    LVGL_PROPERTY_CASE(LoadAnimation, over_bottom);
    LVGL_PROPERTY_CASE(LoadAnimation, move_left);
    LVGL_PROPERTY_CASE(LoadAnimation, move_right);
    LVGL_PROPERTY_CASE(LoadAnimation, move_top);
    LVGL_PROPERTY_CASE(LoadAnimation, move_bottom);
    LVGL_PROPERTY_CASE(LoadAnimation, fade_on);
  }
  return "unknown";
}

Screen::LoadAnimation Screen::get_load_animation(var::StringView value){
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, over_left);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, over_right);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, over_top);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, over_bottom);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, move_left);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, move_right);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, move_top);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, move_bottom);
  LVGL_PROPERTY_STRING_CASE(LoadAnimation, fade_on);
  return LoadAnimation::none;
}