# Source files
set(UTIL_SOURCES
  backtrace.cpp
  filepathutil.cpp
  fps_counter.cpp
  )

add_library(util STATIC ${UTIL_SOURCES})
