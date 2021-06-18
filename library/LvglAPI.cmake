
if(NOT DEFINED API_IS_SDK)
	include(API)
	if(SOS_IS_LINK)
		sos_sdk_include_target(lvgl "${API_CONFIG_LIST}")
	endif()
	sos_sdk_include_target(LvglAPI "${API_CONFIG_LIST}")
endif()
