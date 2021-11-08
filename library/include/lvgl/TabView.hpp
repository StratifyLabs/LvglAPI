#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP

#include "ButtonMatrix.hpp"
#include "Container.hpp"

namespace lvgl {


class TabView : public ObjectAccess<TabView> {
public:
  struct Construct {
    //name first
    API_PUBLIC_MEMBER(Construct, const char *, name, "");
    //alphabetical
    API_PUBLIC_MEMBER(Construct, Direction, direction, Direction::top);
    API_PUBLIC_MEMBER(Construct, u32, size, 10_percent);
  };

  explicit TabView(const Construct &options);
  explicit TabView(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->tabview_class; }

  TabView &add_tab(
    const char *name,
    const char *title,
    void (*setup)(Container) = nullptr) {
    Container obj(api()->tabview_add_tab(m_object, title));
    set_user_data(obj.object(), name);
    if (setup) {
      setup(obj);
    }
    return *this;
  }

  TabView &add_tab(const char *title, void (*setup)(Container) = nullptr) {
    Container obj(api()->tabview_add_tab(m_object, title));
    set_user_data(obj.object(), title);
    if (setup) {
      setup(obj);
    }
    return *this;
  }

  TabView &add_content(size_t tab, void (*setup)(Container)) {
    API_ASSERT(setup != nullptr);
    Container container(get_tab(tab).object());
    if (setup) {
      setup(container);
    }
    return *this;
  }

  API_NO_DISCARD Container get_content() const {
    return Container(api()->tabview_get_content(m_object));
  }

  API_NO_DISCARD ButtonMatrix get_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

  API_NO_DISCARD size_t get_active_tab_offset() const { return api()->tabview_get_tab_act(m_object); }

  API_NO_DISCARD Container get_tab(size_t i) const {
    API_ASSERT(get_content().object());
    API_ASSERT(i < get_content().get_child_count());
    return Container(get_content().get_child(i).object());
  }

  API_NO_DISCARD Container get_active_tab() const { return get_tab(get_active_tab_offset()); }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_TABVIEW_HPP
