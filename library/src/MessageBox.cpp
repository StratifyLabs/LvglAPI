#include "lvgl/MessageBox.hpp"

using namespace lvgl;

MessageBox::MessageBox(Object parent, const MessageBox &options) {
  m_object = api()->msgbox_create(
    options.m_construct->is_modal() ? nullptr : parent.object(),
    options.m_construct->title(), options.m_construct->message(),
    options.m_construct->m_button_list, options.m_construct->is_add_close_button());
}
