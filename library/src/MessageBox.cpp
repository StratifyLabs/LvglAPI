#include "lvgl/MessageBox.hpp"
#include "lvgl/Generic.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(MessageBox);

MessageBox::MessageBox(const Construct & options) {
  m_object = api()->msgbox_create(
    options.is_modal ? nullptr : screen_object(),
    options.title, options.message,
    options.button_list, options.is_add_close_button);
  set_user_data(m_object,options.name);
}
