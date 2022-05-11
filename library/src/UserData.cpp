//
// Created by Tyler Gilbert on 2/26/22.
//

#include "lvgl/UserData.hpp"

using namespace lvgl;

UserData::UserData(const char *name) : m_name(name) {}

void *UserData::get_user_data(void *user_data) {
  auto name = reinterpret_cast<const char *>(user_data);
  if (!name || name[0] == 0) {
    return nullptr;
  }

  //If name is not empty, we can read at least 2 bytes
  //without triggering the address sanitizer
  auto identifier = reinterpret_cast<const u16 *>(user_data);
  if (*identifier == magic_identifier_value) {
    return user_data;
  }
  return nullptr;
}

void UserData::do_manual_cleanup(void *user_data) {
  UserData * user_data_object = reinterpret_cast<UserData*>(get_user_data(user_data));
  if( user_data_object && user_data_object->m_deleter ){
    user_data_object->m_deleter(user_data_object);
  }
}

bool UserData::is_valid(const char * name) {
  if (!name || name[0] == 0) {
    return false;
  }

  auto identifier = reinterpret_cast<const u16 *>(name);
  if (*identifier == magic_identifier_value) {
    return true;
  }
  return false;
}
