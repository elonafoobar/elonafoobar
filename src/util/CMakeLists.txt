# Source files
set(UTIL_SOURCES
  backtrace.cpp
  filesystem.cpp
  fps_counter.cpp
  )

add_library(util STATIC ${UTIL_SOURCES})
