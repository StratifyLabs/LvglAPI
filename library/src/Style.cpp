#include "lvgl/Style.hpp"
#include "lvgl/Font.hpp"
#include "lvgl/macros.hpp"

using namespace lvgl;

Style &Style::set_text_font(const Font &value) {
  return set_property(Property::text_font, PropertyValue(value.font()));
}
