#ifndef LVGLAPI_LVGL_TREE_HPP
#define LVGLAPI_LVGL_TREE_HPP

#include "Object.hpp"

namespace lvgl {

class Tree : public Api {
public:
  Tree();
  Tree(Object object) : m_object(object.object()){}

  template <IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  Object find_object(const char *name) const {
    // recursively find the child
    auto get = find_child(name);
    if (get.object() != nullptr) {
      return get;
    }
    const auto count = self().get_child_count();
    for (u32 i = 0; i < count; i++) {
      const auto child = self().get_child(i);
      auto result = Tree(child).find_object<IsAssertOnFail::no>(name);
      if (result.m_object != nullptr) {
        return result;
      }
    }
    if (isAssertOnFail == IsAssertOnFail::yes) {
      API_ASSERT(false);
    }
    return Object();
  }

  template <class TargetClass = Object, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  TargetClass find(const char *name) const {
    auto object = find_object<isAssertOnFail>(name);
    return TargetClass(object.object());
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  TargetClass find_within(const char * top, const char * bottom) const {
    auto outer = find_object(top);
    return Tree(outer).find<TargetClass, isAssertOnFail>(bottom);
  }

  template <class TargetClass, IsAssertOnFail isAssertOnFail = IsAssertOnFail::yes>
  TargetClass find(const std::initializer_list<const char*> list) const {
    auto current = self();
    for(const char * entry: list){
      current = Tree(current).find_object<isAssertOnFail>(entry);
    }
    return TargetClass(current.object());
  }

  template <class TargetClass> TargetClass find_parent() {
    auto current = self().get_parent();
    while (1) {
      if (current.object() == nullptr) {
        API_ASSERT(false);
      } else {
        if (current.get_instance_class().class_() == TargetClass::get_class()) {
          return current.get<TargetClass>();
        }
      }
      current = current.get_parent();
    }
  }

  Object find_child(const char *name) const {
    const auto count = self().get_child_count();
    for (u32 i = 0; i < count; i++) {
      auto child = self().get_child(i);
      if (is_name_matched(child, name)) {
        return child;
      }
    }
    return Object();
  }

private:
  lv_obj_t *m_object;

  static bool is_name_matched(const Object &child, const char *name) {
    const auto child_name = child.name();
    if (
      (child_name != nullptr)
      && ((child_name == name) || (var::StringView(child.name()) == name))) {
      return true;
    }
    return false;
  }

  Object self() const {
    return Object(m_object);
  }


};

} // namespace lvgl

#endif // LVGLAPI_LVGL_TREE_HPP
