#include "lvgl/Window.hpp"

using namespace lvgl;

Window::Window(Object parent, const Window &options){
  m_object = api()->win_create(parent.object(), options.initial_height());
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);
}
