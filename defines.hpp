#pragma once

#include <boost/predef.h>


#if BOOST_OS_WINDOWS
#define ELONA_OS_WINDOWS
#define NOMINMAX
#elif BOOST_OS_MACOS
#define ELONA_OS_MACOS
#elif BOOST_OS_LINUX
#define ELONA_OS_LINUX
#else
#define ELONA_OS_OTHERS
#endif
