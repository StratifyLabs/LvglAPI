#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP


#include "Object.hpp"
#include "ButtonMatrix.hpp"

namespace lv {

class TabView : public ObjectAccess<TabView> {
public:

  TabView(Object & parent, Direction direction, u32 size);

  TabView& add_tab(const char *name){
    auto * obj = api()->tabview_add_tab(m_object, name);
    printf("added tab %p\n", obj);
    return *this;
  }

  Object get_content() const {
    return Object(api()->tabview_get_content(m_object));
  }

  ButtonMatrix get_tab_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

private:

};

}

#endif // LVGLAPI_LVGL_TABVIEW_HPP
