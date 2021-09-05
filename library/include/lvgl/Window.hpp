#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Container.hpp"
#include "Label.hpp"
#include "Button.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Window : public ObjectAccess<Window> {
public:

  explicit Window(const char * name) : ObjectAccess(name){}

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

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Window(lv_obj_t * object){ m_object = object; }
  Window(Object parent, const Window &options);

  API_AF(Window, lv_coord_t, initial_height, 15_percent);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_WINDOW_HPP
