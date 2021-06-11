#ifndef LVGLAPI_LVGL_TABVIEW_HPP
#define LVGLAPI_LVGL_TABVIEW_HPP


#include "Object.hpp"
#include "ButtonMatrix.hpp"

namespace lv {

class TabView : public ObjectAccess<TabView> {
public:

  TabView(const char * name, Direction direction, u32 size);

  TabView& add_tab(const char *name, Object content = Object()){
    Object obj(api()->tabview_add_tab(m_object, name));
    obj.set_name(name);
    if( content.object() ){
      Container(obj.object()).add(content);
    }
    return *this;
  }

  TabView& add_content(size_t tab, Object object){
    get_tab(tab).add(object);
    return *this;
  }

  Container get_content() const {
    return Container(api()->tabview_get_content(m_object));
  }

  ButtonMatrix get_tab_buttons() const {
    return ButtonMatrix(api()->tabview_get_tab_btns(m_object));
  }

  Container get_tab(size_t i){
    API_ASSERT(get_content().object());
    API_ASSERT(i < get_content().get_child_count());
    return Container(get_content().get_child(i).object());
  }

private:

};

}

#endif // LVGLAPI_LVGL_TABVIEW_HPP
