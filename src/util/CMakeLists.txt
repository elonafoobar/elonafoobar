# Source files
set(UTIL_SOURCES
  filepathutil.cpp
  fps_counter.cpp
  )

if(ANDROID_GENERATE_BUILD_FILES)
  generate_android_mk(util SOURCES ${UTIL_SOURCES})
else()
  add_library(util STATIC ${UTIL_SOURCES})
endif()
