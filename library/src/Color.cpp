#include <var/StringView.hpp>

#include "lvgl/Color.hpp"
#include "lvgl/Draw.hpp"

#include "lvgl/macros.hpp"

using namespace lvgl;


const char * Color::to_cstring(Palette value){
  switch (value) {
    LVGL_PROPERTY_CASE(Palette, red);
    LVGL_PROPERTY_CASE(Palette, pink);
    LVGL_PROPERTY_CASE(Palette, purple);
    LVGL_PROPERTY_CASE(Palette, deep_purple);
    LVGL_PROPERTY_CASE(Palette, indigo);
    LVGL_PROPERTY_CASE(Palette, blue);
    LVGL_PROPERTY_CASE(Palette, light_blue);
    LVGL_PROPERTY_CASE(Palette, cyan);
    LVGL_PROPERTY_CASE(Palette, teal);
    LVGL_PROPERTY_CASE(Palette, green);
    LVGL_PROPERTY_CASE(Palette, light_green);
    LVGL_PROPERTY_CASE(Palette, lime);
    LVGL_PROPERTY_CASE(Palette, yellow);
    LVGL_PROPERTY_CASE(Palette, amber);
    LVGL_PROPERTY_CASE(Palette, orange);
    LVGL_PROPERTY_CASE(Palette, deep_orange);
    LVGL_PROPERTY_CASE(Palette, brown);
    LVGL_PROPERTY_CASE(Palette, blue_grey);
    LVGL_PROPERTY_CASE(Palette, grey);
    LVGL_PROPERTY_CASE(Palette, none);
    LVGL_PROPERTY_CASE(Palette, invalid);
  }
  return "unknown";
}

Palette Color::palette_from_string(const var::StringView value){
  LVGL_PROPERTY_STRING_CASE(Palette, red);
  LVGL_PROPERTY_STRING_CASE(Palette, pink);
  LVGL_PROPERTY_STRING_CASE(Palette, purple);
  LVGL_PROPERTY_STRING_CASE(Palette, deep_purple);
  LVGL_PROPERTY_STRING_CASE(Palette, indigo);
  LVGL_PROPERTY_STRING_CASE(Palette, blue);
  LVGL_PROPERTY_STRING_CASE(Palette, light_blue);
  LVGL_PROPERTY_STRING_CASE(Palette, cyan);
  LVGL_PROPERTY_STRING_CASE(Palette, teal);
  LVGL_PROPERTY_STRING_CASE(Palette, green);
  LVGL_PROPERTY_STRING_CASE(Palette, light_green);
  LVGL_PROPERTY_STRING_CASE(Palette, lime);
  LVGL_PROPERTY_STRING_CASE(Palette, yellow);
  LVGL_PROPERTY_STRING_CASE(Palette, amber);
  LVGL_PROPERTY_STRING_CASE(Palette, orange);
  LVGL_PROPERTY_STRING_CASE(Palette, deep_orange);
  LVGL_PROPERTY_STRING_CASE(Palette, brown);
  LVGL_PROPERTY_STRING_CASE(Palette, blue_grey);
  LVGL_PROPERTY_STRING_CASE(Palette, grey);
  LVGL_PROPERTY_STRING_CASE(Palette, none);
  return Palette::invalid;
}