
if(NOT DEFINED API_IS_SDK)
	include(API)
	if(CMSDK_IS_LINK)
		cmsdk_include_target(lvgl "${API_CONFIG_LIST}")
	endif()
	cmsdk_include_target(LvglAPI "${API_CONFIG_LIST}")
endif()
