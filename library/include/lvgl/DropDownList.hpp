#ifndef LVGLAPI_LVGL_DROPDOWNLIST_HPP
#define LVGLAPI_LVGL_DROPDOWNLIST_HPP

#include "ObjectAccess.hpp"

#include "List.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class DropDownList : public ObjectAccess<DropDownList>
{
public:
  explicit DropDownList(const char * name);

  static const lv_obj_class_t * get_class(){
    return api()->dropdown_class;
  }

  DropDownList& add_option(const char * option, u32 pos = LV_DROPDOWN_POS_LAST){
    api()->dropdown_add_option(m_object, option, pos);
    return *this;
  }

  static constexpr auto options_separator = '\n';

  DropDownList& set_options(const char * options){
    api()->dropdown_set_options(m_object, options);
    return *this;
  }

  DropDownList& set_options_static(const char * options){
    api()->dropdown_set_options_static(m_object, options);
    return *this;
  }

  DropDownList& set_text(const char * text){
    api()->dropdown_set_text(m_object, text);
    return *this;
  }

  DropDownList& clear_options(){
    api()->dropdown_clear_options(m_object);
    return *this;
  }

  DropDownList& set_selected(u16 position){
    api()->dropdown_set_selected(m_object, position);
    return *this;
  }

  DropDownList& set_direction(Direction direction){
    api()->dropdown_set_dir(m_object, lv_dir_t(direction));
    return *this;
  }

  DropDownList& set_symbol(const void * symbol){
    api()->dropdown_set_symbol(m_object, symbol);
    return *this;
  }

  DropDownList& set_highlight_selected(bool value = true){
    api()->dropdown_set_selected_highlight(m_object, value);
    return *this;
  }

  List get_list() const {
    return List(api()->dropdown_get_list(m_object));
  }

  const char * get_text() const {
    return api()->dropdown_get_text(m_object);
  }

  const char * get_options() const {
    return api()->dropdown_get_options(m_object);
  }

  u16 get_selected() const {
    return api()->dropdown_get_selected(m_object);
  }

  u16 get_option_count() const {
    return api()->dropdown_get_option_cnt(m_object);
  }

  template<class StringType> StringType get_selected_string() const {
    StringType result;
    api()->dropdown_get_selected_str(m_object, result.data(), result.capacity());
    return result;
  }

  bool get_highlight_selected() const {
    return api()->dropdown_get_selected_highlight(m_object);
  }

  Direction get_direction() const {
    return Direction(api()->dropdown_get_dir(m_object));
  }

  DropDownList& open(){
    api()->dropdown_open(m_object);
    return *this;
  }

  DropDownList& close(){
    api()->dropdown_close(m_object);
    return *this;
  }


private:
  OBJECT_ACCESS_FRIENDS();
  explicit DropDownList(lv_obj_t * object){ m_object = object; }
};

using DropDown = DropDownList;

}

#endif // LVGLAPI_LVGL_DROPDOWNLIST_HPP
