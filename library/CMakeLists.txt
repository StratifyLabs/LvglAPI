
set(LIBRARIES FsAPI ChronoAPI VarAPI)
if(SOS_IS_LINK)
	list(APPEND LIBRARIES lvgl)
endif()

api_add_api_library(LvglAPI "${LIBRARIES}")


if((SOS_IS_ARM AND API_IS_SDK) OR IS_BOOTSTRAP)
	macro(add_lvgl_include ARCH)
		target_include_directories(LvglAPI_debug_${ARCH}
			PUBLIC
			PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/lvgl/src>
			)

		target_include_directories(LvglAPI_release_${ARCH}
			PUBLIC
			PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lvgl/lvgl/src>
			)
	endmacro()

	add_lvgl_include(${SOS_ARCH})
	foreach(ARCH ${SOS_ARCH_LIST})
		add_lvgl_include(${ARCH})
	endforeach()
endif()


