#ifndef LVGLAPI_LVGL_THEME_HPP
#define LVGLAPI_LVGL_THEME_HPP

#include "Object.hpp"
#include "Font.hpp"

namespace lv {

class Theme : public Api {
public:
  Theme(){
    m_theme = api()->theme_get_from_obj(nullptr);
  }

  Theme& apply(Object object){
    api()->theme_apply(object.object());
    return *this;
  }

  static Theme get_theme(Object object){
    return Theme(api()->theme_get_from_obj(object.object()));
  }

  Theme & set_small_font(const Font & font){
    m_theme->font_small = font.font();
    return *this;
  }

  Theme & set_normal_font(const Font & font){
    m_theme->font_normal = font.font();
    return *this;
  }

  Theme & set_large_font(const Font & font){
    m_theme->font_large = font.font();
    return *this;
  }


private:
  Theme(lv_theme_t * theme) : m_theme(theme){}
  lv_theme_t * m_theme = nullptr;
};

}

#endif // LVGLAPI_LVGL_THEME_HPP
