#include "lvgl/Style.hpp"
#include "lvgl/Font.hpp"

using namespace lvgl;



Style &Style::set_text_font(const Font & value) {
  lv_style_value_t v = {.ptr = value.font()};
  api()->style_set_prop(&m_style, LV_STYLE_TEXT_FONT, v);
  return *this;
}
