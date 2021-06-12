#include "lvgl/Font.hpp"


using namespace lv;

Font::Font(const var::PathString & path){
  m_font = api()->font_load(path.cstring());
  if( m_font ){
    m_is_loaded = true;
  }
}

Font::~Font(){
  if( m_is_loaded && m_font ){
    api()->font_free((lv_font_t*)m_font);
  }
}
