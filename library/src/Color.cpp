#include <var/StringView.hpp>

#include "lvgl/Color.hpp"
#include "lvgl/Draw.hpp"

using namespace lvgl;


#define COLOR_CASE(x, y)                                                              \
  case x::y:                                                                             \
    return MCU_STRINGIFY(y)

#define COLOR_STRING_CASE(x, y)                                                       \
  if (value_stringview == MCU_STRINGIFY(y)) {                                            \
    return x::y;                                                                         \
  }

const char * Color::to_cstring(Palette value){
  switch (value) {
    COLOR_CASE(Palette, red);
    COLOR_CASE(Palette, pink);
    COLOR_CASE(Palette, purple);
    COLOR_CASE(Palette, deep_purple);
    COLOR_CASE(Palette, indigo);
    COLOR_CASE(Palette, blue);
    COLOR_CASE(Palette, light_blue);
    COLOR_CASE(Palette, cyan);
    COLOR_CASE(Palette, teal);
    COLOR_CASE(Palette, green);
    COLOR_CASE(Palette, light_green);
    COLOR_CASE(Palette, lime);
    COLOR_CASE(Palette, yellow);
    COLOR_CASE(Palette, amber);
    COLOR_CASE(Palette, orange);
    COLOR_CASE(Palette, deep_orange);
    COLOR_CASE(Palette, brown);
    COLOR_CASE(Palette, blue_grey);
    COLOR_CASE(Palette, grey);
    COLOR_CASE(Palette, none);
    COLOR_CASE(Palette, invalid);
  }
  return "unknown";
}

Palette Color::palette_from_cstring(const char * value){
  const var::StringView value_stringview = value;
  COLOR_STRING_CASE(Palette, red);
  COLOR_STRING_CASE(Palette, pink);
  COLOR_STRING_CASE(Palette, purple);
  COLOR_STRING_CASE(Palette, deep_purple);
  COLOR_STRING_CASE(Palette, indigo);
  COLOR_STRING_CASE(Palette, blue);
  COLOR_STRING_CASE(Palette, light_blue);
  COLOR_STRING_CASE(Palette, cyan);
  COLOR_STRING_CASE(Palette, teal);
  COLOR_STRING_CASE(Palette, green);
  COLOR_STRING_CASE(Palette, light_green);
  COLOR_STRING_CASE(Palette, lime);
  COLOR_STRING_CASE(Palette, yellow);
  COLOR_STRING_CASE(Palette, amber);
  COLOR_STRING_CASE(Palette, orange);
  COLOR_STRING_CASE(Palette, deep_orange);
  COLOR_STRING_CASE(Palette, brown);
  COLOR_STRING_CASE(Palette, blue_grey);
  COLOR_STRING_CASE(Palette, grey);
  COLOR_STRING_CASE(Palette, none);
  return Palette::invalid;
}