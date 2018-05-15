# CMake v2.8 or later
cmake_minimum_required(VERSION 3.0)


# Project
project(ElonaFoobar VERSION 0.2.2)


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
    ai.cpp
    animation.cpp
    audio.cpp
    autopick.cpp
    blending.cpp
    buff.cpp
    building.cpp
    calc.cpp
    card.cpp
    casino.cpp
    casino_card.cpp
    cat.cpp
    cell_draw.cpp
    character.cpp
    character_making.cpp
    class.cpp
    command.cpp
    config.cpp
    ctrl_file.cpp
    ctrl_inventory.cpp
    crafting.cpp
    debug.cpp
    draw.cpp
    elonacore.cpp
    enchantment.cpp
    event.cpp
    filesystem.cpp
    fish.cpp
    food.cpp
    foobar_save.cpp
    fov.cpp
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
    itemgen.cpp
    log.cpp
    magic.cpp
    main.cpp
    main_menu.cpp
    map.cpp
    map_cell.cpp
    mapgen.cpp
    mef.cpp
    menu.cpp
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
    ui.cpp
    variables.cpp
    wish.cpp
    ${PROJECT_BINARY_DIR}/version.cpp
)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${CORE_SOURCES})


# If a CMake prefix was not provided, assume dependencies are in "./deps"
if("${CMAKE_PREFIX_PATH}" STREQUAL "")
  get_filename_component(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/deps" ABSOLUTE)
  message("No dependency prefix provided, using ${CMAKE_PREFIX_PATH}")
else()
  message("Using provided dependency prefix ${CMAKE_PREFIX_PATH}")
endif()


# Copy folders
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
                   "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/data"
                   "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/lang"
                   "$<TARGET_FILE_DIR:${PROJECT_NAME}>/lang")


# Copy assets from Elona 1.22 if they are present
if(EXISTS "${CMAKE_PREFIX_PATH}/elona")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_PREFIX_PATH}/elona/graphic"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/graphic")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_PREFIX_PATH}/elona/map"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/map")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_PREFIX_PATH}/elona/original"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/original")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_PREFIX_PATH}/elona/sound"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/sound")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_PREFIX_PATH}/elona/user"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/user")
  message("Elona 1.22 distribution found.")
else()
  message(WARNING "Elona 1.22 distribution not found at ${CMAKE_PREFIX_PATH}/elona. The game cannot be run without assets. Please manually copy the 'graphic', 'map', 'original', 'sound' and 'user' directories from Elona 1.22 to the ElonaFoobar output path after building.")
endif()

if(WIN32)
  # Force FindBoost to look for libraries with -mt-sgd
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)

  # Set default project to be run when using Visual Studio
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

  # Specify dynamic libraries to copy to output folder after build
  file(GLOB copy_sources "${CMAKE_PREFIX_PATH}/lib/*${CMAKE_SHARED_LIBRARY_SUFFIX}")
  set(copy_dest "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  message("Will copy libraries to ${copy_dest}")

  # Perform the copy
  foreach(copy_source ${copy_sources})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E
                           copy_if_different ${copy_source} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  endforeach()
endif()

# Thirdparty libraries
if(MSVC)
    # boost_zlib isn't picked up on Windows unless explicitly declared
    find_package(Boost REQUIRED COMPONENTS system filesystem locale iostreams zlib)
else()
    find_package(Boost REQUIRED COMPONENTS system filesystem locale iostreams)
endif()
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

if(NOT DEFINED LUA_INCLUDE_DIR OR NOT DEFINED LUA_LIBRARIES)
    find_package(Lua REQUIRED)
endif()
include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})

if(NOT DEFINED SDL2_INCLUDE_DIR OR NOT DEFINED SDL2_LIBRARIES)
    find_package(SDL2 REQUIRED)
endif()
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

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

# Compiler options
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if(MSVC)
    add_definitions("-D_UNICODE")
    set(CMAKE_CXX_FLAGS "/W4 /source-charset:utf-8 /MT /EHsc")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif()

# Compiler options(debug build)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/MP8 /MTd /ZI /Od")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
endif()

# Force GCC to output warnings about undefined symbols
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    string(APPEND CMAKE_SHARED_LINKER_FLAGS " -Wl,--no-undefined")
endif()


# My libraries
add_subdirectory(snail)
target_link_libraries(${PROJECT_NAME} snail)


# Create macOS .app bundle
SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/ElonaFoobar")
IF(APPLE)
  SET(plugin_dest_dir ElonaFoobar.app/Contents/MacOS)
  SET(qtconf_dest_dir ElonaFoobar.app/Contents/Resources)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/ElonaFoobar.app")
ENDIF(APPLE)
IF(WIN32)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/ElonaFoobar.exe")
ENDIF(WIN32)

INSTALL(TARGETS ElonaFoobar
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)

SET(DIRS ${LINK_DIRECTORIES})

INSTALL(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
    " COMPONENT Runtime)
