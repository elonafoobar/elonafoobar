#include "../android.hpp"
#include <jni.h>
#include "SDL_system.h"

namespace elona
{
namespace snail
{
namespace android
{

#define JNI_METHOD(name, signature, ...) \
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv(); \
    jobject activity = (jobject)SDL_AndroidGetActivity(); \
    jclass clazz(env->GetObjectClass(activity)); \
    jmethodID method_id = env->GetMethodID(clazz, name, signature); \
    env->CallVoidMethod(activity, method_id, __VA_ARGS__); \
    env->DeleteLocalRef(activity); \
    env->DeleteLocalRef(clazz)

void set_requested_orientation(orientation orientation)
{
    JNI_METHOD("setRequestedOrientation", "(I)V", static_cast<int>(orientation));
}

void set_navigation_bar_visibility(bool enable)
{
    JNI_METHOD("setNavigationBarVisibility", "(Z)V", enable);
}

void vibrate(long duration_ms)
{
    JNI_METHOD("vibrate", "(J)V", duration_ms);
}

void vibrate_pulse(int repeat_times)
{
    JNI_METHOD("vibratePulse", "(I)V", repeat_times);
}

} // namespace android
} // namespace snail
} // namespace elona
