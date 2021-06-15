#ifndef COLOR_HPP
#define COLOR_HPP

#include "Style.hpp"

namespace lv {

enum class Palette {
  red = LV_PALETTE_RED,
  pink = LV_PALETTE_PINK,
  purple = LV_PALETTE_PURPLE,
  deep_purple = LV_PALETTE_DEEP_PURPLE,
  indigo = LV_PALETTE_INDIGO,
  blue = LV_PALETTE_BLUE,
  light_blue = LV_PALETTE_LIGHT_BLUE,
  cyan = LV_PALETTE_CYAN,
  teal = LV_PALETTE_TEAL,
  green = LV_PALETTE_GREEN,
  light_green = LV_PALETTE_LIGHT_GREEN,
  lime = LV_PALETTE_LIME,
  yellow = LV_PALETTE_YELLOW,
  amber = LV_PALETTE_AMBER,
  orange = LV_PALETTE_ORANGE,
  deep_orange = LV_PALETTE_DEEP_ORANGE,
  brown = LV_PALETTE_BROWN,
  blue_grey = LV_PALETTE_BLUE_GREY,
  grey = LV_PALETTE_GREY,
  none = LV_PALETTE_NONE,
};

enum class PaletteLevel {
  darken_x4 = -4,
  darken_x3 = -3,
  darken_x2 = -2,
  darken_x1 = -1,
  default_ = 0,
  lighten_x1 = 1,
  lighten_x2 = 2,
  lighten_x3 = 3,
  lighten_x4 = 4
};

class Color : public Api {
public:
  class Rgb {
    API_AF(Rgb, u8, red, 0);
    API_AF(Rgb, u8, green, 0);
    API_AF(Rgb, u8, blue, 0);
    API_AF(Rgb, u8, alpha, 255);
  };

  class Hsv {
  public:
    Hsv() = default;
    Hsv(lv_color_hsv_t value) : m_hsv(value) {}
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u16, hsv, hue, h)
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u8, hsv, saturation, s)
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u8, hsv, value, v)
  private:
    lv_color_hsv_t m_hsv{};
  };

  Color();

  Color(u32 hex_value) { m_color = lv_color_hex(hex_value); }

  Color(lv_color_t color) : m_color(color) {}
  Color(const Rgb &rgb) { m_color = lv_color_make(rgb.red(), rgb.green(), rgb.blue()); }
  Color(const Hsv &hsv) {
    m_color = api()->color_hsv_to_rgb(hsv.hue(), hsv.saturation(), hsv.value());
  }

  static Color get_palette(Palette palette, PaletteLevel level = PaletteLevel::default_) {
    const auto l = static_cast<int>(level);
    const auto p = static_cast<lv_palette_t>(palette);
    if( l < 0 ){
      return Color(api()->palette_darken(p, -1*l));
    } else if ( l > 0 ){
      return Color(api()->palette_lighten(p, l));
    }
    return Color(api()->palette_main(p));
  }

  Color &lighten(u8 level) {
    m_color = lv_color_mix(lv_color_white(), m_color, level);
    return *this;
  }

  Color &darken(u8 level) {
    m_color = lv_color_mix(lv_color_black(), m_color, level);
    return *this;
  }

  Color &mix(Color color, u8 ratio) {
    m_color = lv_color_mix(m_color, color.get_color(), ratio);
    return *this;
  }

  u8 brightness() const { return lv_color_brightness(m_color); }

  lv_color_t get_color() const { return m_color; }

  Hsv to_hsv() const { return Hsv(api()->color_to_hsv(m_color)); }

private:
  lv_color_t m_color;
};

} // namespace lv

#endif // COLOR_HPP
