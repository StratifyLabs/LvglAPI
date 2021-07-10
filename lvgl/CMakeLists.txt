cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

set(GIT_REPOSITORY "https://github.com/lvgl/lvgl.git")
set(GIT_BRANCH "release/v8.0")
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
	message(STATUS "Need to clone for the first call to cmake")
	execute_process(
		COMMAND git clone --branch ${GIT_BRANCH} ${GIT_REPOSITORY}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()


# Make a copy of lv_conf_template.h if it doesn't exist already
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lv_conf.h)
	file(READ
		${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lv_conf_template.h
		TEMPLATE_CONTENTS)
	file(WRITE
		${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lv_conf.h
		${TEMPLATE_CONTENTS}
		)
endif()


project(lvgl C)

set(SOURCES_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src)


set(PRIVATE_SOURCELIST
	${CMAKE_CURRENT_SOURCE_DIR}/lvgl_api.c
	${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lv_conf.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lvgl_api.h
	${SOURCES_PREFIX}/lv_api_map.h
	${SOURCES_PREFIX}/misc/lv_printf.h
	${SOURCES_PREFIX}/misc/lv_utils.c
	${SOURCES_PREFIX}/misc/lv_templ.h
	${SOURCES_PREFIX}/misc/lv_async.h
	${SOURCES_PREFIX}/misc/lv_txt.c
	${SOURCES_PREFIX}/misc/lv_timer.h
	${SOURCES_PREFIX}/misc/lv_math.h
	${SOURCES_PREFIX}/misc/lv_anim.h
	${SOURCES_PREFIX}/misc/lv_tlsf.h
	${SOURCES_PREFIX}/misc/lv_style.c
	${SOURCES_PREFIX}/misc/lv_style_gen.c
	${SOURCES_PREFIX}/misc/lv_mem.c
	${SOURCES_PREFIX}/misc/lv_fs.c
	${SOURCES_PREFIX}/misc/lv_bidi.h
	${SOURCES_PREFIX}/misc/lv_txt_ap.c
	${SOURCES_PREFIX}/misc/lv_gc.h
	${SOURCES_PREFIX}/misc/lv_color.c
	${SOURCES_PREFIX}/misc/lv_ll.c
	${SOURCES_PREFIX}/misc/lv_log.c
	${SOURCES_PREFIX}/misc/lv_area.c
	${SOURCES_PREFIX}/misc/lv_assert.h
	${SOURCES_PREFIX}/misc/lv_timer.c
	${SOURCES_PREFIX}/misc/lv_async.c
	${SOURCES_PREFIX}/misc/lv_txt.h
	${SOURCES_PREFIX}/misc/lv_utils.h
	${SOURCES_PREFIX}/misc/lv_templ.c
	${SOURCES_PREFIX}/misc/lv_printf.c
	${SOURCES_PREFIX}/misc/lv_types.h
	${SOURCES_PREFIX}/misc/lv_style_gen.h
	${SOURCES_PREFIX}/misc/lv_mem.h
	${SOURCES_PREFIX}/misc/lv_style.h
	${SOURCES_PREFIX}/misc/lv_tlsf.c
	${SOURCES_PREFIX}/misc/lv_math.c
	${SOURCES_PREFIX}/misc/lv_anim.c
	${SOURCES_PREFIX}/misc/lv_txt_ap.h
	${SOURCES_PREFIX}/misc/lv_gc.c
	${SOURCES_PREFIX}/misc/lv_bidi.c
	${SOURCES_PREFIX}/misc/lv_fs.h
	${SOURCES_PREFIX}/misc/lv_area.h
	${SOURCES_PREFIX}/misc/lv_log.h
	${SOURCES_PREFIX}/misc/lv_ll.h
	${SOURCES_PREFIX}/misc/lv_color.h
	${SOURCES_PREFIX}/gpu/lv_gpu_stm32_dma2d.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_vglite.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp_osa.c
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_vglite.c
	${SOURCES_PREFIX}/gpu/lv_gpu_stm32_dma2d.c
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp_osa.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp.c
	${SOURCES_PREFIX}/core/lv_obj_style.h
	${SOURCES_PREFIX}/core/lv_group.h
	${SOURCES_PREFIX}/core/lv_indev.c
	${SOURCES_PREFIX}/core/lv_theme.c
	${SOURCES_PREFIX}/core/lv_obj_style_gen.h
	${SOURCES_PREFIX}/core/lv_disp.c
	${SOURCES_PREFIX}/core/lv_obj_class.c
	${SOURCES_PREFIX}/core/lv_obj.h
	${SOURCES_PREFIX}/core/lv_refr.c
	${SOURCES_PREFIX}/core/lv_indev_scroll.h
	${SOURCES_PREFIX}/core/lv_event.c
	${SOURCES_PREFIX}/core/lv_obj_pos.h
	${SOURCES_PREFIX}/core/lv_obj_scroll.h
	${SOURCES_PREFIX}/core/lv_obj_tree.h
	${SOURCES_PREFIX}/core/lv_obj_draw.c
	${SOURCES_PREFIX}/core/lv_obj_class.h
	${SOURCES_PREFIX}/core/lv_disp.h
	${SOURCES_PREFIX}/core/lv_obj.c
	${SOURCES_PREFIX}/core/lv_obj_style_gen.c
	${SOURCES_PREFIX}/core/lv_theme.h
	${SOURCES_PREFIX}/core/lv_indev.h
	${SOURCES_PREFIX}/core/lv_obj_style.c
	${SOURCES_PREFIX}/core/lv_group.c
	${SOURCES_PREFIX}/core/lv_event.h
	${SOURCES_PREFIX}/core/lv_indev_scroll.c
	${SOURCES_PREFIX}/core/lv_refr.h
	${SOURCES_PREFIX}/core/lv_obj_pos.c
	${SOURCES_PREFIX}/core/lv_obj_draw.h
	${SOURCES_PREFIX}/core/lv_obj_tree.c
	${SOURCES_PREFIX}/core/lv_obj_scroll.c
	${SOURCES_PREFIX}/hal/lv_hal_tick.h
	${SOURCES_PREFIX}/hal/lv_hal.h
	${SOURCES_PREFIX}/hal/lv_hal_indev.h
	${SOURCES_PREFIX}/hal/lv_hal_disp.h
	${SOURCES_PREFIX}/hal/lv_hal_tick.c
	${SOURCES_PREFIX}/hal/lv_hal_indev.c
	${SOURCES_PREFIX}/hal/lv_hal_disp.c
	${SOURCES_PREFIX}/lv_conf_kconfig.h
	${SOURCES_PREFIX}/lv_conf_internal.h
	${SOURCES_PREFIX}/extra/lv_extra.h
	${SOURCES_PREFIX}/extra/layouts/flex/lv_flex.c
	${SOURCES_PREFIX}/extra/layouts/flex/lv_flex.h
	${SOURCES_PREFIX}/extra/layouts/grid/lv_grid.c
	${SOURCES_PREFIX}/extra/layouts/grid/lv_grid.h
	${SOURCES_PREFIX}/extra/layouts/lv_layouts.h
	${SOURCES_PREFIX}/extra/lv_extra.c
	${SOURCES_PREFIX}/extra/themes/basic/lv_theme_basic.c
	${SOURCES_PREFIX}/extra/themes/basic/lv_theme_basic.h
	${SOURCES_PREFIX}/extra/themes/default/lv_theme_default.h
	${SOURCES_PREFIX}/extra/themes/default/lv_theme_default.c
	${SOURCES_PREFIX}/extra/themes/mono/lv_theme_mono.h
	${SOURCES_PREFIX}/extra/themes/mono/lv_theme_mono.c
	${SOURCES_PREFIX}/extra/themes/lv_themes.h
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_dropdown.c
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar.h
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_arrow.h
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_dropdown.h
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_arrow.c
	${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar.c
	${SOURCES_PREFIX}/extra/widgets/led/lv_led.c
	${SOURCES_PREFIX}/extra/widgets/led/lv_led.h
	${SOURCES_PREFIX}/extra/widgets/win/lv_win.c
	${SOURCES_PREFIX}/extra/widgets/win/lv_win.h
	${SOURCES_PREFIX}/extra/widgets/chart/lv_chart.c
	${SOURCES_PREFIX}/extra/widgets/chart/lv_chart.h
	${SOURCES_PREFIX}/extra/widgets/spinbox/lv_spinbox.c
	${SOURCES_PREFIX}/extra/widgets/spinbox/lv_spinbox.h
	${SOURCES_PREFIX}/extra/widgets/imgbtn/lv_imgbtn.h
	${SOURCES_PREFIX}/extra/widgets/imgbtn/lv_imgbtn.c
	${SOURCES_PREFIX}/extra/widgets/spinner/lv_spinner.h
	${SOURCES_PREFIX}/extra/widgets/spinner/lv_spinner.c
	${SOURCES_PREFIX}/extra/widgets/tabview/lv_tabview.h
	${SOURCES_PREFIX}/extra/widgets/tabview/lv_tabview.c
	${SOURCES_PREFIX}/extra/widgets/msgbox/lv_msgbox.c
	${SOURCES_PREFIX}/extra/widgets/msgbox/lv_msgbox.h
	${SOURCES_PREFIX}/extra/widgets/span/lv_span.h
	${SOURCES_PREFIX}/extra/widgets/span/lv_span.c
	${SOURCES_PREFIX}/extra/widgets/colorwheel/lv_colorwheel.h
	${SOURCES_PREFIX}/extra/widgets/colorwheel/lv_colorwheel.c
	${SOURCES_PREFIX}/extra/widgets/lv_widgets.h
	${SOURCES_PREFIX}/extra/widgets/list/lv_list.h
	${SOURCES_PREFIX}/extra/widgets/list/lv_list.c
	${SOURCES_PREFIX}/extra/widgets/animimg/lv_animimg.c
	${SOURCES_PREFIX}/extra/widgets/animimg/lv_animimg.h
	${SOURCES_PREFIX}/extra/widgets/meter/lv_meter.c
	${SOURCES_PREFIX}/extra/widgets/meter/lv_meter.h
	${SOURCES_PREFIX}/extra/widgets/tileview/lv_tileview.c
	${SOURCES_PREFIX}/extra/widgets/tileview/lv_tileview.h
	${SOURCES_PREFIX}/extra/widgets/keyboard/lv_keyboard.c
	${SOURCES_PREFIX}/extra/widgets/keyboard/lv_keyboard.h
	${SOURCES_PREFIX}/font/lv_font_montserrat_28_compressed.c
	${SOURCES_PREFIX}/font/lv_font_fmt_txt.h
	${SOURCES_PREFIX}/font/lv_font_montserrat_10.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_14.c
	${SOURCES_PREFIX}/font/lv_font_unscii_8.c
	${SOURCES_PREFIX}/font/lv_symbol_def.h
	${SOURCES_PREFIX}/font/lv_font_montserrat_40.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_44.c
	${SOURCES_PREFIX}/font/lv_font_loader.c
	${SOURCES_PREFIX}/font/lv_font_dejavu_16_persian_hebrew.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_36.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_38.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_32.c
	${SOURCES_PREFIX}/font/lv_font.h
	${SOURCES_PREFIX}/font/korean.ttf
	${SOURCES_PREFIX}/font/lv_font_montserrat_28.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_22.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_26.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_18.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_12.c
	${SOURCES_PREFIX}/font/lv_font_fmt_txt.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_16.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_48.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_42.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_46.c
	${SOURCES_PREFIX}/font/lv_font.c
	${SOURCES_PREFIX}/font/lv_font_unscii_16.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_34.c
	${SOURCES_PREFIX}/font/lv_font_loader.h
	${SOURCES_PREFIX}/font/lv_font_montserrat_8.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_30.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_20.c
	${SOURCES_PREFIX}/font/lv_font_simsun_16_cjk.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_24.c
	${SOURCES_PREFIX}/font/lv_font_montserrat_12_subpx.c
	${SOURCES_PREFIX}/lvgl.h
	${SOURCES_PREFIX}/../lvgl.h
	${SOURCES_PREFIX}/draw/lv_draw_line.c
	${SOURCES_PREFIX}/draw/lv_draw_triangle.c
	${SOURCES_PREFIX}/draw/lv_img_decoder.c
	${SOURCES_PREFIX}/draw/lv_draw_label.h
	${SOURCES_PREFIX}/draw/lv_draw_arc.c
	${SOURCES_PREFIX}/draw/lv_draw_rect.c
	${SOURCES_PREFIX}/draw/lv_img_cache.h
	${SOURCES_PREFIX}/draw/lv_draw_blend.h
	${SOURCES_PREFIX}/draw/lv_draw_mask.h
	${SOURCES_PREFIX}/draw/lv_draw_img.c
	${SOURCES_PREFIX}/draw/lv_img_buf.h
	${SOURCES_PREFIX}/draw/lv_draw.h
	${SOURCES_PREFIX}/draw/lv_img_decoder.h
	${SOURCES_PREFIX}/draw/lv_draw_triangle.h
	${SOURCES_PREFIX}/draw/lv_draw_line.h
	${SOURCES_PREFIX}/draw/lv_draw_blend.c
	${SOURCES_PREFIX}/draw/lv_img_cache.c
	${SOURCES_PREFIX}/draw/lv_draw_mask.c
	${SOURCES_PREFIX}/draw/lv_draw_rect.h
	${SOURCES_PREFIX}/draw/lv_draw_arc.h
	${SOURCES_PREFIX}/draw/lv_draw_label.c
	${SOURCES_PREFIX}/draw/lv_draw_img.h
	${SOURCES_PREFIX}/draw/lv_img_buf.c
	${SOURCES_PREFIX}/widgets/lv_slider.h
	${SOURCES_PREFIX}/widgets/lv_img.h
	${SOURCES_PREFIX}/widgets/lv_label.c
	${SOURCES_PREFIX}/widgets/lv_table.h
	${SOURCES_PREFIX}/widgets/lv_roller.c
	${SOURCES_PREFIX}/widgets/lv_arc.h
	${SOURCES_PREFIX}/widgets/lv_bar.h
	${SOURCES_PREFIX}/widgets/lv_dropdown.h
	${SOURCES_PREFIX}/widgets/lv_btn.c
	${SOURCES_PREFIX}/widgets/lv_canvas.h
	${SOURCES_PREFIX}/widgets/lv_objx_templ.h
	${SOURCES_PREFIX}/widgets/lv_textarea.c
	${SOURCES_PREFIX}/widgets/lv_switch.h
	${SOURCES_PREFIX}/widgets/lv_checkbox.h
	${SOURCES_PREFIX}/widgets/lv_line.h
	${SOURCES_PREFIX}/widgets/lv_btnmatrix.c
	${SOURCES_PREFIX}/widgets/lv_label.h
	${SOURCES_PREFIX}/widgets/lv_img.c
	${SOURCES_PREFIX}/widgets/lv_slider.c
	${SOURCES_PREFIX}/widgets/lv_btn.h
	${SOURCES_PREFIX}/widgets/lv_dropdown.c
	${SOURCES_PREFIX}/widgets/lv_bar.c
	${SOURCES_PREFIX}/widgets/lv_roller.h
	${SOURCES_PREFIX}/widgets/lv_table.c
	${SOURCES_PREFIX}/widgets/lv_arc.c
	${SOURCES_PREFIX}/widgets/lv_line.c
	${SOURCES_PREFIX}/widgets/lv_checkbox.c
	${SOURCES_PREFIX}/widgets/lv_switch.c
	${SOURCES_PREFIX}/widgets/lv_textarea.h
	${SOURCES_PREFIX}/widgets/lv_canvas.c
	${SOURCES_PREFIX}/widgets/lv_objx_templ.c
	${SOURCES_PREFIX}/widgets/lv_btnmatrix.h
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
	LV_CONF_INCLUDE_SIMPLE=1
	PRIVATE
	)

target_compile_options(${RELEASE_TARGET}
	PUBLIC
	-Os
	)

target_include_directories(${RELEASE_TARGET}
	PUBLIC
	$<INSTALL_INTERFACE:include/lvgl>
	$<INSTALL_INTERFACE:include/lvgl/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lvgl>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
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

install(FILES
	${SOURCES_PREFIX}/core/lv_disp.h
	${SOURCES_PREFIX}/core/lv_event.h
	${SOURCES_PREFIX}/core/lv_group.h
	${SOURCES_PREFIX}/core/lv_indev.h
	${SOURCES_PREFIX}/core/lv_indev_scroll.h
	${SOURCES_PREFIX}/core/lv_obj.h
	${SOURCES_PREFIX}/core/lv_obj_class.h
	${SOURCES_PREFIX}/core/lv_obj_draw.h
	${SOURCES_PREFIX}/core/lv_obj_pos.h
	${SOURCES_PREFIX}/core/lv_obj_scroll.h
	${SOURCES_PREFIX}/core/lv_obj_style.h
	${SOURCES_PREFIX}/core/lv_obj_style_gen.h
	${SOURCES_PREFIX}/core/lv_obj_tree.h
	${SOURCES_PREFIX}/core/lv_refr.h
	${SOURCES_PREFIX}/core/lv_theme.h
	DESTINATION include/lvgl/src/core
	)

install(FILES
	${SOURCES_PREFIX}/draw/lv_draw_line.h
	${SOURCES_PREFIX}/draw/lv_draw_mask.h
	${SOURCES_PREFIX}/draw/lv_draw_rect.h
	${SOURCES_PREFIX}/draw/lv_draw_triangle.h
	${SOURCES_PREFIX}/draw/lv_img_buf.h
	${SOURCES_PREFIX}/draw/lv_img_cache.h
	${SOURCES_PREFIX}/draw/lv_img_decoder.h
	${SOURCES_PREFIX}/draw/lv_draw.h
	${SOURCES_PREFIX}/draw/lv_draw_arc.h
	${SOURCES_PREFIX}/draw/lv_draw_blend.h
	${SOURCES_PREFIX}/draw/lv_draw_img.h
	${SOURCES_PREFIX}/draw/lv_draw_label.h
	DESTINATION include/lvgl/src/draw
	)

install(FILES
	${SOURCES_PREFIX}/misc/lv_anim.h
	${SOURCES_PREFIX}/misc/lv_types.h
	${SOURCES_PREFIX}/misc/lv_area.h
	${SOURCES_PREFIX}/misc/lv_utils.h
	${SOURCES_PREFIX}/misc/lv_assert.h
	${SOURCES_PREFIX}/misc/lv_async.h
	${SOURCES_PREFIX}/misc/lv_bidi.h
	${SOURCES_PREFIX}/misc/lv_color.h
	${SOURCES_PREFIX}/misc/lv_fs.h
	${SOURCES_PREFIX}/misc/lv_gc.h
	${SOURCES_PREFIX}/misc/lv_ll.h
	${SOURCES_PREFIX}/misc/lv_log.h
	${SOURCES_PREFIX}/misc/lv_math.h
	${SOURCES_PREFIX}/misc/lv_mem.h
	${SOURCES_PREFIX}/misc/lv_printf.h
	${SOURCES_PREFIX}/misc/lv_style.h
	${SOURCES_PREFIX}/misc/lv_style_gen.h
	${SOURCES_PREFIX}/misc/lv_templ.h
	${SOURCES_PREFIX}/misc/lv_timer.h
	${SOURCES_PREFIX}/misc/lv_tlsf.h
	${SOURCES_PREFIX}/misc/lv_txt.h
	${SOURCES_PREFIX}/misc/lv_txt_ap.h
	DESTINATION include/lvgl/src/misc
	)

install(FILES
	${SOURCES_PREFIX}/widgets/lv_arc.h
	${SOURCES_PREFIX}/widgets/lv_bar.h
	${SOURCES_PREFIX}/widgets/lv_btn.h
	${SOURCES_PREFIX}/widgets/lv_btnmatrix.h
	${SOURCES_PREFIX}/widgets/lv_canvas.h
	${SOURCES_PREFIX}/widgets/lv_checkbox.h
	${SOURCES_PREFIX}/widgets/lv_dropdown.h
	${SOURCES_PREFIX}/widgets/lv_img.h
	${SOURCES_PREFIX}/widgets/lv_label.h
	${SOURCES_PREFIX}/widgets/lv_line.h
	${SOURCES_PREFIX}/widgets/lv_objx_templ.h
	${SOURCES_PREFIX}/widgets/lv_roller.h
	${SOURCES_PREFIX}/widgets/lv_slider.h
	${SOURCES_PREFIX}/widgets/lv_switch.h
	${SOURCES_PREFIX}/widgets/lv_table.h
	${SOURCES_PREFIX}/widgets/lv_textarea.h
	DESTINATION include/lvgl/src/widgets
	)

install(FILES
	${SOURCES_PREFIX}/font/lv_font.h
	${SOURCES_PREFIX}/font/lv_font_fmt_txt.h
	${SOURCES_PREFIX}/font/lv_font_loader.h
	${SOURCES_PREFIX}/font/lv_symbol_def.h
	DESTINATION include/lvgl/src/font
	)
install(FILES
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_pxp_osa.h
	${SOURCES_PREFIX}/gpu/lv_gpu_nxp_vglite.h
	${SOURCES_PREFIX}/gpu/lv_gpu_stm32_dma2d.h
	DESTINATION include/lvgl/src/gpu
	)

install(FILES
	${SOURCES_PREFIX}/hal/lv_hal.h
	${SOURCES_PREFIX}/hal/lv_hal_disp.h
	${SOURCES_PREFIX}/hal/lv_hal_indev.h
	${SOURCES_PREFIX}/hal/lv_hal_tick.h
	DESTINATION include/lvgl/src/hal
	)

install(FILES ${SOURCES_PREFIX}/extra/lv_extra.h DESTINATION include/lvgl/src/extra)

install(FILES ${SOURCES_PREFIX}/extra/widgets/lv_widgets.h DESTINATION include/lvgl/src/extra/widgets)
install(FILES ${SOURCES_PREFIX}/extra/widgets/animimg/lv_animimg.h DESTINATION include/lvgl/src/extra/widgets/animimg)
install(FILES ${SOURCES_PREFIX}/extra/widgets/imgbtn/lv_imgbtn.h DESTINATION include/lvgl/src/extra/widgets/imgbtn)
install(FILES ${SOURCES_PREFIX}/extra/widgets/span/lv_span.h DESTINATION include/lvgl/src/extra/widgets/span)
install(FILES ${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar.h DESTINATION include/lvgl/src/extra/widgets/calendar)
install(FILES ${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_arrow.h DESTINATION include/lvgl/src/extra/widgets/calendar)
install(FILES ${SOURCES_PREFIX}/extra/widgets/calendar/lv_calendar_header_dropdown.h DESTINATION include/lvgl/src/extra/widgets/calendar)
install(FILES ${SOURCES_PREFIX}/extra/widgets/keyboard/lv_keyboard.h DESTINATION include/lvgl/src/extra/widgets/keyboard)
install(FILES ${SOURCES_PREFIX}/extra/widgets/spinbox/lv_spinbox.h DESTINATION include/lvgl/src/extra/widgets/spinbox)
install(FILES ${SOURCES_PREFIX}/extra/widgets/led/lv_led.h DESTINATION include/lvgl/src/extra/widgets/led)
install(FILES ${SOURCES_PREFIX}/extra/widgets/spinner/lv_spinner.h DESTINATION include/lvgl/src/extra/widgets/spinner)
install(FILES ${SOURCES_PREFIX}/extra/widgets/list/lv_list.h DESTINATION include/lvgl/src/extra/widgets/list)
install(FILES ${SOURCES_PREFIX}/extra/widgets/tabview/lv_tabview.h DESTINATION include/lvgl/src/extra/widgets/tabview)
install(FILES ${SOURCES_PREFIX}/extra/widgets/chart/lv_chart.h DESTINATION include/lvgl/src/extra/widgets/chart)
install(FILES ${SOURCES_PREFIX}/extra/widgets/colorwheel/lv_colorwheel.h DESTINATION include/lvgl/src/extra/widgets/colorwheel)
install(FILES ${SOURCES_PREFIX}/extra/widgets/msgbox/lv_msgbox.h DESTINATION include/lvgl/src/extra/widgets/msgbox)
install(FILES ${SOURCES_PREFIX}/extra/widgets/tileview/lv_tileview.h DESTINATION include/lvgl/src/extra/widgets/tileview)
install(FILES ${SOURCES_PREFIX}/extra/widgets/meter/lv_meter.h DESTINATION include/lvgl/src/extra/widgets/meter)
install(FILES ${SOURCES_PREFIX}/extra/widgets/win/lv_win.h DESTINATION include/lvgl/src/extra/widgets/win)

install(FILES ${SOURCES_PREFIX}/extra/themes/lv_themes.h DESTINATION include/lvgl/src/extra/themes)
install(FILES ${SOURCES_PREFIX}/extra/themes/basic/lv_theme_basic.h DESTINATION include/lvgl/src/extra/themes/basic)
install(FILES ${SOURCES_PREFIX}/extra/themes/default/lv_theme_default.h DESTINATION include/lvgl/src/extra/themes/default)
install(FILES ${SOURCES_PREFIX}/extra/themes/mono/lv_theme_mono.h DESTINATION include/lvgl/src/extra/themes/mono)

install(FILES ${SOURCES_PREFIX}/extra/layouts/lv_layouts.h DESTINATION include/lvgl/src/extra/layouts)
install(FILES ${SOURCES_PREFIX}/extra/layouts/flex/lv_flex.h DESTINATION include/lvgl/src/extra/layouts/flex)
install(FILES ${SOURCES_PREFIX}/extra/layouts/grid/lv_grid.h DESTINATION include/lvgl/src/extra/layouts/grid)

install(FILES
	${SOURCES_PREFIX}/lvgl.h
	${SOURCES_PREFIX}/lv_api_map.h
	${SOURCES_PREFIX}/lv_conf_internal.h
	${SOURCES_PREFIX}/lv_conf_kconfig.h
	DESTINATION include/lvgl/src)

install(FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lvgl_api.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/lvgl/lv_conf.h
	${CMAKE_CURRENT_SOURCE_DIR}/lvgl/lvgl.h
	DESTINATION include/lvgl)

install(FILES ${PROJECT_NAME}.cmake
	DESTINATION ${SOS_SDK_PATH}/cmake/targets)


