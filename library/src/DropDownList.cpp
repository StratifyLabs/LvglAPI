#include "lvgl/DropDownList.hpp"

using namespace lvgl;

DropDownList::DropDownList(Object parent, const DropDownList&){
  m_object = api()->dropdown_create(parent.object());
}
