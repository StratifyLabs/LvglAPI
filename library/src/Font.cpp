#if defined __StratifyOS__
#include <sos.hpp>
#endif

#include <printer/Printer.hpp>
#include <var/StackString.hpp>

#include "lvgl/Font.hpp"

namespace printer {
Printer &operator<<(Printer &printer, const lvgl::Font::Info &a) {
  return printer.key("name", a.name())
    .key("pointSize", var::NumberString(a.point_size()))
    .key("style", lvgl::Font::to_cstring(a.style()));
}
} // namespace printer

using namespace lvgl;

#define STYLE_CASE(x)                                                                    \
  case Style::x:                                                                         \
    return MCU_STRINGIFY(x)

const char * Font::to_cstring(Style style) {
  switch (style) {
    STYLE_CASE(any);
    STYLE_CASE(thin);
    STYLE_CASE(thin_italic);
    STYLE_CASE(extra_light);
    STYLE_CASE(extra_light_italic);
    STYLE_CASE(light);
    STYLE_CASE(light_italic);
    STYLE_CASE(regular);
    STYLE_CASE(regular_italic);
    STYLE_CASE(medium);
    STYLE_CASE(medium_italic);
    STYLE_CASE(semi_bold);
    STYLE_CASE(semi_bold_italic);
    STYLE_CASE(bold);
    STYLE_CASE(bold_italic);
    STYLE_CASE(extra_bold);
    STYLE_CASE(extra_bold_italic);
    STYLE_CASE(icons);
  }

  return "unknown";
}

#if USE_FILE_FONT
Font::Font(const var::PathString &path) {
  m_font = api()->font_load(path.cstring());
  if (m_font) {
    m_is_loaded = true;
  }
}

Font::~Font() {
  if (m_is_loaded && m_font) {
    api()->font_free((lv_font_t *)m_font);
  }
}
#endif

Font::Info::Info(const char *path) {
  const auto parts = var::StringView(path).split("-");

  if (parts.count() != 3) {
    m_point_size = 0;
    return;
  }

  m_name = parts.at(0);
  m_point_size = parts.at(2).to_integer();

  m_style = [](const var::StringView value) -> Style {
    if (value == "t") {
      return Style::thin;
    }
    if (value == "ti") {
      return Style::thin_italic;
    }
    if (value == "el") {
      return Style::extra_light;
    }
    if (value == "eli") {
      return Style::extra_light_italic;
    }
    if (value == "l") {
      return Style::light;
    }
    if (value == "li") {
      return Style::light_italic;
    }
    if (value == "r") {
      return Style::regular;
    }
    if (value == "ri") {
      return Style::thin;
    }
    if (value == "m") {
      return Style::medium;
    }
    if (value == "mi") {
      return Style::medium_italic;
    }
    if (value == "sb") {
      return Style::semi_bold;
    }
    if (value == "sbi") {
      return Style::semi_bold_italic;
    }
    if (value == "b") {
      return Style::bold;
    }
    if (value == "bi") {
      return Style::bold_italic;
    }
    if (value == "eb") {
      return Style::extra_bold;
    }
    if (value == "ebi") {
      return Style::extra_bold_italic;
    }
    if (value == "ico") {
      return Style::icons;
    }
    return Style::any;
  }(parts.at(1));
}

Font::Info Font::find_best_fit(const Info &info) {

  const auto count = []() {
    int offset = 0;
    while (api()->get_font(offset) != nullptr) {
      offset++;
    }
    return offset;
  }();

  if (count == 0) {
    return Info();
  }

  const lvgl_api_font_descriptor_t *descriptor_list[count];
  {
    for(int offset = 0; offset < count; offset++){
      descriptor_list[offset] = api()->get_font(offset);
    }
  }

  u16 point_size_difference = 65535;
  u16 best_offset = 0;

  for (u16 i = 0; i < count; i++) {
    const Info font_info(descriptor_list[i]->name);
    // check if name is compatible
    if (info.name().is_empty() || info.name() == font_info.name()) {

      // check it style is compatible
      if ((info.style() == Style::any) || (info.style() == font_info.style())) {
        // now find the best size -- closest point size without going over
        if (font_info.point_size() <= info.point_size()) {
          const auto difference = info.point_size() - font_info.point_size();
          if (difference < point_size_difference) {
            point_size_difference = difference;
            best_offset = i;
          }
        }
      }
    }
  }

  return Info(descriptor_list[best_offset]->name)
    .set_font(descriptor_list[best_offset]->font);
}

