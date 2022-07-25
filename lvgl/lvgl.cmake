
if(NOT DEFINED IS_SDK AND CMSDK_IS_ARM)
	cmsdk_include_target(lvgl_kernel "${API_CONFIG_LIST}")
endif()
