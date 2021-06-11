#include "lvgl/Spinner.hpp"

using namespace lv;

Spinner::Spinner(Object parent, const Create &options) {
  m_object = api()->spinner_create(parent.object(), options.time(), options.arc_length());
  set_name(options.name());
}
