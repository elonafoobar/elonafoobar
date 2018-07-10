APP_STL := c++_shared
APP_CPPFLAGS += -std=c++14 -fexceptions
APP_LDFLAGS += -fuse-ld=gold -rdynamic -Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libgnustl_shared.so
APP_ABI := armeabi-v7a
APP_PLATFORM = android-15
NDK_TOOLCHAIN_VERSION := clang
NDK_DEBUG=0
V=1

LOCAL_SRC_FILES := boost/lib/llvm/${TARGET_ARCH_ABI}/libboost_filesystem.so \
	boost/lib/llvm/${TARGET_ARCH_ABI}/libboost_system.so \
	boost/lib/llvm/${TARGET_ARCH_ABI}/libboost_iostreams.so
