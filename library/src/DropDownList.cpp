#include "lvgl/DropDownList.hpp"

using namespace lvgl;

DropDownList::DropDownList(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->dropdown_create(parent.object());
  set_name(options.name());
}
