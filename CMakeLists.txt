# CMake v2.8 or later
cmake_minimum_required(VERSION 3.0)


# Project
project(ElonaFoobar VERSION 0.2.6)


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
configure_file("${PROJECT_SOURCE_DIR}/src/version.cpp.in" "${PROJECT_SOURCE_DIR}/src/version.cpp")


# C++14 or later
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Options
option(WITH_TESTS "Build test executable (TESTS or BENCH)" "NONE")

if((WITH_TESTS STREQUAL "TESTS") OR (WITH_TESTS STREQUAL "BENCH"))
  SET(SNAIL_HEADLESS ON CACHE BOOL "Snail headless")
  add_definitions(-DSNAIL_RENDERER_HEADLESS)
else()
  SET(SNAIL_HEADLESS OFF CACHE BOOL "Snail SDL")
  add_definitions(-DSNAIL_RENDERER_SDL)
endif()

# Source files
set(CORE_SOURCES
    src/ability.cpp
    src/access_character_info.cpp
    src/access_item_db.cpp
    src/adventurer.cpp
    src/activity.cpp
    src/ai.cpp
    src/animation.cpp
    src/audio.cpp
    src/autopick.cpp
    src/blending.cpp
    src/buff.cpp
    src/building.cpp
    src/calc.cpp
    src/card.cpp
    src/casino.cpp
    src/casino_card.cpp
    src/cat.cpp
    src/cell_draw.cpp
    src/character.cpp
    src/character_making.cpp
    src/character_status.cpp
    src/class.cpp
    src/command.cpp
    src/config.cpp
    src/config_def.cpp
    src/ctrl_file.cpp
    src/ctrl_inventory.cpp
    src/crafting.cpp
    src/debug.cpp
    src/dmgheal.cpp
    src/draw.cpp
    src/element.cpp
    src/elonacore.cpp
    src/enchantment.cpp
    src/equipment.cpp
    src/event.cpp
    src/filesystem.cpp
    src/fish.cpp
    src/food.cpp
    src/fov.cpp
    src/gdata.cpp
    src/get_card_info.cpp
    src/get_random_item_id.cpp
    src/get_random_npc_id.cpp
    src/god.cpp
    src/i18n.cpp
    src/init.cpp
    src/initialize_map.cpp
    src/input.cpp
    src/item.cpp
    src/item_db.cpp
    src/item_material.cpp
    src/itemgen.cpp
    src/log.cpp
    src/magic.cpp
    src/main_menu.cpp
    src/map.cpp
    src/map_cell.cpp
    src/mapgen.cpp
    src/mef.cpp
    src/menu.cpp
    src/message.cpp
    src/network.cpp
    src/proc_event.cpp
    src/proc_random_event.cpp
    src/quest.cpp
    src/race.cpp
    src/random.cpp
    src/set_item_info.cpp
    src/set_option.cpp
    src/shop.cpp
    src/status_ailment.cpp
    src/std.cpp
    src/talk.cpp
    src/talk_npc.cpp
    src/talk_unique.cpp
    src/tcg.cpp
    src/testing.cpp
    src/text.cpp
    src/trait.cpp
    src/turn_sequence.cpp
    src/ui.cpp
    src/variables.cpp
    src/wish.cpp
    src/lua_env/event_manager.cpp
    src/lua_env/handle_manager.cpp
    src/lua_env/lua_env.cpp
    src/lua_env/lua_api.cpp
    src/version.cpp
)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


# Executable
if(WITH_TESTS STREQUAL "TESTS")
  set (CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/catch2})
  add_library(Catch INTERFACE)
  target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

  # Test sources
  set(TEST_SOURCES
    src/tests/tests.cpp
    src/tests/util.cpp
    src/tests/config.cpp
    src/tests/config_def.cpp
    src/tests/lua_api.cpp
    src/tests/lua_callbacks.cpp
    src/tests/lua_events.cpp
    src/tests/lua_handles.cpp
    src/tests/lua_mods.cpp
    src/tests/lua_serialization.cpp
    src/tests/elonacore.cpp
    src/tests/i18n.cpp
    src/tests/i18n_builtins.cpp
    src/tests/i18n_regressions.cpp
    src/tests/serialization.cpp
    ${CORE_SOURCES}
    )

  add_executable(${PROJECT_NAME} ${TEST_SOURCES})
  target_link_libraries(${PROJECT_NAME} Catch)
elseif(WITH_TESTS STREQUAL "BENCH")
  add_subdirectory(thirdparty/hayai)

  # Benchmark sources
  set(BENCH_SOURCES
    src/bench/ai.cpp
    src/bench/generate.cpp
    src/bench/i18n.cpp
    src/bench/lua_callbacks.cpp
    src/bench/magic.cpp
    src/bench/util.cpp
    ${CORE_SOURCES}
    )

  add_executable(${PROJECT_NAME} ${BENCH_SOURCES})
  target_link_libraries(${PROJECT_NAME} hayai_main ${LIB_TIMING})
else()
  add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${CORE_SOURCES} src/main.cpp)
endif()


# If a CMake prefix was not provided, assume dependencies are in "./deps"
if("${CMAKE_PREFIX_PATH}" STREQUAL "")
  get_filename_component(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/deps" ABSOLUTE)
  message("No dependency prefix provided, using ${CMAKE_PREFIX_PATH}")
else()
  message("Using provided dependency prefix ${CMAKE_PREFIX_PATH}")
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
  message("Will copy libraries to output folder.")

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

if(WIN32)
  # Build custom version of Lua 5.3 with UTF-16 filename support
  add_subdirectory(${CMAKE_PREFIX_PATH}/lib/lua ${PROJECT_BINARY_DIR}/lib/lua)
  target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_PREFIX_PATH}/lib/lua/src/)
  target_link_libraries(${PROJECT_NAME} liblua53)
else()
  if(NOT DEFINED LUA_INCLUDE_DIR OR NOT DEFINED LUA_LIBRARIES)
    find_package(Lua REQUIRED)
  endif()
  include_directories(${LUA_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
endif()

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

if(WITH_TESTS STREQUAL "BENCH")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Force GCC to output warnings about undefined symbols
    string(APPEND CMAKE_CXX_FLAGS " -Wl,--no-undefined")
    # Disable deprecated declarations, because it causes warnings with Boost locale's use of auto_ptr
    string(APPEND CMAKE_CXX_FLAGS " -Wno-deprecated-declarations")
endif()

# My libraries
add_subdirectory(src/snail)

if((WITH_TESTS STREQUAL "TESTS") OR (WITH_TESTS STREQUAL "BENCH"))
  target_link_libraries(${PROJECT_NAME} snail_headless)
else()
  target_link_libraries(${PROJECT_NAME} snail)
endif()


INSTALL(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)

# Create macOS .app bundle
SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
IF(APPLE)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
ENDIF(APPLE)
IF(WIN32)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe")
ENDIF(WIN32)

SET(DIRS ${LINK_DIRECTORIES})

INSTALL(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
    " COMPONENT Runtime)

# Kludgy function to work around the lack of directory support in copy_if_different
function(copy_nonexisting src rel final)
  file(GLOB_RECURSE allfiles RELATIVE "${rel}" "${src}/*")

  foreach( each_file ${allfiles} )
    set(destinationfile "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${final}/${each_file}")
    set(sourcefile "${rel}/${each_file}")
    add_custom_command(TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND}
      -Ddestinationfile=${destinationfile}
      -Dsourcefile=${sourcefile}
      -P ${CMAKE_MODULE_PATH}/copy_nonexisting.cmake
      )
  endforeach(each_file)
endfunction()

# Copy folders
copy_nonexisting("runtime" "${CMAKE_SOURCE_DIR}/runtime" ".")

# Copy assets from Elona 1.22 if they are present
if(EXISTS "${CMAKE_PREFIX_PATH}/elona")
  copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/graphic" "${CMAKE_PREFIX_PATH}/elona/graphic" "graphic")
  copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/map" "${CMAKE_PREFIX_PATH}/elona/map" "map")
  copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/original" "${CMAKE_PREFIX_PATH}/elona/original" "original")
  copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/sound" "${CMAKE_PREFIX_PATH}/elona/sound" "sound")
  copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/user" "${CMAKE_PREFIX_PATH}/elona/user" "user")
  message("Elona 1.22 distribution found.")
else()
  message(WARNING "Elona 1.22 distribution not found at ${CMAKE_PREFIX_PATH}/elona. The game cannot be run without assets. Please manually copy the 'graphic', 'map', 'original', 'sound' and 'user' directories from Elona 1.22 to the ${PROJECT_NAME} output path after building.")
endif()

if((WITH_TESTS STREQUAL "TESTS") OR (WITH_TESTS STREQUAL "BENCH"))
  copy_nonexisting("${CMAKE_CURRENT_SOURCE_DIR}/src/tests/data" "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/data" "tests/data")
endif()

if(WITH_TESTS STREQUAL "TESTS")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/lua"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/lua")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                     "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/lua/classes"
                     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/lua/classes")
endif()
