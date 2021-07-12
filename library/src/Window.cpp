#include "lvgl/Window.hpp"

using namespace lvgl;

Window::Window(Object parent, const Create &options) : ObjectAccess(object_type()) {
  m_object = api()->win_create(parent.object(), options.height());
  set_name(options.name());
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);
}
