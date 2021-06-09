cmake_minimum_required(VERSION 3.10)

add_library(lvgl_qt
  LvglRenderer.cpp
  LvglRenderer.hpp
)

set_property(TARGET lvgl_qt PROPERTY CXX_STANDARD 17)

target_compile_definitions(lvgl_qt
	PUBLIC
	__link
	)

target_include_directories(lvgl_qt
  PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(lvgl_qt
  PUBLIC
	LvglAPI_release_link
	Qt${QT_VERSION_MAJOR}::Gui
)
