#include "lvgl/Dropdown.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Dropdown);


Dropdown::Dropdown(const char * name){
  construct_dropdown(name);
}
