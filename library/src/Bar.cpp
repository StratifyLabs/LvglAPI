#include <printer/Printer.hpp>
#include <var/StackString.hpp>

#include "lvgl/Bar.hpp"

namespace printer {
Printer &operator<<(Printer &printer, const lvgl::Range &range) {
  return printer.key("minimim", var::NumberString(range.minimum()))
    .key("value", var::NumberString(range.value()))
    .key("maximum", var::NumberString(range.maximum()));
}
} // namespace printer

using namespace lvgl;

Bar::Bar(const char * name){
  m_object = api()->bar_create(screen_object());
  set_user_data(m_object,name);
}
