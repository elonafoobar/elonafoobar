if(SPIDER_BACKEND STREQUAL "BOOST_ASIO")
  set(SPIDER_LIBRARY spider_boost_asio)
  set(SPIDER_DIR boost_asio)
  add_definitions(-DSPIDER_BACKEND_BOOST_ASIO)
elseif(SPIDER_BACKEND STREQUAL "HEADLESS")
  set(SPIDER_LIBRARY spider_headless)
  set(SPIDER_DIR headless)
  add_definitions(-DSPIDER_BACKEND_HEADLESS)
else()
  message(FATAL_ERROR "Unsupported backend: ${SPIDER_BACKEND}")
endif()
# Expose SPIDER_LIBRARY.
set(SPIDER_LIBRARY ${SPIDER_LIBRARY} PARENT_SCOPE)

# Source files
set(SPIDER_SOURCES
  http/backends/${SPIDER_DIR}/request.cpp
  http/backends/${SPIDER_DIR}/core.cpp
  )

add_library(${SPIDER_LIBRARY} STATIC ${SPIDER_SOURCES})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/uri/include")
