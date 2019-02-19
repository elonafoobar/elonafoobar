#pragma once

#include "defines.hpp"

#ifdef ELONA_BIG_ENDIAN
#define PUTIT_BIG_ENDIAN // BE
#else
#define PUTIT_LITTLE_ENDIAN // LE
#endif

#include "../putit/putit.hpp"
