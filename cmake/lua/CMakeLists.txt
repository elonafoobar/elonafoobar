project(lua C)
cmake_minimum_required(VERSION 2.8)

include_directories (lua src/)
set(SRC_CORE
  src/lapi.c
  src/lcode.c
  src/lctype.c
  src/ldebug.c
  src/ldo.c
  src/ldump.c
  src/lfunc.c
  src/lgc.c
  src/llex.c
  src/lmem.c
  src/lobject.c
  src/lopcodes.c
  src/lparser.c
  src/lstate.c
  src/lstring.c
  src/ltable.c
  src/ltm.c
  src/lundump.c
  src/lvm.c
  src/lzio.c
  src/lwstring.c
  )
set(SRC_LIB
  src/lauxlib.c
  src/lbaselib.c
  # src/lbitlib.c
  src/lcorolib.c
  src/ldblib.c
  src/liolib.c
  src/lmathlib.c
  src/loslib.c
  src/lstrlib.c
  src/ltablib.c
  src/lutf8lib.c
  src/loadlib.c
  src/linit.c
  )

add_library(liblua53 STATIC ${SRC_CORE} ${SRC_LIB})
target_include_directories(liblua53 INTERFACE src/)
set_target_properties(liblua53 PROPERTIES OUTPUT_NAME lua53)

set(COMPILER_FLAGS
  CMAKE_CXX_FLAGS
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_C_FLAGS
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_RELEASE
  )
foreach(COMPILER_FLAG ${COMPILER_FLAGS})
  string(REPLACE "/MD" "/MT" ${COMPILER_FLAG} "${${COMPILER_FLAG}}")
endforeach()
