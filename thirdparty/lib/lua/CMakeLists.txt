project ( lua C )
cmake_minimum_required ( VERSION 2.8 )

find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "Git not Found")
endif()

include_directories ( lua lua/ )
set ( SRC_CORE
  lua/lapi.c
  lua/lcode.c
  lua/lctype.c
  lua/ldebug.c
  lua/ldo.c
  lua/ldump.c
  lua/lfunc.c
  lua/lgc.c
  lua/llex.c
  lua/lmem.c
  lua/lobject.c
  lua/lopcodes.c
  lua/lparser.c
  lua/lstate.c
  lua/lstring.c
  lua/ltable.c
  lua/ltm.c
  lua/lundump.c
  lua/lvm.c
  lua/lzio.c
  lua/lwstring.c )
set ( SRC_LIB
  lua/lauxlib.c
  lua/lbaselib.c
  # lua/lbitlib.c
  lua/lcorolib.c
  lua/ldblib.c
  lua/liolib.c
  lua/lmathlib.c
  lua/loslib.c
  lua/lstrlib.c
  lua/ltablib.c
  lua/lutf8lib.c
  lua/loadlib.c
  lua/linit.c )

add_library ( liblua53 STATIC ${SRC_CORE} ${SRC_LIB} )
target_include_directories( liblua53 INTERFACE lua/ )
set_target_properties ( liblua53 PROPERTIES OUTPUT_NAME lua53 )

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

#add_library ( libluadll SHARED ${SRC_CORE} ${SRC_LIB} )
#target_compile_definitions ( libluadll PRIVATE _CRT_SECURE_NO_WARNINGS LUA_BUILD_AS_DLL )
#target_include_directories( libluadll INTERFACE lua/ )
#set_target_properties ( libluadll PROPERTIES OUTPUT_NAME lua53 )
