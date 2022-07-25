
set(LIBRARIES ThreadAPI FsAPI ChronoAPI VarAPI)
if(CMSDK_IS_LINK)
	list(APPEND LIBRARIES WindowAPI)
	list(APPEND LIBRARIES lvgl)
endif()

api_add_api_library(LvglAPI "${LIBRARIES}")

if((CMSDK_IS_ARM AND API_IS_SDK) OR IS_BOOTSTRAP)
	macro(add_lvgl_include ARCH)
		target_include_directories(LvglAPI_debug_${ARCH}
			PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/lvgl/src>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/include/lvgl>
			$<INSTALL_INTERFACE:include/lvgl/src>
			$<INSTALL_INTERFACE:include/lvgl>
			)

		target_include_directories(LvglAPI_release_${ARCH}
			PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/lvgl/src>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/include/lvgl>
			$<INSTALL_INTERFACE:include/lvgl/src>
			$<INSTALL_INTERFACE:include/lvgl>
			)

		target_compile_definitions(LvglAPI_debug_${ARCH}
			PUBLIC
			LV_CONF_INCLUDE_SIMPLE=1
			)

		target_compile_definitions(LvglAPI_release_${ARCH}
			PUBLIC
			LV_CONF_INCLUDE_SIMPLE=1
			)
	endmacro()

	add_lvgl_include(${CMSDK_ARCH})
	foreach(ARCH ${CMSDK_ARCH_LIST})
		add_lvgl_include(${ARCH})
	endforeach()
endif()


