# Source files
set(SNAIL_SOURCES
    application.cpp
    detail/sdl.cpp
    font.cpp
    fpsmanager.cpp
    image.cpp
    input.cpp
    messagebox.cpp
    renderer.cpp
    scene.cpp
    window.cpp
)


# Library
add_library(snail STATIC ${SNAIL_SOURCES})
