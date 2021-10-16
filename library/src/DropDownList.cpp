#include "lvgl/DropDownList.hpp"

using namespace lvgl;

DropDownList::DropDownList(const char * name){
  m_object = api()->dropdown_create(screen_object());
  set_user_data(m_object,name);
}
