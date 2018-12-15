LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := util

SDL_PATH := ../../android/external

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/SDL2/include \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_mixer \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_image \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_ttf \
$(LOCAL_PATH)/$(SDL_PATH)/boost/include

LOCAL_CPP_FEATURES := exceptions rtti

# Add your application source files here...
LOCAL_SRC_FILES := \
fps_counter.cpp \
profiler.cpp \

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image SDL2_ttf boost_filesystem boost_system

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CFLAGS += -Wextra -Wall -ffast-math $(LTO)

LOCAL_LDFLAGS += $(LOCAL_CFLAGS) $(LTO) -fPIC

include $(BUILD_SHARED_LIBRARY)
