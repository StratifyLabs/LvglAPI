#include <printer/Printer.hpp>
#include <var/StackString.hpp>

#include "lvgl/Bar.hpp"

namespace printer {
Printer &operator<<(Printer &printer, const lvgl::Range &range) {
  return printer.key("minimum", var::NumberString(range.minimum()))
    .key("value", var::NumberString(range.value()))
    .key("maximum", var::NumberString(range.maximum()));
}
} // namespace printer

using namespace lvgl;

Bar::Bar(const char * name){
  m_object = api()->bar_create(screen_object());
  set_user_data(m_object,name);
}

Bar &Bar::set_mode(Bar::Mode value) {
  api()->bar_set_mode(m_object, static_cast<lv_bar_mode_t>(value));
  return *this;
}
