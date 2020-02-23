# CMake v3.2 or later
cmake_minimum_required(VERSION 3.2)


# Project
project(Elona_foobar VERSION 0.6.0)



# Platform detection
set(LINUX FALSE)
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(LINUX TRUE)
endif()


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
  OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "Commit hash: ${PROJECT_VERSION_REVISION}")


# Get date and time
string(TIMESTAMP PROJECT_VERSION_TIMESTAMP UTC)

# Get platform
set(PROJECT_VERSION_PLATFORM "${CMAKE_SYSTEM}")

# Versioning file
configure_file("${PROJECT_SOURCE_DIR}/src/version.cpp.in" "${PROJECT_SOURCE_DIR}/src/version.cpp")



# C++17 or later
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# If a CMake prefix was not provided, assume dependencies are in "./deps"
if("${CMAKE_PREFIX_PATH}" STREQUAL "")
  get_filename_component(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/deps" ABSOLUTE)
  message("No dependency prefix provided, using ${CMAKE_PREFIX_PATH}")
else()
  message("Using provided dependency prefix ${CMAKE_PREFIX_PATH}")
endif()

# Options
set(ELONA_BUILD_TARGET "GAME" CACHE STRING "Build executable type (GAME, LAUNCHER, TESTS, or BENCH)")

if((ELONA_BUILD_TARGET STREQUAL "TESTS") OR (ELONA_BUILD_TARGET STREQUAL "BENCH"))
  set(SNAIL_BACKEND "HEADLESS")
  set(SPIDER_BACKEND "HEADLESS")
else()
  set(SNAIL_BACKEND "SDL")
  set(SPIDER_BACKEND "BOOST_ASIO")
endif()

# Executable
if(ELONA_BUILD_TARGET STREQUAL "TESTS")
  set (CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/catch2})
  add_library(Catch INTERFACE)
  target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

  # Test sources
  set(TEST_SOURCES
    src/tests/tests.cpp
    src/tests/util.cpp
    src/tests/config.cpp
    src/tests/config_def.cpp
    src/tests/filesystem.cpp
    src/tests/lua_api.cpp
    src/tests/lua_callbacks.cpp
    src/tests/lua_events.cpp
    src/tests/lua_exports.cpp
    src/tests/lua_handles.cpp
    src/tests/lua_mod_resolve.cpp
    src/tests/lua_mods.cpp
    src/tests/lua_data.cpp
    src/tests/lua_data_character.cpp
    src/tests/lua_data_item.cpp
    src/tests/lua_serialization.cpp
    src/tests/elonacore.cpp
    src/tests/item.cpp
    src/tests/i18n.cpp
    src/tests/i18n_builtins.cpp
    src/tests/i18n_regressions.cpp
    src/tests/keybind_deserializer.cpp
    src/tests/keybind_key_names.cpp
    src/tests/keybind_manager.cpp
    src/tests/keybind_serializer.cpp
    src/tests/semver.cpp
    src/tests/serialization.cpp
    )

  add_executable(${PROJECT_NAME} src/version.cpp ${TEST_SOURCES})
  target_link_libraries(${PROJECT_NAME} Catch)
elseif(ELONA_BUILD_TARGET STREQUAL "BENCH")
  add_subdirectory(src/thirdparty/hayai)

  # Benchmark sources
  set(BENCH_SOURCES
    src/bench/ai.cpp
    src/bench/generate.cpp
    src/bench/i18n.cpp
    src/bench/lua_callbacks.cpp
    src/bench/magic.cpp
    src/bench/serialization.cpp
    src/bench/util.cpp
    )

  add_executable(${PROJECT_NAME} src/version.cpp ${BENCH_SOURCES})
  target_link_libraries(${PROJECT_NAME} hayai_main ${LIB_TIMING})
elseif(ELONA_BUILD_TARGET STREQUAL "GAME")
  if(WIN32)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/icon_windows.rc")
  endif()
  add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/version.cpp ${RESOURCES})
elseif(ELONA_BUILD_TARGET STREQUAL "LAUNCHER")
  if(WIN32)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/icon_windows.rc")
  endif()
  add_executable(${PROJECT_NAME} WIN32 src/launcher_main.cpp src/version.cpp ${RESOURCES})
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Elona foobar Launcher")
else()
  message(FATAL_ERROR "Unknown build mode: ${ELONA_BUILD_TARGET}")
endif()

if (NOT DEFINED ZLIB_INCLUDE_DIR OR NOT DEFINED ZLIB_LIBRARIES)
  find_package(ZLIB REQUIRED)
endif()
include_directories(${ZLIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})

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
find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# NOTE: The prebuilt version of lua in the windows dependency
# submodule is patched with wstring support.
if(WIN32)
  # FindLua does not support distinguishing debug/release builds.
  set(LUA_INCLUDE_DIR ${CMAKE_PREFIX_PATH}/include)
  set(LUA_LIBRARIES debug ${CMAKE_PREFIX_PATH}/lib/lua53d.lib optimized ${CMAKE_PREFIX_PATH}/lib/lua53.lib)
else()
  if(NOT DEFINED LUA_INCLUDE_DIR OR NOT DEFINED LUA_LIBRARIES)
    find_package(Lua REQUIRED)
  endif()
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

if(LINUX)
  target_link_libraries(${PROJECT_NAME} dl)
endif()

if(WIN32)
else()
  target_link_libraries(${PROJECT_NAME} pthread)
endif()

if(NOT DEFINED OPENSSL_INCLUDE_DIR OR NOT DEFINED OPENSSL_LIBRARIES)
  find_package(OpenSSL REQUIRED)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

set(GENERAL_OPTIONS)
set(DEBUG_OPTIONS)
set(RELEASE_OPTIONS)
set(LINKER_OPTIONS)
set(EXTRA_DEFINES)
set(DISABLED_WARNINGS)
set(WARNINGS_AS_ERRORS)

list(APPEND EXTRA_DEFINES
  "BOOST_ALLOW_DEPRECATED_HEADERS" # https://github.com/boostorg/random/issues/49

  # https://www.boost.org/doc/libs/1_69_0/doc/html/boost_asio/using.html
  # > With MSVC or Borland C++ you may want to add -DBOOST_DATE_TIME_NO_LIB and
  # > -DBOOST_REGEX_NO_LIB to your project settings to disable autolinking of
  # > the Boost.Date_Time and Boost.Regex libraries respectively.
  "BOOST_DATE_TIME_NO_LIB"
  "BOOST_REGEX_NO_LIB"
  )

if(MSVC)
  list(APPEND EXTRA_DEFINES "_UNICODE")
  list(APPEND GENERAL_OPTIONS
    "W4"
    "source-charset:utf-8"
    "MT"
    "EHsc"
    )
  list(APPEND DEBUG_OPTIONS
    "MP8"
    "MTd"
    "ZI"
    "Od"
    "bigobj"
    )
  list(APPEND RELEASE_OPTIONS
    "MT"
    )
  list(APPEND DISABLED_WARNINGS
    "4244" # 'conversion' conversion from 'type1' to 'type2', possible loss of data
    "4267" # 'var' : conversion from 'size_t' to 'type', possible loss of data
    "4456" # declaration of 'identifier' hides previous local declaration
    "4459" # declaration of 'identifier' hides global declaration
    "4996" # Call to 'std::equal' with parameters that may be unsafe
    )
  list(APPEND EXTRA_DEFINES
    "BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE"
    )

  foreach(opt ${DISABLED_WARNINGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd${opt}")
  endforeach()

  foreach(opt ${GENERAL_OPTIONS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /${opt}")
  endforeach()

  foreach(opt ${DEBUG_OPTIONS})
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /${opt}")
  endforeach()

  foreach(opt ${RELEASE_OPTIONS})
    foreach(flag_var CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      set(${flag_var} "${${flag_var}} /${opt}")
    endforeach()
  endforeach()
else() # GCC or Clang
  list(APPEND GENERAL_OPTIONS
    "Wall"
    "Wextra"
    )
  list(APPEND DEBUG_OPTIONS
    "g"
    "O0"
    "DDEBUG"
    "DSOL_CHECK_ARGUMENTS"
    )
  if(ELONA_BUILD_TARGET STREQUAL "BENCH")
    list(APPEND GENERAL_OPTIONS "g1")
  endif()
  list(APPEND DISABLED_WARNINGS
    "deprecated-declarations"
    )
  list(APPEND WARNINGS_AS_ERRORS
    "return-type"
    )

  # Speed up linking on Linux by using split DWARF
  if (LINUX)
    list(APPEND GENERAL_OPTIONS "gsplit-dwarf")
  endif ()

  # Use gold linker or lld if available
  set(LINKER)

  option(USE_GOLD_LINKER "Link with GNU gold" ON)
  if (USE_GOLD_LINKER)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
    if(LD_VERSION MATCHES "GNU gold")
      set(LINKER "gold")
    endif()
  endif()

  option(USE_LLD_LINKER "Link with lld" ON)
  if (USE_LLD_LINKER)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
    if(LD_VERSION MATCHES "LLD")
      set(LINKER "lld")
    endif()
  endif()

  if (LINKER)
    list(APPEND LINKER_OPTIONS "fuse-ld=${LINKER}")
    message(STATUS "Using linker: ${LINKER}")
  else()
    message(STATUS "Using system linker.")
  endif()

  foreach(opt ${DISABLED_WARNINGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-${opt}")
  endforeach()

  foreach(opt ${WARNINGS_AS_ERRORS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=${opt}")
  endforeach()

  foreach(opt ${GENERAL_OPTIONS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -${opt}")
  endforeach()

  foreach(opt ${DEBUG_OPTIONS})
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -${opt}")
  endforeach()

  foreach(opt ${RELEASE_OPTIONS})
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -${opt}")
  endforeach()

  foreach(opt ${LINKER_OPTIONS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -${opt}")
  endforeach()
endif()

foreach(opt ${EXTRA_DEFINES})
  add_definitions("-D${opt}")
endforeach()

# My libraries: util
add_subdirectory(src/util)
target_link_libraries(${PROJECT_NAME} util)

# My libraries: snail
add_subdirectory(src/snail)
target_link_libraries(${PROJECT_NAME} ${SNAIL_LIBRARY})

# My libraries: spider
add_subdirectory(src/spider)
target_link_libraries(${PROJECT_NAME} ${SPIDER_LIBRARY})

add_subdirectory(src/thirdparty/uri)
target_link_libraries(${PROJECT_NAME} ${NETWORK_URI_LIBRARY})

# My libraries: elona
add_subdirectory(src/elona)
target_link_libraries(${PROJECT_NAME} elona ${SNAIL_LIBRARY} ${SPIDER_LIBRARY} util ${NETWORK_URI_LIBRARY})

if((ELONA_BUILD_TARGET STREQUAL "GAME") OR (ELONA_BUILD_TARGET STREQUAL "LAUNCHER"))
  add_subdirectory(src/thirdparty/nfd)
  target_link_libraries(${PROJECT_NAME} nfd)
endif()

add_subdirectory(src/thirdparty/minizip)
target_link_libraries(${PROJECT_NAME} minizip)


# Install target
if(APPLE)
  set(ELONA_INSTALL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/bundled")
  set(ELONA_INSTALL_APP "${ELONA_INSTALL_PATH}/${PROJECT_NAME}.app")

  install(
    TARGETS ${PROJECT_NAME}
    BUNDLE
    DESTINATION ${ELONA_INSTALL_PATH}
    COMPONENT Runtime
  )

  install(CODE "
    include(BundleUtilities)

    fixup_bundle(\"${ELONA_INSTALL_APP}\" \"\" \"\")
    " COMPONENT Runtime)
endif()


function(copy_nonexisting source target)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -Dsourcefile=${source}
    -Ddestinationfile=${target}
    -P ${CMAKE_MODULE_PATH}/copy_nonexisting.cmake)
endfunction()

function(copy_dir source target)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${source}
    ${target})
endfunction()

function(copy_mod_dirs mod_root_dir target)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -Dmod_root_dir=${mod_root_dir}
    -Dtarget=${target}
    -P ${CMAKE_MODULE_PATH}/copy_mod_dirs.cmake)
endfunction()

function(copy_file source target)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${source}
    ${target})
endfunction()

function(remove_dir dir)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory
    ${dir})
endfunction()

set(ASSET_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set(RUNTIME_DIR "${ASSET_DIR}")

# Copy and overwrite runtime folders/files (except config.json)
copy_dir(${CMAKE_SOURCE_DIR}/runtime/data/ "${RUNTIME_DIR}/data/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/font/ "${RUNTIME_DIR}/font/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/graphic/ "${RUNTIME_DIR}/graphic/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/locale/ "${RUNTIME_DIR}/locale/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/map/ "${RUNTIME_DIR}/map/")
copy_mod_dirs(${CMAKE_SOURCE_DIR}/runtime/mod/ "${RUNTIME_DIR}/mod/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/profile/ "${RUNTIME_DIR}/profile/")

# Copy assets from Elona 1.22 if they are present.
if(EXISTS "${CMAKE_PREFIX_PATH}/elona")
  copy_dir("${CMAKE_PREFIX_PATH}/elona/graphic" "${ASSET_DIR}/graphic")
  copy_dir("${CMAKE_PREFIX_PATH}/elona/sound" "${ASSET_DIR}/sound")
  message("Elona 1.22 distribution found.")
else()
  message(WARNING "Elona 1.22 distribution not found at ${CMAKE_PREFIX_PATH}/elona. The game cannot be run without assets. Please manually copy the 'graphic' and 'sound' directories from Elona 1.22 to the ${PROJECT_NAME} output path after building.")
endif()

if((ELONA_BUILD_TARGET STREQUAL "TESTS") OR (ELONA_BUILD_TARGET STREQUAL "BENCH"))
  copy_dir(${CMAKE_SOURCE_DIR}/src/tests/data "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/data")
endif()

if(ELONA_BUILD_TARGET STREQUAL "TESTS")
  copy_dir(${CMAKE_SOURCE_DIR}/src/tests/lua "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/lua")
endif()

remove_dir("$<TARGET_FILE_DIR:${PROJECT_NAME}>/profile/testing")
