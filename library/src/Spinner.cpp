#include "lvgl/Spinner.hpp"

using namespace lvgl;

Spinner::Spinner(Object parent, const Spinner &options) {
  m_object = api()->spinner_create(
    parent.object(), options.m_construct->time(), options.m_construct->arc_length());
}
