#pragma once

#include <boost/predef.h>


// Operating system
#if BOOST_OS_WINDOWS
#define ELONA_OS_WINDOWS
#define NOMINMAX
#elif BOOST_OS_MACOS
#define ELONA_OS_MACOS
#elif BOOST_OS_LINUX
#define ELONA_OS_LINUX
#elif BOOST_OS_ANDROID
#define ELONA_OS_ANDROID
#else
#define ELONA_OS_OTHERS
#endif


// Endianness
#if BOOST_ENDIAN_BIG_BYTE
#define ELONA_BIG_ENDIAN
#elif BOOST_ENDIAN_LITTLE_BYTE
#define ELONA_LITTLE_ENDIAN
#else
#error "Unsupported endianness"
#endif


#ifdef ELONA_OS_ANDROID
#undef bcopy
#include <android/log.h>

#define LOG_TAG "Elona foobar"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

namespace elona
{
namespace defines
{
static const constexpr bool is_android =
#ifdef ELONA_OS_ANDROID
    true;
#else
    false;
#endif
} // namespace defines
} // namespace elona
