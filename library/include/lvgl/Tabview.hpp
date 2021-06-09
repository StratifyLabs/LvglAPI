#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP


#include "Object.hpp"
#include "ButtonMatrix.hpp"

namespace lv {

class TabView : public ObjectAccess<TabView> {
public:

  TabView(const char * name, Direction direction, u32 size);

  TabView& add_tab(const char *name, Object content = Object()){
    auto * obj = api()->tabview_add_tab(m_object, name);
    if( content.object() ){
      Object(obj).add(content);
    }
    printf("added tab %p\n", obj);
    return *this;
  }

  TabView& add_content(size_t tab, Object object){
    get_tab(tab).add(object);
    return *this;
  }

  Object get_content() const {
    return Object(api()->tabview_get_content(m_object));
  }

  ButtonMatrix get_tab_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

  Object get_tab(size_t i){
    API_ASSERT(get_content().object());
    API_ASSERT(i < get_content().get_child_count());
    return Object(get_content().get_child(i));
  }

private:

};

}

#endif // LVGLAPI_LVGL_TABVIEW_HPP
