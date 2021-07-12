#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Container.hpp"
#include "Label.hpp"
#include "Button.hpp"

namespace lvgl {

class Window : public ObjectAccess<Window> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}

  private:
    API_AF(Create, lv_coord_t, height, 15_percent);
  };
  Window(Object parent, const Create &options);

  Window &add_button(const char *name, const void *icon, lv_coord_t width, void (*add)(Button &) = nullptr) {
    auto object = api()->win_add_btn(m_object, icon, width);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void *)name;
    if( add ){
      Button button(object);
      add(button);
    }
    return *this;
  }

  Window &add_title(const char *name, const char * text, void (*add)(Label &) = nullptr) {
    auto object = api()->win_add_title(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void *)name;
    if( add ){
      Label label(object);
      add(label);
    }
    return *this;
  }

  Container get_header() const { return Container(api()->win_get_header(m_object)); }

  Container get_content() const { return Container(api()->win_get_content(m_object)); }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_WINDOW_HPP
