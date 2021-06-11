#include "lvgl/Window.hpp"

using namespace lv;

Window::Window(Object parent, const Create& options)
{
  m_object = api()->win_create(parent.object(), options.height());
  set_name(options.name());
}
