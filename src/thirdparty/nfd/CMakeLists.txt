# Source files
set(SOURCES ./nfd_common.c)

if(MSVC)
  # Windows
  list(APPEND SOURCES ./nfd_win.cpp)
elseif (LINUX)
  # Linux
  list(APPEND SOURCES ./nfd_gtk.c)
else()
  # macOS
  list(APPEND SOURCES ./nfd_cocoa.m)
endif()


add_library(nfd STATIC ${SOURCES})


if(LINUX)
  find_package(PkgConfig)
  pkg_check_modules(NFD_GTK REQUIRED gtk+-3.0)
  target_include_directories(nfd PUBLIC ${NFD_GTK_INCLUDE_DIRS})
  target_link_libraries(nfd ${NFD_GTK_LIBRARIES})
endif()
