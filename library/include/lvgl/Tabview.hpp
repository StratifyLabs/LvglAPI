#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP

#include "ButtonMatrix.hpp"
#include "Object.hpp"

namespace lv {

class TabView : public ObjectAccess<TabView> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name_value) : CreateAccess(name_value) {}

  private:
    API_AF(Create, Direction, direction, Direction::top);
    API_AF(Create, u32, size, 10_percent);
  };

  TabView(Object parent, const Create &options);

  TabView &add_tab(
    const char *name,
    void *context = nullptr,
    void (*add)(Container &container, void *context) = nullptr) {
    Container obj(api()->tabview_add_tab(m_object, name));
    if (add) {
      add(obj, context);
    }
    return *this;
  }

  TabView &add_content(
    size_t tab,
    void *context,
    void (*add)(Container &container, void *context)) {
    API_ASSERT(add != nullptr);
    Container container(get_tab(tab).object());
    add(container, context);

    return *this;
  }

  Container get_content() const {
    return Container(api()->tabview_get_content(m_object));
  }

  ButtonMatrix get_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

  Container get_tab(size_t i) {
    API_ASSERT(get_content().object());
    API_ASSERT(i < get_content().get_child_count());
    return Container(get_content().get_child(i).object());
  }

private:
};

} // namespace lv

#endif // LVGLAPI_LVGL_TABVIEW_HPP
