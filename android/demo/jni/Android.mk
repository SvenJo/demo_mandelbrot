LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mandelbrot-demo 
LOCAL_SRC_FILES := demo.cpp

LOCAL_C_INCLUDES := /develop/sven/git/mandelbrot/include
LOCAL_C_INCLUDES += /develop/sven/git/mandelbrot/demo

LOCAL_CPPFLAGS += -DNDEBUG
LOCAL_CPPFLAGS += -O2

LOCAL_CFLAGS += -fopenmp # use CFLAGS for openmp
LOCAL_LDFLAGS += -fopenmp

LOCAL_CPPFLAGS := -std=c++11 -Wall         # whatever g++ flags you like
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like



include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
