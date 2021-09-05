#include "lvgl/Button.hpp"

using namespace lvgl;


Button::Button(Object parent, const Button &){
  m_object = api()->btn_create(parent.object());
}


Button::Button(Object parent, const Create & options){
  m_object = api()->btn_create(parent.object());
  set_name(options.name());
}
