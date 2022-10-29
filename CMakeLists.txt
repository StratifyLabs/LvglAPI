cmake_minimum_required (VERSION 3.12)
cmsdk2_minimum_required(2.1.2)

project(LvglAPI
	LANGUAGES CXX
	VERSION 1.0.1)
include(CTest)

option(LVGL_API_USE_FREETYPE "Use Freetype font loader" OFF)
add_subdirectory(lvgl)
add_subdirectory(library)

if(LVGL_API_USE_FREETYPE)
	include(FindFreeType)
	if(NOT ${FREETYPE_FOUND})
		message(FATAL_ERROR "LVGL_API_USE_FREETYPE is ON but freetype is not found in the system")
	else()
		message(STATUS "Freetype include directories ${FREETYPE_INCLUDE_DIRS}")
		message(STATUS "Freetype libraries directories ${FREETYPE_LIBRARIES}")
		message(STATUS "Freetype version directories ${FREETYPE_VERSION_STRING}")
	endif()
	cmsdk2_git_clone_or_pull_branch(
		NAME lv_lib_freetype
		REPOSITORY https://github.com/lvgl/lv_lib_freetype
		BRANCH master
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
endif()

option(LVGL_API_IS_TEST "Enable test builds for LvglAPI" OFF)
if(LVGL_API_IS_TEST)
	add_subdirectory(tests tests)
endif()

