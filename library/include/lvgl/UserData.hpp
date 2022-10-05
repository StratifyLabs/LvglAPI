//
// Created by Tyler Gilbert on 2/26/22.
//

#ifndef LVGL_API_LVGL_USER_DATA_HPP
#define LVGL_API_LVGL_USER_DATA_HPP

#include "Types.hpp"

namespace lvgl {

class UserData {
  static constexpr u16 magic_identifier_value = '~' << 8 | '.';

protected:
  // this MUST be the first non-static data member
  u16 m_magic_identifier = magic_identifier_value;

  // limit the access to new to derived items only
  void *operator new(size_t size) { return ::operator new(size); }
  using Deleter = void (*)(UserData *);
  Deleter m_deleter = nullptr;

  explicit UserData(const char *name);

  friend class Object;
  friend class PeriodicTimer;
  const char *m_name = nullptr;
  lv_obj_t *m_associated_object = nullptr;

  // This returns a pointer to the user data object if it is
  // a user data object. If it is a plain name (`const char*`)
  // it returns nullptr
  static void *get_user_data(void *user_data);

  static void do_manual_cleanup(void *user_data);

  template <typename Derived> static Derived *get_user_data_derived(void *user_data) {
    return static_cast<Derived *>(get_user_data(user_data));
  }

public:
  static bool is_valid(const char *name);
};

template <class Derived> class UserDataAccess : private UserData {
public:
  explicit UserDataAccess(const char *name = "") : UserData(name) {
    // we need to guarantee this is organized in memory like
    // a plain old data to ensure m_magic_identifier
    // is in the expected location
    API_ASSERT(
      reinterpret_cast<std::uintptr_t>(this)
      == reinterpret_cast<std::uintptr_t>(&m_magic_identifier));
  }

  API_NO_DISCARD bool needs_free() const { return m_deleter; }
  API_NO_DISCARD const char *name() const { return m_name ? m_name : "unnamed"; }
  API_NO_DISCARD const char *cast_as_name() const {
    return reinterpret_cast<const char *>(this);
  }
  API_NO_DISCARD lv_obj_t *associated_object() const { return m_associated_object; }

  template <typename... Args> static Derived &create(Args... args) {
    auto *result = new Derived(args...);
    result->m_deleter = derived_deleter;
    return *result;
  }

  static const char *create_from_name(const char *name) {
    if (!is_valid(name)) {
      auto *result = new Derived(name);
      result->m_deleter = derived_deleter;
      return result->cast_as_name();
    }
    return name;
  }
  
protected:
  using UserDataBase = UserDataAccess<Derived>;
  static void derived_deleter(UserData *user_data) {
    static_assert(
      std::is_base_of<UserData, Derived>::value,
      "Use `struct Derived : public UserDataAccess<Derived>`");
    auto *derived = static_cast<Derived *>(user_data);
    if (derived && derived->needs_free()) {
      delete (static_cast<Derived *>(derived));
    }
  }

private:
  UserDataAccess(const UserDataAccess &) = default;
  UserDataAccess &operator=(const UserDataAccess &) = default;
};

} // namespace lvgl

#endif // LVGL_API_LVGL_USER_DATA_HPP
