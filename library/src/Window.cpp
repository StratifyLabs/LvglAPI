#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "lvgl/Window.hpp"


using namespace lvgl;

Window::Window(const char *name, lv_coord_t header_height) {
  m_object = api()->win_create(screen_object(), header_height);
  set_user_data(m_object, name);
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);
}
