//
// Created by Tyler Gilbert on 12/8/21.
//

#include <printer/Printer.hpp>
#include <var/StackString.hpp>

#include "lvgl/Types.hpp"

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const lvgl::Size &a) {
  return printer.key("width", var::NumberString(a.width()))
    .key("height", var::NumberString(a.height()));
}
Printer &operator<<(Printer &printer, const lvgl::Point &a){
  return printer.key("x", var::NumberString(a.x()))
    .key("y", var::NumberString(a.y()));
}
Printer &operator<<(Printer &printer, const lvgl::Area &a){
  return printer.object("point", a.get_point())
    .object("size", a.get_size());
}
} // namespace printer