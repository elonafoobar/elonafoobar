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

#define JNI_METHOD_ARGLESS(name, signature)        \
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv(); \
    jobject activity = (jobject)SDL_AndroidGetActivity(); \
    jclass clazz(env->GetObjectClass(activity)); \
    jmethodID method_id = env->GetMethodID(clazz, name, signature); \
    env->CallVoidMethod(activity, method_id); \
    env->DeleteLocalRef(activity); \
    env->DeleteLocalRef(clazz)


void toast(std::string message, toast_length length)
{
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    jclass clazz(env->GetObjectClass(activity));
    jstring toast_message = env->NewStringUTF(message.c_str());
    jmethodID method_id = env->GetMethodID(clazz, "toast", "(Ljava/lang/String;I)V");
    env->CallVoidMethod(activity, method_id, toast_message, static_cast<int>(length));
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(clazz);
}

void set_requested_orientation(orientation orientation)
{
    JNI_METHOD("setRequestedOrientation", "(I)V", static_cast<int>(orientation));
}

void set_navigation_bar_visibility(bool enable)
{
    JNI_METHOD("setNavigationBarVisibility", "(Z)V", enable);
}

void vibrate(int duration_ms)
{
    JNI_METHOD("vibrate", "(I)V", duration_ms);
}

void vibrate_pulse()
{
    JNI_METHOD_ARGLESS("vibratePulse", "()V");
}

} // namespace android
} // namespace snail
} // namespace elona
