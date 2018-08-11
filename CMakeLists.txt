# CMake v2.8 or later
cmake_minimum_required(VERSION 3.0)


# Project
project(Elona_foobar VERSION 0.2.6)


# Options
option(ANDROID_BUNDLE_ASSETS "Bundle assets with Android distribution" OFF)
option(ANDROID_GENERATE_PROPERTIES "Generate android/app/gradle.properties" OFF)


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

# Android version code. Increment on every distinct release.
set(PROJECT_VERSION_CODE 1)

# Versioning file
configure_file("${PROJECT_SOURCE_DIR}/src/version.cpp.in" "${PROJECT_SOURCE_DIR}/src/version.cpp")

# CMake is run last in the Android build process, so gradle.properties
# has to be generated beforehand.
if(ANDROID_GENERATE_PROPERTIES)
  configure_file("${PROJECT_SOURCE_DIR}/android/gradle.properties.in" "${PROJECT_SOURCE_DIR}/android/gradle.properties")
  return()
endif()


# C++14 or later
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(CORE_SOURCES
  src/ability.cpp
  src/access_character_info.cpp
  src/access_item_db.cpp
  src/activity.cpp
  src/adventurer.cpp
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
  src/crafting.cpp
  src/ctrl_file.cpp
  src/ctrl_inventory.cpp
  src/db_item.cpp
  src/db_music.cpp
  src/db_sound.cpp
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
  src/item_load_desc.cpp
  src/item_material.cpp
  src/itemgen.cpp
  src/lion.cpp
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
  src/quest.cpp
  src/race.cpp
  src/random.cpp
  src/random_event.cpp
  src/set_item_info.cpp
  src/set_option.cpp
  src/shop.cpp
  src/spec.cpp
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

  src/lua_env/api_manager.cpp
  src/lua_env/event_manager.cpp
  src/lua_env/export_manager.cpp
  src/lua_env/handle_manager.cpp
  src/lua_env/lua_env.cpp
  src/lua_env/mod_manager.cpp
  src/lua_env/registry_manager.cpp

  src/lua_env/lua_api/lua_api_animation.cpp
  src/lua_env/lua_api/lua_api_chara.cpp
  src/lua_env/lua_api/lua_api.cpp
  src/lua_env/lua_api/lua_api_debug.cpp
  src/lua_env/lua_api/lua_api_fov.cpp
  src/lua_env/lua_api/lua_api_gui.cpp
  src/lua_env/lua_api/lua_api_i18n.cpp
  src/lua_env/lua_api/lua_api_input.cpp
  src/lua_env/lua_api/lua_api_item.cpp
  src/lua_env/lua_api/lua_api_magic.cpp
  src/lua_env/lua_api/lua_api_map.cpp
  src/lua_env/lua_api/lua_api_math.cpp
  src/lua_env/lua_api/lua_api_pos.cpp
  src/lua_env/lua_api/lua_api_rand.cpp
  src/lua_env/lua_api/lua_api_skill.cpp
  src/lua_env/lua_api/lua_api_trait.cpp
  src/lua_env/lua_api/lua_api_world.cpp

  src/lua_env/lua_class/lua_class_character.cpp
  src/lua_env/lua_class/lua_class.cpp
  src/lua_env/lua_class/lua_class_item.cpp
  src/lua_env/lua_class/lua_class_position.cpp

  src/pic_loader/pic_loader.cpp

  src/ui/ui_menu_book.cpp
  src/ui/ui_menu_ctrl_ally.cpp
  src/ui/ui_menu_god.cpp
  src/ui/ui_menu_item_desc.cpp
  src/ui/ui_menu_npc_tone.cpp

  src/version.cpp
  )

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# If a CMake prefix was not provided, assume dependencies are in "./deps"
if("${CMAKE_PREFIX_PATH}" STREQUAL "")
  get_filename_component(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/deps" ABSOLUTE)
  message("No dependency prefix provided, using ${CMAKE_PREFIX_PATH}")
else()
  message("Using provided dependency prefix ${CMAKE_PREFIX_PATH}")
endif()

if(ANDROID)
  set(ANDROID_TOOLCHAIN clang)
  set(ANDROID_STL c++_shared)
  set(ANDROID_ASSETS_DIRECTORIES "${CMAKE_SOURCE_DIR}/android/assets")
  set(ANDROID_CPP_FEATURES exceptions)
  set(ANDROID_PLATFORM android-21)

  string(TOLOWER ${CMAKE_BUILD_TYPE} ANDROID_BUILD_DIR)
  set(DISTRIBUTION_DIR ${CMAKE_SOURCE_DIR}/android/distribution/android/SDL2/intermediates/ndkBuild)

  set(EXTERNAL_LIB_LOCATION ${CMAKE_SOURCE_DIR}/android/external)

  SET(SNAIL_HEADLESS OFF CACHE BOOL "Snail SDL")
  add_definitions(-DSNAIL_RENDERER_SDL)

  add_library( SDL2 SHARED IMPORTED )
  add_library( SDL2_image SHARED IMPORTED )
  add_library( SDL2_ttf SHARED IMPORTED )
  add_library( SDL2_mixer SHARED IMPORTED )
  add_library( lua SHARED IMPORTED )
  add_library( snail SHARED IMPORTED )
  add_library( boost_filesystem SHARED IMPORTED )
  add_library( boost_system SHARED IMPORTED )
  add_library( boost_iostreams SHARED IMPORTED )

  set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2.so)
  set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_image.so)
  set_target_properties(SDL2_ttf PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_ttf.so)
  set_target_properties(SDL2_mixer PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_mixer.so)
  set_target_properties(lua PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/liblua.so)
  set_target_properties(snail PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libsnail.so)

  set_target_properties(boost_filesystem PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/android/app/src/main/jniLibs/${ANDROID_ABI}/libboost_filesystem.so)
  set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/android/app/src/main/jniLibs/${ANDROID_ABI}/libboost_system.so)
  set_target_properties(boost_iostreams PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/android/app/src/main/jniLibs/${ANDROID_ABI}/libboost_iostreams.so)

  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2/include)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_image)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_ttf)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_mixer)
  include_directories(${EXTERNAL_LIB_LOCATION}/lua/src)
  include_directories(${EXTERNAL_LIB_LOCATION}/snail)
  include_directories(${EXTERNAL_LIB_LOCATION}/boost/include)
  link_directories(${EXTERNAL_LIB_LOCATION}/boost/libs/llvm/armeabi-v7a)

  add_library( ${PROJECT_NAME} SHARED ${CORE_SOURCES} src/main.cpp )

  target_link_libraries( ${PROJECT_NAME} android log SDL2 SDL2_image SDL2_ttf SDL2_mixer lua boost_filesystem boost_system boost_iostreams snail )
else()
  # Options
  option(WITH_TESTS "Build test executable (TESTS or BENCH)" "NONE")

  if((WITH_TESTS STREQUAL "TESTS") OR (WITH_TESTS STREQUAL "BENCH"))
    SET(SNAIL_HEADLESS ON CACHE BOOL "Snail headless")
    add_definitions(-DSNAIL_RENDERER_HEADLESS)
  else()
    SET(SNAIL_HEADLESS OFF CACHE BOOL "Snail SDL")
    add_definitions(-DSNAIL_RENDERER_SDL)
  endif()

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
      src/tests/spec.cpp
      src/tests/lua_api.cpp
      src/tests/lua_callbacks.cpp
      src/tests/lua_events.cpp
      src/tests/lua_exports.cpp
      src/tests/lua_handles.cpp
      src/tests/lua_mods.cpp
      src/tests/lua_registry.cpp
      src/tests/lua_registry_character.cpp
      src/tests/lua_registry_item.cpp
      src/tests/lua_serialization.cpp
      src/tests/elonacore.cpp
      src/tests/item.cpp
      src/tests/i18n.cpp
      src/tests/i18n_builtins.cpp
      src/tests/i18n_regressions.cpp
      src/tests/serialization.cpp
      ${CORE_SOURCES}
      )

    add_executable(${PROJECT_NAME} ${TEST_SOURCES})
    target_link_libraries(${PROJECT_NAME} Catch)
  elseif(WITH_TESTS STREQUAL "BENCH")
    add_subdirectory(src/thirdparty/hayai)

    # Benchmark sources
    set(BENCH_SOURCES
      src/bench/ai.cpp
      src/bench/generate.cpp
      src/bench/i18n.cpp
      src/bench/lion.cpp
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
    if(WITH_TESTS STREQUAL "BENCH")
      set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
    else()
      set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    endif()
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

  # Warning suppressions
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Force GCC to output warnings about undefined symbols
    string(APPEND CMAKE_CXX_FLAGS " -Wl,--no-undefined")
    # Disable deprecated declarations, because it causes warnings with boost_locale's use of auto_ptr
    string(APPEND CMAKE_CXX_FLAGS " -Wno-deprecated-declarations")
  elseif(MSVC)
    # Disable warnings about hiding of global/local declarations
    string(APPEND CMAKE_CXX_FLAGS " /wd4459 /wd4456")
    # Disable warnings about Boost versions.
    add_definitions(-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
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
endif()


# Kludgy function to work around the lack of directory support in copy_if_different
function(copy_nonexisting src rel final_dir final)
  if(ANDROID)
    # Asset directory is wiped on each rebuild anyway.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${rel}"
      "${final_dir}/${final}")
  else()
    file(GLOB_RECURSE allfiles RELATIVE "${rel}" "${src}/*")

    foreach( each_file ${allfiles} )
      set(destinationfile "${final_dir}/${final}/${each_file}")
      set(sourcefile "${rel}/${each_file}")
      add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        -Ddestinationfile=${destinationfile}
        -Dsourcefile=${sourcefile}
        -P ${CMAKE_MODULE_PATH}/copy_nonexisting.cmake)
    endforeach(each_file)
  endif()
endfunction()

if(ANDROID)
  set(ASSET_DIR "${CMAKE_SOURCE_DIR}/android/app/src/main/assets")
  file(REMOVE_RECURSE ${ASSET_DIR})
  file(MAKE_DIRECTORY ${ASSET_DIR})
  copy_nonexisting("runtime" "${CMAKE_SOURCE_DIR}/runtime" ${ASSET_DIR} "runtime")

  # Remove default config, in order to use Android-specific defaults.
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove "${ASSET_DIR}/runtime/config.hcl")
else()
  set(ASSET_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  copy_nonexisting("runtime" "${CMAKE_SOURCE_DIR}/runtime" ${ASSET_DIR} ".")
endif()

# Copy assets from Elona 1.22 if they are present
if (NOT ANDROID OR ANDROID_BUNDLE_ASSETS)
    if(EXISTS "${CMAKE_PREFIX_PATH}/elona")
    copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/graphic" "${CMAKE_PREFIX_PATH}/elona/graphic" ${ASSET_DIR} "graphic")
    copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/map" "${CMAKE_PREFIX_PATH}/elona/map" ${ASSET_DIR} "map")
    copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/original" "${CMAKE_PREFIX_PATH}/elona/original" ${ASSET_DIR} "original")
    copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/sound" "${CMAKE_PREFIX_PATH}/elona/sound" ${ASSET_DIR} "sound")
    copy_nonexisting("${CMAKE_PREFIX_PATH}/elona/user" "${CMAKE_PREFIX_PATH}/elona/user" ${ASSET_DIR} "user")
    message("Elona 1.22 distribution found.")
    else()
    message(WARNING "Elona 1.22 distribution not found at ${CMAKE_PREFIX_PATH}/elona. The game cannot be run without assets. Please manually copy the 'graphic', 'map', 'original', 'sound' and 'user' directories from Elona 1.22 to the ${PROJECT_NAME} output path after building.")
    endif()
endif()

if(NOT ANDROID)
  if((WITH_TESTS STREQUAL "TESTS") OR (WITH_TESTS STREQUAL "BENCH"))
    copy_nonexisting("${CMAKE_CURRENT_SOURCE_DIR}/src/tests/data" "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/data" ${ASSET_DIR} "tests/data")
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
endif()
