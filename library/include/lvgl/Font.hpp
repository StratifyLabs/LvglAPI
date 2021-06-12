#ifndef LVGLAPI_LVGL_FONT_HPP
#define LVGLAPI_LVGL_FONT_HPP

#include <algorithm>
#include <var/StackString.hpp>

#include "Style.hpp"

namespace lv {

class Font : public Api
{
public:
  Font() = default;
  Font(const lv_font_t * font) : m_font(font){}
  Font(const var::PathString & path);
  ~Font();
  Font(const Font &) = delete;
  Font& operator=(const Font &) = delete;
  Font& operator=(Font && font){
    std::swap(m_font, font.m_font);
    std::swap(m_is_loaded, font.m_is_loaded);
    return *this;
  }
  Font(Font && font){
    std::swap(m_font, font.m_font);
    std::swap(m_is_loaded, font.m_is_loaded);
  }

  const lv_font_t * font() const {
    return m_font;
  }

private:
  const lv_font_t * m_font = nullptr;
  bool m_is_loaded = false;

};

}

#endif // FONT_HPP
