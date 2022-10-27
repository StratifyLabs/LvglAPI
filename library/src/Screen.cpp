#include "lvgl/Screen.hpp"
#include "lvgl/macros.hpp"

using namespace lvgl;

namespace {
using ScreenList = var::Vector<lv_obj_t *>;
auto local_screen_list = ScreenList();
}

Screen::Screen(const char *name) {
  if (local_screen_list.count() == 0) {
    // add the default screen
    auto active_screen = api()->disp_get_scr_act(nullptr);
    local_screen_list.push_back(active_screen);
    set_user_data(active_screen, default_name);
  }

  m_object = api()->obj_create(nullptr);
  set_user_data(m_object, name);
  for (auto &entry : local_screen_list) {
    if (entry == nullptr) {
      entry = m_object;
      return;
    }
  }
  local_screen_list.push_back(m_object);
}

void Screen::remove_screen(const char *name) {
  for (auto &entry : local_screen_list) {
    if (entry != nullptr) {
      auto s = Screen(entry);
      const var::StringView s_name = s.name();
      if (s_name == name && s_name != default_name) {
        s.async_remove();
        entry = nullptr;
        return;
      }
    }
  }
}

Screen Screen::find_screen(const char *name) {
  for (auto &entry : local_screen_list) {
    if (entry != nullptr) {
      auto s = Screen(entry);
      if (var::StringView(s.name()) == name) {
        return s;
      }
    }
  }
  return Screen{static_cast<lv_obj_t *>(nullptr)};
}

var::Vector<lv_obj_t *> &Screen::screen_list() { return local_screen_list; }
