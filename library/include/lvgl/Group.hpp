#ifndef LVGLAPI_GROUP_HPP
#define LVGLAPI_GROUP_HPP

#include "Object.hpp"

namespace lvgl {

class Group : public Api {
public:

  enum class RefocusPolicy {
    next = LV_GROUP_REFOCUS_POLICY_NEXT,
    previous = LV_GROUP_REFOCUS_POLICY_PREV
  };

  static Group create();

  Group & set_default(){
    api()->group_set_default(m_group);
    return *this;
  }

  static Group get_default(){
    Group result;
    result.m_group = api()->group_get_default();
    return result;
  }

  Group& add(Object object){
    api()->group_add_obj(m_group, object.object());
    return *this;
  }

  static void remove(Object object){
    api()->group_remove_obj(object.object());
  }

  Group& remove_all(){
    api()->group_remove_all_objs(m_group);
    return *this;
  }

  static void focus(Object object){
    api()->group_focus_obj(object.object());
  }

  Group & focus_next(){
    api()->group_focus_next(m_group);
    return *this;
  }

  Group & focus_previous(){
    api()->group_focus_prev(m_group);
    return *this;
  }

  Group & focus_freeze(bool value = true){
    api()->group_focus_freeze(m_group, value);
    return *this;
  }

  Group & set_refocus_policy(RefocusPolicy value){
    api()->group_set_refocus_policy(m_group, lv_group_refocus_policy_t(value));
    return *this;
  }

  Group & set_editing(bool value = true){
    api()->group_set_editing(m_group, value);
    return *this;
  }

  API_NO_DISCARD bool is_editing() const {
    return api()->group_get_editing(m_group);
  }

  Group & set_wrap(bool value = true){
    api()->group_set_wrap(m_group, value);
    return *this;
  }

  API_NO_DISCARD bool is_wrap() const {
    return api()->group_get_wrap(m_group);
  }

  API_NO_DISCARD u32 get_object_count() const {
    return api()->group_get_obj_count(m_group);
  }

  API_NO_DISCARD Object get_focused() const {
    return Object(api()->group_get_focused(m_group));
  }

  API_NO_DISCARD lv_group_t * group(){
    return m_group;
  }

private:
  lv_group_t *m_group = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_GROUP_HPP
