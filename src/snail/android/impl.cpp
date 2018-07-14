#include "../android.hpp"
#include <jni.h>
#include "SDL_system.h"

namespace elona
{
namespace snail
{
namespace android
{

void set_requested_orientation(orientation orientation)
{
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    jclass clazz(env->GetObjectClass(activity));
    jmethodID method_id = env->GetMethodID(clazz, "setRequestedOrientation", "(I)V");
    env->CallVoidMethod(activity, method_id, static_cast<int>(orientation));
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(clazz);
}

}
}
}
