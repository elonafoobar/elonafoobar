#pragma once



#define ELONA_APPEND_PROMPT(text, key, value) \
    do \
    { \
        promptl(0, promptmax) = (text); \
        promptl(1, promptmax) = (key); \
        promptl(2, promptmax) = (value); \
        ++promptmax; \
    } while (0)


#define ELONA_YES_NO_PROMPT() \
    do \
    { \
        ELONA_APPEND_PROMPT(i18n::_(u8"ui", u8"yes"), u8"y"s, u8"0"s); \
        ELONA_APPEND_PROMPT(i18n::_(u8"ui", u8"no"), u8"n"s, u8"1"s); \
    } while (0)
