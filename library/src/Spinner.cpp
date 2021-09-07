#include "lvgl/Spinner.hpp"

using namespace lvgl;

Spinner::Spinner(Object parent, const Spinner &options){
  m_object = api()->spinner_create(parent.object(), options.initial_time(), options.initial_arc_length());
}
