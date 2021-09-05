#include "lvgl/MessageBox.hpp"

using namespace lvgl;

MessageBox::MessageBox(Object parent, const MessageBox &options)
  : ObjectAccess(object_type()) {
  m_object = api()->msgbox_create(
    options.is_initial_modal() ? nullptr : parent.object(), options.initial_title(), options.initial_message(), options.m_button_list,
    options.is_initial_add_close_button());
}
