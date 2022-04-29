// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef LVGLAPI_LVGL_MACROS_HPP
#define LVGLAPI_LVGL_MACROS_HPP

#define LVGL_PROPERTY_CASE(x, y)                                                         \
  case x::y:                                                                             \
    return MCU_STRINGIFY(y)

#define LVGL_PROPERTY_STRING_CASE(x, y)                                                  \
  if (value == MCU_STRINGIFY(y)) {                                                       \
    return x::y;                                                                         \
  }

#define LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(CLASS_NAME)                             \
  explicit CLASS_NAME(lv_obj_t *object) { m_object = object; }

#define LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(CLASS_NAME)                               \
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(CLASS_NAME)                                   \
  explicit CLASS_NAME(const char *name = "")

#define LVGL_OBJECT_ACCESS_GET_CLASS(CLASS_NAME)                                         \
  static const lv_obj_class_t *get_class() { return api()->CLASS_NAME; }

#define LVGL_OBJECT_ASSERT_SIZE(CLASS_NAME)                                              \
  static_assert(                                                                         \
    sizeof(CLASS_NAME) == sizeof(lvgl::ObjectAccessSizeCheck),                           \
    "Objects derived from ObjectAccess<> cannot have non-static data members")
#endif // LVGLAPI_LVGL_MACROS_HPP
