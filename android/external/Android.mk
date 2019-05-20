include $(call all-subdir-makefiles)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -lz
LOCAL_SHARED_LIBRARIES := util snail elona
