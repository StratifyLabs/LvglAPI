#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP

#include "ButtonMatrix.hpp"
#include "Container.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class TabView : public ObjectAccess<TabView> {
public:
  struct Construct {
    API_PUBLIC_MEMBER(Construct, const char *, name, "");
    API_PUBLIC_MEMBER(Construct, Direction, direction, Direction::top);
    API_PUBLIC_MEMBER(Construct, u32, size, 10_percent);
  };

  explicit TabView(const Construct &options);

  static const lv_obj_class_t *get_class() { return api()->tabview_class; }

  TabView &add_tab(
    const char *name,
    const char *title,
    void (*add)(Container &container) = nullptr) {
    Container obj(api()->tabview_add_tab(m_object, title));
    set_user_data(obj.object(), name);
    if (add) {
      add(obj);
    }
    return *this;
  }

  TabView &add_tab(const char *name, void (*add)(Container &container) = nullptr) {
    Container obj(api()->tabview_add_tab(m_object, name));
    set_user_data(obj.object(), name);
    if (add) {
      add(obj);
    }
    return *this;
  }

  TabView &add_tab(
    const UserData &context,
    const char *title,
    void (*add)(Container &container) = nullptr) {
    return add_tab(context.cast_as_name(), title, add);
  }

  TabView &add_tab(const UserData &context, void (*add)(Container &container) = nullptr) {
    return add_tab(context.cast_as_name(), add);
  }

  TabView &add_content(size_t tab, void (*add)(Container &container)) {
    API_ASSERT(add != nullptr);
    Container container(get_tab(tab).object());
    if (add) {
      add(container);
    }
    return *this;
  }

  Container get_content() const {
    return Container(api()->tabview_get_content(m_object));
  }

  ButtonMatrix get_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

  size_t get_active_tab_offset() const { return api()->tabview_get_tab_act(m_object); }

  Container get_tab(size_t i) const {
    API_ASSERT(get_content().object());
    API_ASSERT(i < get_content().get_child_count());
    return Container(get_content().get_child(i).object());
  }

  Container get_active_tab() const { return get_tab(get_active_tab_offset()); }

private:
  OBJECT_ACCESS_FRIENDS();


  explicit TabView(lv_obj_t *object) { m_object = object; }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_TABVIEW_HPP
