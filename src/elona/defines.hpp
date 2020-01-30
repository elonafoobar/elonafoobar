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
#else
#define ELONA_OS_OTHERS
#endif


// Compiler
#if BOOST_COMP_CLANG
#define ELONA_COMPILER_CLANG
#endif


// Endianness
#if BOOST_ENDIAN_BIG_BYTE
#define ELONA_BIG_ENDIAN
#elif BOOST_ENDIAN_LITTLE_BYTE
#define ELONA_LITTLE_ENDIAN
#else
#error "Unsupported endianness"
#endif
