#include "lvgl/MessageBox.hpp"

using namespace lvgl;

MessageBox::MessageBox(Object parent, const Create &options)
  : ObjectAccess(object_type()) {
  m_object = api()->msgbox_create(
    parent.object(), options.title(), options.message(), options.button_list(),
    options.is_add_close_button());

  set_name(options.name());
}
