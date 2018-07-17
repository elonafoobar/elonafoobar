#include "android.hpp"

#ifdef ANDROID
#include "android/impl.cpp"
#else
#include "android/dummy.cpp"
#endif
