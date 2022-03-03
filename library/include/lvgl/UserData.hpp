//
// Created by Tyler Gilbert on 2/26/22.
//

#ifndef LVGL_API_LVGL_USER_DATA_HPP
#define LVGL_API_LVGL_USER_DATA_HPP

#include "Types.hpp"

namespace lvgl {

class UserData {
  void *operator new(size_t size) { return ::operator new(size); }

public:
  explicit UserData(const char *name = "");
  virtual ~UserData() = default;

  API_NO_DISCARD const char *name() const;

  template <typename Type> Type *cast() const {
    return reinterpret_cast<Type *>(const_cast<UserData *>(this));
  }

  API_NO_DISCARD const char *cast_as_name() const;
  API_NO_DISCARD void *cast_as_void() const;
  API_NO_DISCARD bool needs_free() const { return m_needs_free; }
  API_NO_DISCARD lv_obj_t *associated_object() const { return m_associated_object; }

protected:
  // dynamically allocate the UserData and have it live with the created object
  // this will be freed when the associated object is removed
  template <class Derived, typename... Args> static Derived &create(Args... args) {
    auto *result = new Derived(args...);
    result->m_needs_free = true;
    return *result;
  }

private:
  friend class Object;

  // This returns a pointer to the user data object if it is
  // a user data object. If it is a plain name (`const char*`)
  // it returns null
  static UserData *get_user_data(void *user_data);

  // the magic function is used to determine if the user data points
  // to a UserData compatible object or to a `const char *`
  // and is just a plain old name
  static void magic_function();
  const void *m_magic = reinterpret_cast<void *>(magic_function);
  const char *m_name = nullptr;
  lv_obj_t *m_associated_object = nullptr;
  bool m_needs_free = false;
};

template <class Derived> class UserDataAccess : public UserData {
public:
  explicit UserDataAccess(const char *name = "") : UserData(name) {}
  virtual ~UserDataAccess() = default;

  template <typename... Args> static Derived &create(Args... args) {
    return UserData::create<Derived>(args...);
  }

protected:
  using UserDataBase = UserDataAccess<Derived>;
};

}


#endif // LVGL_API_LVGL_USER_DATA_HPP
