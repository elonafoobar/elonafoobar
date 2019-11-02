# CMake v3.2 or later
cmake_minimum_required(VERSION 3.2)


# Project
project(Elona_foobar VERSION 0.5.0)

# Android version code. Increment on every distinct release.
set(PROJECT_VERSION_CODE 9)


# Options
option(ANDROID_BUNDLE_ASSETS "Bundle assets with Android distribution" OFF)
option(ANDROID_GENERATE_BUILD_FILES "Generate android/app/gradle.properties and src/{elona,snail,spider,util}/Android.mk" OFF)


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

function(generate_android_mk target)
  cmake_parse_arguments(ARGS "" "" "SOURCES" ${ARGN})
  set(ANDROID_MK_TARGET ${target})
  set(ANDROID_MK_SOURCES "LOCAL_SRC_FILES := \\\n")
  foreach(SOURCE ${ARGS_SOURCES})
    set(ANDROID_MK_SOURCES "${ANDROID_MK_SOURCES}${SOURCE} \\\n")
  endforeach()
  configure_file("${PROJECT_SOURCE_DIR}/src/${target}/Android.mk.in" "${PROJECT_SOURCE_DIR}/src/${target}/Android.mk")
endfunction()


# CMake is run last in the Android build process, so gradle.properties
# and Android.mk have to be generated beforehand.
if(ANDROID_GENERATE_BUILD_FILES)
  configure_file("${PROJECT_SOURCE_DIR}/android/gradle.properties.in" "${PROJECT_SOURCE_DIR}/android/gradle.properties")

  # Generate Android.mk
  add_subdirectory(src/util)
  set(SNAIL_BACKEND "SDL")
  add_subdirectory(src/snail)
  # TODO set(SPIDER_BACKEND "BOOST_ASIO")
  set(SPIDER_BACKEND "HEADLESS")
  add_subdirectory(src/spider)
  add_subdirectory(src/elona)

  return()
endif()


# C++14 or later
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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

  set(SNAIL_BACKEND "SDL")
  # TODO set(SPIDER_BACKEND "BOOST_ASIO")
  set(SPIDER_BACKEND "HEADLESS")

  add_library(SDL2 SHARED IMPORTED)
  add_library(SDL2_image SHARED IMPORTED)
  add_library(SDL2_ttf SHARED IMPORTED)
  add_library(SDL2_mixer SHARED IMPORTED)
  add_library(lua SHARED IMPORTED)
  add_library(util SHARED IMPORTED)
  add_library(snail SHARED IMPORTED)
  add_library(spider SHARED IMPORTED)
  add_library(elona SHARED IMPORTED)
  add_library(boost_filesystem SHARED IMPORTED)
  add_library(boost_system SHARED IMPORTED)

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
  set_target_properties(util PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libutil.so)
  set_target_properties(snail PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libsnail.so)
  set_target_properties(spider PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libspider.so)
  set_target_properties(elona PROPERTIES IMPORTED_LOCATION
    ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libelona.so)

  set_target_properties(boost_filesystem PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/android/app/src/main/jniLibs/${ANDROID_ABI}/libboost_filesystem.so)
  set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/android/app/src/main/jniLibs/${ANDROID_ABI}/libboost_system.so)

  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2/include)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_image)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_ttf)
  include_directories(${EXTERNAL_LIB_LOCATION}/SDL2_mixer)
  include_directories(${EXTERNAL_LIB_LOCATION}/lua/src)
  include_directories(${EXTERNAL_LIB_LOCATION}/util)
  include_directories(${EXTERNAL_LIB_LOCATION}/snail)
  include_directories(${EXTERNAL_LIB_LOCATION}/spider)
  include_directories(${EXTERNAL_LIB_LOCATION}/elona)
  include_directories(${EXTERNAL_LIB_LOCATION}/boost/include)
  link_directories(${EXTERNAL_LIB_LOCATION}/boost/libs/llvm/armeabi-v7a)

  add_library(${PROJECT_NAME} SHARED src/main.cpp src/version.cpp)

  target_link_libraries(${PROJECT_NAME} android log SDL2 SDL2_image SDL2_ttf SDL2_mixer lua boost_filesystem boost_system util snail spider elona)
else()
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
      src/tests/spec.cpp
      src/tests/lua_api.cpp
      src/tests/lua_callbacks.cpp
      src/tests/lua_events.cpp
      src/tests/lua_exports.cpp
      src/tests/lua_handles.cpp
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
    add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/version.cpp)
  elseif(ELONA_BUILD_TARGET STREQUAL "LAUNCHER")
    add_executable(${PROJECT_NAME} WIN32 src/launcher_main.cpp src/version.cpp)
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

  install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)

  # Create macOS .app bundle
  set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
  if(APPLE)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
  endif(APPLE)
  if(WIN32)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe")
  endif(WIN32)

  set(DIRS ${LINK_DIRECTORIES})

  install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
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

if(ANDROID)
  set(ASSET_DIR "${CMAKE_SOURCE_DIR}/android/app/src/main/assets")
  file(REMOVE_RECURSE ${ASSET_DIR})
  file(MAKE_DIRECTORY ${ASSET_DIR})
  set(RUNTIME_DIR "${ASSET_DIR}/runtime")
else()
  set(ASSET_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  set(RUNTIME_DIR "${ASSET_DIR}")
endif()

# Copy and overwrite runtime folders/files (except config.json)
copy_dir(${CMAKE_SOURCE_DIR}/runtime/data/ "${RUNTIME_DIR}/data/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/font/ "${RUNTIME_DIR}/font/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/graphic/ "${RUNTIME_DIR}/graphic/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/locale/ "${RUNTIME_DIR}/locale/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/map/ "${RUNTIME_DIR}/map/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/mod/ "${RUNTIME_DIR}/mod/")
copy_dir(${CMAKE_SOURCE_DIR}/runtime/profile/ "${RUNTIME_DIR}/profile/")

# Copy assets from Elona 1.22 if they are present.
if (NOT ANDROID OR ANDROID_BUNDLE_ASSETS)
  if(EXISTS "${CMAKE_PREFIX_PATH}/elona")
    copy_dir("${CMAKE_PREFIX_PATH}/elona/graphic" "${ASSET_DIR}/graphic")
    copy_dir("${CMAKE_PREFIX_PATH}/elona/sound" "${ASSET_DIR}/sound")
    copy_dir("${CMAKE_PREFIX_PATH}/elona/user" "${ASSET_DIR}/user")
    message("Elona 1.22 distribution found.")
  else()
    message(WARNING "Elona 1.22 distribution not found at ${CMAKE_PREFIX_PATH}/elona. The game cannot be run without assets. Please manually copy the 'graphic', 'sound' and 'user' directories from Elona 1.22 to the ${PROJECT_NAME} output path after building.")
  endif()
endif()

if(NOT ANDROID)
  if((ELONA_BUILD_TARGET STREQUAL "TESTS") OR (ELONA_BUILD_TARGET STREQUAL "BENCH"))
    copy_dir(${CMAKE_SOURCE_DIR}/src/tests/data "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/data")
  endif()

  if(ELONA_BUILD_TARGET STREQUAL "TESTS")
    copy_dir(${CMAKE_SOURCE_DIR}/src/tests/lua "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/lua")
  endif()

  remove_dir("$<TARGET_FILE_DIR:${PROJECT_NAME}>/profile/testing")
endif()
