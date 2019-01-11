# Source files
set(SOURCES ./nfd_common.c)

if(MSVC)
    # Windows
    list(APPEND SOURCES ./nfd_win.cpp)
elseif (LINUX)
    # Linux
    list(APPEND SOURCES ./nfd_gtk.cpp)
else()
    # macOS
    list(APPEND SOURCES ./nfd_cocoa.m)
endif()


add_library(nfd STATIC ${SOURCES})
include_directories(./include)