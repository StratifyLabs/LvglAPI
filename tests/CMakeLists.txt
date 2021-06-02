

set(DEPENDENCIES LvglAPI TestAPI FsAPI)
if(SOS_IS_LINK)
	#Stratify OS will have jansson include in the kernel
	list(APPEND DEPENDENCIES lvgl)
endif()

api_add_test_executable(LvglAPI 32768 "${DEPENDENCIES}")



