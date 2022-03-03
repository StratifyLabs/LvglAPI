//
// Created by Tyler Gilbert on 2/26/22.
//

#include "lvgl/UserData.hpp"

using namespace lvgl;

UserData::UserData(const char *name) : m_name(name) {}

const char *UserData::name() const { return m_name ? m_name : "unnamed"; }

const char *UserData::cast_as_name() const {
  return reinterpret_cast<const char *>(this);
}

void UserData::magic_function() {}

UserData *UserData::get_user_data(void *user_data) {
  auto *context = reinterpret_cast<UserData *>(user_data);
  return context->m_magic == reinterpret_cast<void *>(magic_function) ? context : nullptr;
}

void *UserData::cast_as_void() const {
  return reinterpret_cast<void *>(const_cast<UserData *>(this));
}

