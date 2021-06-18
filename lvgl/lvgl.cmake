
if(NOT DEFINED IS_SDK AND SOS_IS_ARM)
	sos_sdk_include_target(lvgl_kernel "${API_CONFIG_LIST}")
endif()
