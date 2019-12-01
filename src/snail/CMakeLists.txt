# Library
if(SNAIL_BACKEND STREQUAL "HEADLESS")
  set(SNAIL_LIBRARY "snail_headless")
  add_definitions(-DSNAIL_BACKEND_HEADLESS)
elseif(SNAIL_BACKEND STREQUAL "SDL")
  set(SNAIL_LIBRARY "snail_sdl")
else()
  message(FATAL_ERROR "Unsupported snail backend: ${SNAIL_BACKEND}")
endif()
# Expose SNAIL_LIBRARY.
set(SNAIL_LIBRARY ${SNAIL_LIBRARY} PARENT_SCOPE)

string(TOLOWER ${SNAIL_BACKEND} SNAIL_DIR)

# Source files
set(SNAIL_SOURCES
  font.cpp
  image.cpp
  input.cpp
  surface.cpp

  backends/${SNAIL_DIR}/application.cpp
  backends/${SNAIL_DIR}/audio.cpp
  backends/${SNAIL_DIR}/detail.cpp
  backends/${SNAIL_DIR}/filedialog.cpp
  backends/${SNAIL_DIR}/hsp.cpp
  backends/${SNAIL_DIR}/messagebox.cpp
  backends/${SNAIL_DIR}/renderer.cpp
  backends/${SNAIL_DIR}/window.cpp
  backends/${SNAIL_DIR}/surface.cpp
  )

add_library(${SNAIL_LIBRARY} STATIC ${SNAIL_SOURCES})

if(NOT DEFINED SDL2_INCLUDE_DIR OR NOT DEFINED SDL2_LIBRARIES)
  find_package(SDL2 REQUIRED)
endif()
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${SNAIL_LIBRARY} ${SDL2_LIBRARY})

if(NOT DEFINED SDL2_IMAGE_INCLUDE_DIR OR NOT DEFINED SDL2_IMAGE_LIBRARIES)
  find_package(SDL2_image REQUIRED)
endif()
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${SNAIL_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

if(NOT DEFINED SDL2_TTF_INCLUDE_DIR OR NOT DEFINED SDL2_TTF_LIBRARIES)
  find_package(SDL2_ttf REQUIRED)
endif()
include_directories(${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${SNAIL_LIBRARY} ${SDL2_TTF_LIBRARIES})

if(NOT DEFINED SDL2_MIXER_INCLUDE_DIR OR NOT DEFINED SDL2_MIXER_LIBRARIES)
  find_package(SDL2_mixer REQUIRED)
endif()
include_directories(${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(${SNAIL_LIBRARY} ${SDL2_MIXER_LIBRARIES})

if(NOT SNAIL_BACKEND STREQUAL "HEADLESS")
  target_link_libraries(${SNAIL_LIBRARY} nfd)
endif()
