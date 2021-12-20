#include "lvgl/ColorPicker.hpp"

using namespace lvgl;

ColorPicker::ColorWheel(const char * name){
  api()->colorwh
  set_user_data(m_object,name);

}
