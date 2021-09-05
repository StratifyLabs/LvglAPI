#include "lvgl/Spinner.hpp"

using namespace lvgl;

Spinner::Spinner(Object parent, const Create &options){
  m_object = api()->spinner_create(parent.object(), options.time(), options.arc_length());
  set_name(options.name());
}

Spinner::Spinner(Object parent, const Spinner &options){
  m_object = api()->spinner_create(parent.object(), options.time(), options.arc_length());
  set_name(options.name());
}
