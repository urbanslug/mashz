cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(mashz VERSION 0.0.1)

include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Falling back to different standard it not allowed.
set(CMAKE_CXX_EXTENSIONS OFF)  # Make sure no compiler-specific features are used.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -mcx16 -march=native -fpermissive")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mcx16  -march=native -fpermissive")

# Dev compilation flags
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O -mcx16  -march=native -g -fsanitize=address -fpermissive")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -mcx16  -march=native -g -fsanitize=address -fpermissive")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(src/common/wflign EXCLUDE_FROM_ALL)

add_subdirectory(src/common/lastz)

add_executable(mashz src/yeet/yeet_main.cpp)

target_include_directories(mashz PRIVATE
  src
  src/common/wflign/deps
  src/common/wflign/deps/wflambda
  src/common/wflign/deps/patchmap
  src/common/wflign/deps/WFA
  src/common)

target_link_libraries(mashz
  gsl
  gslcblas
  m
  pthread
  libwflign_static
  edlib
  wflambda
  wfa
  z)

install(TARGETS mashz-lastz mashz DESTINATION bin)
