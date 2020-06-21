#pragma once



#define ELONA_APPEND_RESPONSE(x, y) \
    do \
    { \
        list(0, listmax) = (x); \
        listn(0, listmax) = (y); \
        ++listmax; \
    } while (0)
