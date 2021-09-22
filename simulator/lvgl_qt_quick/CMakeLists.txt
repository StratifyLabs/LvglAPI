cmake_minimum_required(VERSION 3.10)

add_library(lvgl_qt_quick
	qml.qrc
)

set_property(TARGET lvgl_qt_quick PROPERTY CXX_STANDARD 17)

target_include_directories(lvgl_qt_quick
  PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(lvgl_qt_quick
	PUBLIC
	lvgl_qt
)

target_compile_definitions(lvgl_qt_quick
  PRIVATE
	$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
