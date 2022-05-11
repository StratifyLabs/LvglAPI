#include "lvgl/Switch.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Switch);

Switch::Switch(const char * name){
  construct_switch(name);
}
