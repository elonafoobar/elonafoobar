# CMake v2.8 or later
cmake_minimum_required(VERSION 3.0)


# Project
project(ElonaFoobar VERSION 0.1.0)


# Versioning

# Get commit hash from Git
find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "Git not Found")
endif()
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION_REVISION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)


# Get date and time
string(TIMESTAMP PROJECT_VERSION_TIMESTAMP UTC)

# Get platform
set(PROJECT_VERSION_PLATFORM "${CMAKE_SYSTEM}")

# Versioning file
configure_file("${PROJECT_SOURCE_DIR}/version.cpp.in" "${PROJECT_BINARY_DIR}/version.cpp")


# C++14 or later
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Source files
set(CORE_SOURCES
    ability.cpp
    access_character_info.cpp
    access_item_db.cpp
    animation.cpp
    buff.cpp
    calc.cpp
    cat.cpp
    cell_draw.cpp
    character.cpp
    class.cpp
    config.cpp
    ctrl_file.cpp
    ctrl_inventory.cpp
    debug.cpp
    draw.cpp
    elonacore.cpp
    filesystem.cpp
    fish.cpp
    get_card_info.cpp
    get_random_item_id.cpp
    get_random_npc_id.cpp
    god.cpp
    i18n.cpp
    init.cpp
    initialize_map.cpp
    input.cpp
    item.cpp
    item_db.cpp
    item_material.cpp
    magic.cpp
    main.cpp
    map.cpp
    message.cpp
    proc_event.cpp
    race.cpp
    random.cpp
    set_item_info.cpp
    set_option.cpp
    std.cpp
    talk_npc.cpp
    talk_unique.cpp
    tcg.cpp
    text.cpp
    trait.cpp
    variables.cpp
    ${PROJECT_BINARY_DIR}/version.cpp
)


# Executable
add_executable(${PROJECT_NAME} ${CORE_SOURCES})


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


# Thirdparty libraries
find_package(Boost REQUIRED COMPONENTS system filesystem locale)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

if(NOT DEFINED LUA_INCLUDE_DIR OR NOT DEFINED LUA_LIBRARIES)
    find_package(lua REQUIRED)
endif()
include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})

if(NOT DEFINED SDL2_INCLUDE_DIR OR NOT DEFINED SDL2_LIBRARIES)
    find_package(SDL2 REQUIRED)
endif()
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(NOT DEFINED SDL2_IMAGE_INCLUDE_DIR OR NOT DEFINED SDL2_IMAGE_LIBRARIES)
    find_package(SDL2_image REQUIRED)
endif()
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

if(NOT DEFINED SDL2_TTF_INCLUDE_DIR OR NOT DEFINED SDL2_TTF_LIBRARIES)
    find_package(SDL2_ttf REQUIRED)
endif()
include_directories(${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

if(NOT DEFINED SDL2_MIXER_INCLUDE_DIR OR NOT DEFINED SDL2_MIXER_LIBRARIES)
    find_package(SDL2_mixer REQUIRED)
endif()
include_directories(${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})



# My libraries
add_subdirectory(snail)
target_link_libraries(${PROJECT_NAME} snail)



# Compiler options
if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /source-charset:utf-8 /MT /EHsc")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif()

# Compiler options(debug build)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
endif()
