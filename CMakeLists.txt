cmake_minimum_required (VERSION 3.12)

project(LvglAPI CXX)
include(CTest)

option(LVGL_API_IS_QT_SIMULATOR "Enable the Qt simulator" OFF)

add_subdirectory(lvgl lvgl)
add_subdirectory(library library)
if(SOS_IS_LINK AND LVGL_API_IS_QT_SIMULATOR)
	add_subdirectory(simulator simulator)
endif()
if(SOS_IS_TEST)
	add_subdirectory(tests tests)
endif()

