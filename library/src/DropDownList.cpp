#include "lvgl/DropDownList.hpp"

using namespace lv;

DropDownList::DropDownList(Object parent, const Create& options){
  m_object = api()->dropdown_create(parent.object());
  set_name(options.name());
}
