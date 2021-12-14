// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef LVGLAPI_LVGL_MACROS_HPP
#define LVGLAPI_LVGL_MACROS_HPP

#define LVGL_PROPERTY_CASE(x, y)                                                         \
  case x::y:                                                                             \
    return MCU_STRINGIFY(y)

#define LVGL_PROPERTY_STRING_CASE(x, y)                                                  \
  if (value_stringview == MCU_STRINGIFY(y)) {                                            \
    return x::y;                                                                         \
  }

#endif // LVGLAPI_LVGL_MACROS_HPP
