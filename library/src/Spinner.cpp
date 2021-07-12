#include "lvgl/Spinner.hpp"

using namespace lvgl;

Spinner::Spinner(Object parent, const Create &options) : ObjectAccess(object_type()){
  m_object = api()->spinner_create(parent.object(), options.time(), options.arc_length());
  set_name(options.name());
}
