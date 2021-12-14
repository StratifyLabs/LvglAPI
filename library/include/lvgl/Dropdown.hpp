#ifndef LVGLAPI_LVGL_DROPDOWNLIST_HPP
#define LVGLAPI_LVGL_DROPDOWNLIST_HPP

#include "ObjectAccess.hpp"

#include "List.hpp"

namespace lvgl {


class Dropdown : public ObjectAccess<Dropdown>
{
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Dropdown);

  static const lv_obj_class_t * get_class(){
    return api()->dropdown_class;
  }

  Dropdown & add_option(const char * option, u32 pos = LV_DROPDOWN_POS_LAST){
    api()->dropdown_add_option(m_object, option, pos);
    return *this;
  }

  static constexpr auto options_separator = '\n';

  Dropdown & set_options(const char * options){
    api()->dropdown_set_options(m_object, options);
    return *this;
  }

  Dropdown & set_options_as_static(const char * options){
    api()->dropdown_set_options_static(m_object, options);
    return *this;
  }

  Dropdown & set_text(const char * text){
    api()->dropdown_set_text(m_object, text);
    return *this;
  }

  Dropdown & clear_options(){
    api()->dropdown_clear_options(m_object);
    return *this;
  }

  Dropdown & set_selected(u16 position){
    api()->dropdown_set_selected(m_object, position);
    return *this;
  }

  Dropdown & set_direction(Direction direction){
    api()->dropdown_set_dir(m_object, lv_dir_t(direction));
    return *this;
  }

  Dropdown & set_symbol(const void * symbol){
    api()->dropdown_set_symbol(m_object, symbol);
    return *this;
  }

  Dropdown & set_highlight_selected(bool value = true){
    api()->dropdown_set_selected_highlight(m_object, value);
    return *this;
  }

  API_NO_DISCARD List get_list() const {
    return List(api()->dropdown_get_list(m_object));
  }

  API_NO_DISCARD const char * get_text() const {
    return api()->dropdown_get_text(m_object);
  }

  API_NO_DISCARD const char * get_options() const {
    return api()->dropdown_get_options(m_object);
  }

  API_NO_DISCARD u16 get_selected() const {
    return api()->dropdown_get_selected(m_object);
  }

  API_NO_DISCARD u16 get_option_count() const {
    return api()->dropdown_get_option_cnt(m_object);
  }

  template<class StringType> API_NO_DISCARD StringType get_selected_string() const {
    StringType result;
    api()->dropdown_get_selected_str(m_object, result.data(), result.capacity());
    return result;
  }

  API_NO_DISCARD bool get_highlight_selected() const {
    return api()->dropdown_get_selected_highlight(m_object);
  }

  API_NO_DISCARD Direction get_direction() const {
    return Direction(api()->dropdown_get_dir(m_object));
  }

  Dropdown & open(){
    api()->dropdown_open(m_object);
    return *this;
  }

  Dropdown & close(){
    api()->dropdown_close(m_object);
    return *this;
  }

};

using DropDown = Dropdown;

}

#endif // LVGLAPI_LVGL_DROPDOWNLIST_HPP
