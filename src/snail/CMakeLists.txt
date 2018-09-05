option(SNAIL_HEADLESS "Don't render anything" OFF)

# Library
if(SNAIL_HEADLESS)
  set(LIBRARY_NAME snail_headless)
  add_definitions(-DSNAIL_RENDERER_HEADLESS)
else(SNAIL_HEADLESS)
  set(LIBRARY_NAME snail)
  add_definitions(-DSNAIL_RENDERER_SDL)
endif(SNAIL_HEADLESS)

# Source files
set(SNAIL_SOURCES
    application.cpp
    audio.cpp
    detail/sdl.cpp
    font.cpp
    fpsmanager.cpp
    hsp.cpp
    image.cpp
    input.cpp
    messagebox.cpp
    renderer.cpp
    scene.cpp
    touch_input.cpp
    window.cpp
    android.cpp
)

add_library(${LIBRARY_NAME} STATIC ${SNAIL_SOURCES})

if(NOT DEFINED SDL2_INCLUDE_DIR OR NOT DEFINED SDL2_LIBRARIES)
    find_package(SDL2 REQUIRED)
endif()
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${SDL2_LIBRARY})

if(NOT DEFINED SDL2_IMAGE_INCLUDE_DIR OR NOT DEFINED SDL2_IMAGE_LIBRARIES)
    find_package(SDL2_image REQUIRED)
endif()
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${SDL2_IMAGE_LIBRARIES})

if(NOT DEFINED SDL2_TTF_INCLUDE_DIR OR NOT DEFINED SDL2_TTF_LIBRARIES)
    find_package(SDL2_ttf REQUIRED)
endif()
include_directories(${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${SDL2_TTF_LIBRARIES})

if(NOT DEFINED SDL2_MIXER_INCLUDE_DIR OR NOT DEFINED SDL2_MIXER_LIBRARIES)
    find_package(SDL2_mixer REQUIRED)
endif()
include_directories(${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${SDL2_MIXER_LIBRARIES})
