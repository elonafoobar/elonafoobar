# Source files
set(UTIL_SOURCES
  backtrace.cpp
  filepathutil.cpp
  fps_counter.cpp
  )

if(WIN32)
  list(APPEND UTIL_SOURCES unicode_utf16.cpp)
endif()

if(ANDROID_GENERATE_BUILD_FILES)
  generate_android_mk(util SOURCES ${UTIL_SOURCES})
else()
  add_library(util STATIC ${UTIL_SOURCES})
endif()
