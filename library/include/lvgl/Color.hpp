#ifndef COLOR_HPP
#define COLOR_HPP

#include "Types.hpp"

namespace lvgl {

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
    explicit Hsv(lv_color_hsv_t value) : m_hsv(value) {}
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u16, hsv, hue, h)
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u8, hsv, saturation, s)
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Hsv, u8, hsv, value, v)
  private:
    lv_color_hsv_t m_hsv{};
  };

  Color();

  constexpr explicit Color(lv_color_t color) : m_color(color) {}

  explicit Color(const Rgb &rgb)
    : m_color(lv_color_make(rgb.red(), rgb.green(), rgb.blue())) {}
  explicit Color(const Hsv &hsv)
    : m_color(api()->color_hsv_to_rgb(hsv.hue(), hsv.saturation(), hsv.value())) {}

  static Color from_hex(u32 hex_value){
    return Color{lv_color_hex(hex_value)};
  }

  static Color get_palette(Palette palette, PaletteLevel level = PaletteLevel::default_) {
    const auto l = int(level);
    const auto p = lv_palette_t(palette);
    if (l < 0) {
      return Color(api()->palette_darken(p, -1 * l));
    } else if (l > 0) {
      return Color(api()->palette_lighten(p, l));
    }
    return Color(api()->palette_main(p));
  }

  Color &lighten(MixRatio ratio) {
    m_color = lv_color_mix(lv_color_white(), m_color, u8(ratio));
    return *this;
  }

  Color &darken(MixRatio ratio) {
    m_color = lv_color_mix(lv_color_black(), m_color, u8(ratio));
    return *this;
  }

  Color &mix(Color color, MixRatio ratio) {
    m_color = lv_color_mix(m_color, color.get_color(), u8(ratio));
    return *this;
  }

  u8 brightness() const { return lv_color_brightness(m_color); }

  lv_color_t get_color() const { return m_color; }

  Hsv to_hsv() const { return Hsv(api()->color_to_hsv(m_color)); }

  static Color red(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::red, level);
  }
  static Color pink(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::pink, level);
  }
  static Color purple(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::purple, level);
  }
  static Color deep_purple(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::deep_purple, level);
  }
  static Color indigo(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::indigo, level);
  }
  static Color blue(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::blue, level);
  }
  static Color light_blue(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::light_blue, level);
  }
  static Color cyan(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::cyan, level);
  }
  static Color teal(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::teal, level);
  }
  static Color green(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::green, level);
  }
  static Color light_green(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::light_green, level);
  }
  static Color lime(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::lime, level);
  }
  static Color yellow(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::yellow, level);
  }
  static Color amber(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::amber, level);
  }
  static Color orange(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::orange, level);
  }
  static Color deep_orange(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::deep_orange, level);
  }
  static Color brown(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::brown, level);
  }
  static Color grey(PaletteLevel level = PaletteLevel::default_) {
    return get_palette(Palette::grey, level);
  }

private:
  lv_color_t m_color{};
};

} // namespace lvgl

#endif // COLOR_HPP
