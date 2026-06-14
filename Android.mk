LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := html_chromium
# Собираем все cpp файлы в папке
LOCAL_SRC_FILES := $(wildcard *.cpp)
LOCAL_LDLIBS    := -llog -landroid
include $(BUILD_SHARED_LIBRARY)
