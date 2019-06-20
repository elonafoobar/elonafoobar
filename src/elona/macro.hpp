#pragma once



#define ELONA_TALK_SCENE_CUT() \
    do \
    { \
        talk_window_query(); \
        if (scenemode) \
        { \
            if (scene_cut == 1) \
            { \
                return TalkResult::talk_end; \
            } \
        } \
    } while (0)


#define ELONA_APPEND_RESPONSE(x, y) \
    do \
    { \
        list(0, listmax) = (x); \
        listn(0, listmax) = (y); \
        ++listmax; \
    } while (0)

#define UNUSED(x) (void)x



#if defined(__clang__) || defined(__GNUC__)
#define ELONA_NODISCARD_ATTR __attribute__((warn_unused_result))
#elif defined(MSVC)
#define ELONA_NODISCARD_ATTR _Check_return_
#else
#define ELONA_NODISCARD_ATTR
#endif
