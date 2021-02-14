LOCAL_PATH      := $(call my-dir)
include $(CLEAR_VARS)
# 配置 native 层可以使用 log 打印
LOCAL_LDLIBS := -lm -llog

LOCAL_SRC_FILES := crash_test.cpp
LOCAL_MODULE    := crash_test
include $(BUILD_SHARED_LIBRARY)