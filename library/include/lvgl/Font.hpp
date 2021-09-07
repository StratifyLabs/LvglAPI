#ifndef LVGLAPI_LVGL_FONT_HPP
#define LVGLAPI_LVGL_FONT_HPP

#include <algorithm>
#include <var/StackString.hpp>

#include "Style.hpp"

namespace lvgl {

class Font : public Api {
public:
  Font() = default;
  Font(const lv_font_t *font) : m_font(font) {}
  Font(const var::PathString &path);

  const lv_font_t *font() const { return m_font; }


  enum class Style {
    any,
    thin /*! Thin font (t) */,
    thin_italic /*! Thin italic (ti) */,
    extra_light /*! Extra light (el) */,
    extra_light_italic /*! Extra light italic (eli) */,
    light /*! Light (l) */,
    light_italic /*! Light italic (li) */,
    regular /*! Regular (r) */,
    regular_italic /*! Regular Italic (ri) */,
    medium /*! Medium (m) */,
    medium_italic /*! Medium italic (mi) */,
    semi_bold /*! Semi bold (sb) */,
    semi_bold_italic /*! Semi bold italic (sbi) */,
    bold /*! Bold (b) */,
    bold_italic /*! Bold italic (bi) */,
    extra_bold /*! Extra bold (eb) */,
    extra_bold_italic /*! Extra bold italic (ebi) */,
    icons /*! Font is a collection of bitmap icons (ico) */,
  };

  static const char* to_cstring(Style style);

  class Info {
  public:
    /* Using Info() = default; causes problems with
     * the following code
     *
     * int function(){
     *   static const auto font_info = Font::Info();
     * }
     *
     * It causes a crash on ARM Cortex M7. The problem
     * is with the var::NameString member. It seems
     * it doesn't get moved correctly.
     *
     */

    Info(){};
    explicit Info(const char * path);
    Font get_font() const {
      return Font(font());
    }

    bool is_valid() const {
      return point_size() > 0;
    }

    const Font operator()() const {
      return get_font();
    }

  private:
    API_AF(Info,const lv_font_t*, font, nullptr);
    API_AF(Info,Style,style,Style::any);
    API_AF(Info,u16,point_size,0);
    API_AC(Info,var::NameString,name);
  };

#if defined __StratifyOS__

  static Info find_best_fit(const Info & info);

  static Info find(const char * name, size_t point_size, Style style = Style::any){
    return find_best_fit(Info().set_name(name).set_point_size(point_size).set_style(style));
  }

  static Info find(size_t point_size, Style style = Style::any){
    return find_best_fit(Info().set_point_size(point_size).set_style(style));
  }

#endif

private:
  const lv_font_t *m_font = nullptr;
};

} // namespace lvgl

namespace printer {
Printer & operator<<(Printer & printer, const lvgl::Font::Info & a);
}

#endif // FONT_HPP
