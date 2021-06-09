#include "lvgl/Label.hpp"

using namespace lv;

Label::Label(const char* name){
  m_object = api()->label_create(lv_scr_act());
  set_name(name);
}
