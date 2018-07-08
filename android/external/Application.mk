APP_STL := c++_shared
APP_CPPFLAGS += -std=c++14
APP_LDFLAGS += -fuse-ld=gold
APP_ABI := armeabi-v7a
APP_PLATFORM=android-15

LOCAL_SRC_FILES := boost/1.66.0/lib/llvm/${TARGET_ARCH_ABI}/libboost_filesystem.so \
	boost/1.66.0/lib/llvm/${TARGET_ARCH_ABI}/libboost_system.so \
	boost/1.66.0/lib/llvm/${TARGET_ARCH_ABI}/libboost_iostreams.so 
