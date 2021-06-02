cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

set(GIT_REPOSITORY "https://github.com/lvgl/lvgl.git")
set(GIT_BRANCH "release/v7")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
	message(STATUS "Need to clone for the first call to cmake")
	execute_process(
		COMMAND git clone --branch ${GIT_BRANCH} ${GIT_REPOSITORY}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()

project(lvgl C)

set(SOURCES_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src)


set(PRIVATE_SOURCELIST
	${SOURCES_PREFIX}/lv_api_map.h
	${SOURCES_PREFIX}/lv_core/lv_group.h
	${SOURCES_PREFIX}/lv_core/lv_indev.c
	${SOURCES_PREFIX}/lv_core/lv_disp.c
	${SOURCES_PREFIX}/lv_core/lv_obj.h
	${SOURCES_PREFIX}/lv_core/lv_refr.c
	${SOURCES_PREFIX}/lv_core/lv_style.c
	${SOURCES_PREFIX}/lv_core/lv_core.mk
	${SOURCES_PREFIX}/lv_core/lv_obj_style_dec.h
	${SOURCES_PREFIX}/lv_core/lv_disp.h
	${SOURCES_PREFIX}/lv_core/lv_obj.c
	${SOURCES_PREFIX}/lv_core/lv_indev.h
	${SOURCES_PREFIX}/lv_core/lv_group.c
	${SOURCES_PREFIX}/lv_core/lv_style.h
	${SOURCES_PREFIX}/lv_core/lv_refr.h
	${SOURCES_PREFIX}/lv_misc/lv_printf.h
	${SOURCES_PREFIX}/lv_misc/lv_utils.c
	${SOURCES_PREFIX}/lv_misc/lv_templ.h
	${SOURCES_PREFIX}/lv_misc/lv_async.h
	${SOURCES_PREFIX}/lv_misc/lv_txt.c
	${SOURCES_PREFIX}/lv_misc/lv_debug.c
	${SOURCES_PREFIX}/lv_misc/lv_task.c
	${SOURCES_PREFIX}/lv_misc/lv_math.h
	${SOURCES_PREFIX}/lv_misc/lv_anim.h
	${SOURCES_PREFIX}/lv_misc/lv_misc.mk
	${SOURCES_PREFIX}/lv_misc/lv_mem.c
	${SOURCES_PREFIX}/lv_misc/lv_fs.c
	${SOURCES_PREFIX}/lv_misc/lv_bidi.h
	${SOURCES_PREFIX}/lv_misc/lv_txt_ap.c
	${SOURCES_PREFIX}/lv_misc/lv_gc.h
	${SOURCES_PREFIX}/lv_misc/lv_color.c
	${SOURCES_PREFIX}/lv_misc/lv_ll.c
	${SOURCES_PREFIX}/lv_misc/lv_log.c
	${SOURCES_PREFIX}/lv_misc/lv_area.c
	${SOURCES_PREFIX}/lv_misc/lv_debug.h
	${SOURCES_PREFIX}/lv_misc/lv_task.h
	${SOURCES_PREFIX}/lv_misc/lv_async.c
	${SOURCES_PREFIX}/lv_misc/lv_txt.h
	${SOURCES_PREFIX}/lv_misc/lv_utils.h
	${SOURCES_PREFIX}/lv_misc/lv_templ.c
	${SOURCES_PREFIX}/lv_misc/lv_printf.c
	${SOURCES_PREFIX}/lv_misc/lv_types.h
	${SOURCES_PREFIX}/lv_misc/lv_mem.h
	${SOURCES_PREFIX}/lv_misc/lv_math.c
	${SOURCES_PREFIX}/lv_misc/lv_anim.c
	${SOURCES_PREFIX}/lv_misc/lv_txt_ap.h
	${SOURCES_PREFIX}/lv_misc/lv_gc.c
	${SOURCES_PREFIX}/lv_misc/lv_bidi.c
	${SOURCES_PREFIX}/lv_misc/lv_fs.h
	${SOURCES_PREFIX}/lv_misc/lv_area.h
	${SOURCES_PREFIX}/lv_misc/lv_log.h
	${SOURCES_PREFIX}/lv_misc/lv_ll.h
	${SOURCES_PREFIX}/lv_misc/lv_color.h
	${SOURCES_PREFIX}/lv_conf_kconfig.h
	${SOURCES_PREFIX}/lv_widgets/lv_linemeter.h
	${SOURCES_PREFIX}/lv_widgets/lv_slider.h
	${SOURCES_PREFIX}/lv_widgets/lv_img.h
	${SOURCES_PREFIX}/lv_widgets/lv_gauge.c
	${SOURCES_PREFIX}/lv_widgets/lv_imgbtn.h
	${SOURCES_PREFIX}/lv_widgets/lv_win.c
	${SOURCES_PREFIX}/lv_widgets/lv_cpicker.c
	${SOURCES_PREFIX}/lv_widgets/lv_list.h
	${SOURCES_PREFIX}/lv_widgets/lv_page.c
	${SOURCES_PREFIX}/lv_widgets/lv_keyboard.c
	${SOURCES_PREFIX}/lv_widgets/lv_widgets.mk
	${SOURCES_PREFIX}/lv_widgets/lv_label.c
	${SOURCES_PREFIX}/lv_widgets/lv_table.h
	${SOURCES_PREFIX}/lv_widgets/lv_roller.c
	${SOURCES_PREFIX}/lv_widgets/lv_arc.h
	${SOURCES_PREFIX}/lv_widgets/lv_bar.h
	${SOURCES_PREFIX}/lv_widgets/lv_dropdown.h
	${SOURCES_PREFIX}/lv_widgets/lv_btn.c
	${SOURCES_PREFIX}/lv_widgets/lv_canvas.h
	${SOURCES_PREFIX}/lv_widgets/lv_spinbox.c
	${SOURCES_PREFIX}/lv_widgets/lv_objx_templ.h
	${SOURCES_PREFIX}/lv_widgets/lv_calendar.h
	${SOURCES_PREFIX}/lv_widgets/lv_textarea.c
	${SOURCES_PREFIX}/lv_widgets/lv_switch.h
	${SOURCES_PREFIX}/lv_widgets/lv_chart.c
	${SOURCES_PREFIX}/lv_widgets/lv_msgbox.c
	${SOURCES_PREFIX}/lv_widgets/lv_tabview.h
	${SOURCES_PREFIX}/lv_widgets/lv_checkbox.h
	${SOURCES_PREFIX}/lv_widgets/lv_objmask.c
	${SOURCES_PREFIX}/lv_widgets/lv_line.h
	${SOURCES_PREFIX}/lv_widgets/lv_cont.c
	${SOURCES_PREFIX}/lv_widgets/lv_spinner.h
	${SOURCES_PREFIX}/lv_widgets/lv_btnmatrix.c
	${SOURCES_PREFIX}/lv_widgets/lv_tileview.c
	${SOURCES_PREFIX}/lv_widgets/lv_led.c
	${SOURCES_PREFIX}/lv_widgets/lv_label.h
	${SOURCES_PREFIX}/lv_widgets/lv_keyboard.h
	${SOURCES_PREFIX}/lv_widgets/lv_page.h
	${SOURCES_PREFIX}/lv_widgets/lv_list.c
	${SOURCES_PREFIX}/lv_widgets/lv_cpicker.h
	${SOURCES_PREFIX}/lv_widgets/lv_gauge.h
	${SOURCES_PREFIX}/lv_widgets/lv_img.c
	${SOURCES_PREFIX}/lv_widgets/lv_win.h
	${SOURCES_PREFIX}/lv_widgets/lv_imgbtn.c
	${SOURCES_PREFIX}/lv_widgets/lv_slider.c
	${SOURCES_PREFIX}/lv_widgets/lv_linemeter.c
	${SOURCES_PREFIX}/lv_widgets/lv_btn.h
	${SOURCES_PREFIX}/lv_widgets/lv_dropdown.c
	${SOURCES_PREFIX}/lv_widgets/lv_bar.c
	${SOURCES_PREFIX}/lv_widgets/lv_roller.h
	${SOURCES_PREFIX}/lv_widgets/lv_table.c
	${SOURCES_PREFIX}/lv_widgets/lv_arc.c
	${SOURCES_PREFIX}/lv_widgets/lv_objmask.h
	${SOURCES_PREFIX}/lv_widgets/lv_line.c
	${SOURCES_PREFIX}/lv_widgets/lv_tabview.c
	${SOURCES_PREFIX}/lv_widgets/lv_checkbox.c
	${SOURCES_PREFIX}/lv_widgets/lv_chart.h
	${SOURCES_PREFIX}/lv_widgets/lv_switch.c
	${SOURCES_PREFIX}/lv_widgets/lv_textarea.h
	${SOURCES_PREFIX}/lv_widgets/lv_msgbox.h
	${SOURCES_PREFIX}/lv_widgets/lv_spinbox.h
	${SOURCES_PREFIX}/lv_widgets/lv_canvas.c
	${SOURCES_PREFIX}/lv_widgets/lv_calendar.c
	${SOURCES_PREFIX}/lv_widgets/lv_objx_templ.c
	${SOURCES_PREFIX}/lv_widgets/lv_led.h
	${SOURCES_PREFIX}/lv_widgets/lv_tileview.h
	${SOURCES_PREFIX}/lv_widgets/lv_spinner.c
	${SOURCES_PREFIX}/lv_widgets/lv_btnmatrix.h
	${SOURCES_PREFIX}/lv_widgets/lv_cont.h
	${SOURCES_PREFIX}/lv_themes/lv_theme_mono.h
	${SOURCES_PREFIX}/lv_themes/lv_theme_empty.h
	${SOURCES_PREFIX}/lv_themes/lv_theme.c
	${SOURCES_PREFIX}/lv_themes/lv_themes.mk
	${SOURCES_PREFIX}/lv_themes/lv_theme_template.h
	${SOURCES_PREFIX}/lv_themes/lv_theme_material.c
	${SOURCES_PREFIX}/lv_themes/lv_theme_empty.c
	${SOURCES_PREFIX}/lv_themes/lv_theme.h
	${SOURCES_PREFIX}/lv_themes/lv_theme_mono.c
	${SOURCES_PREFIX}/lv_themes/lv_theme_template.c
	${SOURCES_PREFIX}/lv_themes/lv_theme_material.h
	${SOURCES_PREFIX}/lv_conf_internal.h
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_stm32_dma2d.h
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_vglite.h
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_pxp_osa.c
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_pxp.h
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_vglite.c
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_stm32_dma2d.c
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_pxp_osa.h
	${SOURCES_PREFIX}/lv_gpu/lv_gpu.mk
	${SOURCES_PREFIX}/lv_gpu/lv_gpu_nxp_pxp.c
	${SOURCES_PREFIX}/lv_hal/lv_hal.mk
	${SOURCES_PREFIX}/lv_hal/lv_hal_tick.h
	${SOURCES_PREFIX}/lv_hal/lv_hal.h
	${SOURCES_PREFIX}/lv_hal/lv_hal_indev.h
	${SOURCES_PREFIX}/lv_hal/lv_hal_disp.h
	${SOURCES_PREFIX}/lv_hal/lv_hal_tick.c
	${SOURCES_PREFIX}/lv_hal/lv_hal_indev.c
	${SOURCES_PREFIX}/lv_hal/lv_hal_disp.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_line.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_triangle.c
	${SOURCES_PREFIX}/lv_draw/lv_img_decoder.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_label.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_arc.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_rect.c
	${SOURCES_PREFIX}/lv_draw/lv_img_cache.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_blend.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_mask.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_img.c
	${SOURCES_PREFIX}/lv_draw/lv_img_buf.h
	${SOURCES_PREFIX}/lv_draw/lv_draw.h
	${SOURCES_PREFIX}/lv_draw/lv_img_decoder.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_triangle.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_line.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_blend.c
	${SOURCES_PREFIX}/lv_draw/lv_img_cache.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_mask.c
	${SOURCES_PREFIX}/lv_draw/lv_draw.mk
	${SOURCES_PREFIX}/lv_draw/lv_draw_rect.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_arc.h
	${SOURCES_PREFIX}/lv_draw/lv_draw_label.c
	${SOURCES_PREFIX}/lv_draw/lv_draw_img.h
	${SOURCES_PREFIX}/lv_draw/lv_img_buf.c
	${SOURCES_PREFIX}/lvgl.h
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_28_compressed.c
	${SOURCES_PREFIX}/lv_font/lv_font_fmt_txt.h
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_10.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_14.c
	${SOURCES_PREFIX}/lv_font/lv_font_unscii_8.c
	${SOURCES_PREFIX}/lv_font/lv_symbol_def.h
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_40.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_44.c
	${SOURCES_PREFIX}/lv_font/lv_font_loader.c
	${SOURCES_PREFIX}/lv_font/lv_font_dejavu_16_persian_hebrew.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_36.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_38.c
	${SOURCES_PREFIX}/lv_font/lv_font.mk
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_32.c
	${SOURCES_PREFIX}/lv_font/lv_font.h
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_28.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_22.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_26.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_18.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_12.c
	${SOURCES_PREFIX}/lv_font/lv_font_fmt_txt.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_16.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_48.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_42.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_46.c
	${SOURCES_PREFIX}/lv_font/lv_font.c
	${SOURCES_PREFIX}/lv_font/lv_font_unscii_16.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_34.c
	${SOURCES_PREFIX}/lv_font/lv_font_loader.h
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_8.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_30.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_20.c
	${SOURCES_PREFIX}/lv_font/lv_font_simsun_16_cjk.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_24.c
	${SOURCES_PREFIX}/lv_font/lv_font_montserrat_12_subpx.c
	${SOURCES_PREFIX}/)


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
	HAVE_CONFIG_H=1
	PRIVATE
	IS_LOCAL_BUILD=1
	)

target_compile_options(${RELEASE_TARGET}
	PUBLIC
	-Os
	)

target_include_directories(${RELEASE_TARGET}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src
	)

sos_sdk_library_target(DEBUG ${PROJECT_NAME} "${LIB_OPTION}" debug ${SOS_ARCH})
add_library(${DEBUG_TARGET} STATIC)
sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})
sos_sdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${SOS_ARCH} "")

if(SOS_IS_LINK)
	sos_sdk_library_target(COVERAGE ${PROJECT_NAME} "${LIB_OPTION}" coverage ${SOS_ARCH})
	add_library(${COVERAGE_TARGET} STATIC)
	sos_sdk_copy_target(${RELEASE_TARGET} ${COVERAGE_TARGET})
	sos_sdk_library_add_arch_targets("${COVERAGE_OPTIONS}" ${SOS_ARCH} "")
endif()

sos_sdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${SOS_ARCH} "")

set(HEADER_LIST
	${SOURCES_PREFIX}/src/lv_misc/lv_log.h
	${SOURCES_PREFIX}/src/lv_misc/lv_task.h
	${SOURCES_PREFIX}/src/lv_misc/lv_math.h
	${SOURCES_PREFIX}/src/lv_misc/lv_async.h
	${SOURCES_PREFIX}/src/lv_hal/lv_hal.h
	${SOURCES_PREFIX}/src/lv_core/lv_obj.h
	${SOURCES_PREFIX}/src/lv_core/lv_group.h
	${SOURCES_PREFIX}/src/lv_core/lv_indev.h
	${SOURCES_PREFIX}/src/lv_core/lv_refr.h
	${SOURCES_PREFIX}/src/lv_core/lv_disp.h
	${SOURCES_PREFIX}/src/lv_themes/lv_theme.h
	${SOURCES_PREFIX}/src/lv_font/lv_font.h
	${SOURCES_PREFIX}/src/lv_font/lv_font_loader.h
	${SOURCES_PREFIX}/src/lv_font/lv_font_fmt_txt.h
	${SOURCES_PREFIX}/src/lv_misc/lv_printf.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_btn.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_imgbtn.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_img.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_label.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_line.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_page.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_cont.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_list.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_chart.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_table.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_checkbox.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_cpicker.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_bar.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_slider.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_led.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_btnmatrix.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_keyboard.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_dropdown.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_roller.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_textarea.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_canvas.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_win.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_tabview.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_tileview.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_msgbox.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_objmask.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_gauge.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_linemeter.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_switch.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_arc.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_spinner.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_calendar.h
	${SOURCES_PREFIX}/src/lv_widgets/lv_spinbox.h
	${SOURCES_PREFIX}/src/lv_draw/lv_img_cache.h
	${SOURCES_PREFIX}/src/lv_api_map.h
	)

install(FILES
	./lvgl/src/lvgl.h
	${HEADER_LIST}
	DESTINATION include/lvgl)

install(FILES ${PROJECT_NAME}.cmake
	DESTINATION ${SOS_SDK_PATH}/cmake/targets)
