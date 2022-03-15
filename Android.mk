LOCAL_PATH      := $(call my-dir)
include $(CLEAR_VARS)

# override strip command to strip all symbols from output library; no need to ship with those..
# cmd-strip = $(TOOLCHAIN_PREFIX)strip $1 

LOCAL_ARM_MODE  := arm
#LOCAL_PATH      := $(NDK_PROJECT_PATH)
LOCAL_MODULE    := openvr_api
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/*.cpp) $(wildcard $(LOCAL_PATH)/util/*.cpp) $(wildcard $(LOCAL_PATH)/sensors/*.cpp) $(wildcard $(LOCAL_PATH)/sensors/internal/*.cpp)
LOCAL_LDLIBS    := -llog -landroid -lGLESv2
 
include $(BUILD_SHARED_LIBRARY)
