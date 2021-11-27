cmake_minimum_required(VERSION 3.12)

set(SOURCES_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lodepng)

set(GIT_REPOSITORY "https://github.com/lvandeve/lodepng.git")
set(GIT_BRANCH "master")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lodepng)
  message(STATUS "Need to clone for the first call to cmake")
  execute_process(
    COMMAND git clone --branch ${GIT_BRANCH} ${GIT_REPOSITORY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

  file(RENAME ${SOURCES_PREFIX}/lodepng.cpp ${SOURCES_PREFIX}/lodepng.c)
endif()

if(NOT LODEPNG_DEFINITIONS)
  message(FATAL_ERROR "LODEPNG_DEFINITIONS must be defined")
endif()

project(lodepng C)

set(PRIVATE_SOURCELIST
  ${SOURCES_PREFIX}/lodepng.c
  ${SOURCES_PREFIX}/lodepng.h
  )


if(SOS_IS_ARM)
  set(LIB_OPTION kernel)
endif()

sos_sdk_library_target(RELEASE ${PROJECT_NAME} "${LIB_OPTION}" release ${SOS_ARCH})

add_library(${RELEASE_TARGET} STATIC)

target_sources(${RELEASE_TARGET}
  PUBLIC
  PRIVATE
  ${PRIVATE_SOURCELIST}
  )

target_compile_definitions(${RELEASE_TARGET}
  PUBLIC
  ${LODEPNG_DEFINITIONS}
  PRIVATE
  )

target_compile_options(${RELEASE_TARGET}
  PUBLIC
  -Os
  )

target_include_directories(${RELEASE_TARGET}
  PUBLIC
  $<INSTALL_INTERFACE:include/lodepng>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lodepng>
  PRIVATE
  )

sos_sdk_library_target(DEBUG ${PROJECT_NAME} "${LIB_OPTION}" debug ${SOS_ARCH})
add_library(${DEBUG_TARGET} STATIC)
sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})

if(SOS_IS_LINK)
  set(DEPENDENCIES "")
  sos_sdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${SOS_ARCH} "${DEPENDENCIES}")

  sos_sdk_library_target(COVERAGE ${PROJECT_NAME} "${LIB_OPTION}" coverage ${SOS_ARCH})
  add_library(${COVERAGE_TARGET} STATIC)
  sos_sdk_copy_target(${RELEASE_TARGET} ${COVERAGE_TARGET})
  sos_sdk_library_add_arch_targets("${COVERAGE_OPTIONS}" ${SOS_ARCH} "")
  sos_sdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${SOS_ARCH} "${DEPENDENCIES}")
else()
  sos_sdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${SOS_ARCH} "StratifyOS_mcu")
  sos_sdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${SOS_ARCH} "StratifyOS_mcu")
endif()

install(FILES
  ${SOURCES_PREFIX}/lodepng.h
  ${SOURCES_PREFIX}/lodepng_util.h
  DESTINATION include/lodepng
  )



