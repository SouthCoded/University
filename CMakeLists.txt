cmake_minimum_required(VERSION 2.8.7)

project(GeneLZW)
include(CTest)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "Setting build type to 'Debug' as none was specified.")
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
   # Set the possible values of build type for cmake-gui
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(ASAN FALSE CACHE BOOL "Compile with ASAN on")

set(BASE_FLAGS "-g -std=c++11 -pedantic-errors -Winit-self -Woverloaded-virtual -Wuninitialized -Wall -Wextra -fno-exceptions")
set(BASE_C_FLAGS "-g -std=c11 -pedantic-errors -Winit-self -Wuninitialized -Wall -Wextra")
set(BASE_LD_FLAGS "")
if (ASAN)
  set(BASE_FLAGS "${BASE_FLAGS} -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")
  set(BASE_C_FLAGS "${BASE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")
  set(BASE_LD_FLAGS "${BASE_LD_FLAGS} -fsanitize=address")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${BASE_FLAGS} -O0 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${BASE_FLAGS} -O3 -march=native -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${BASE_C_FLAGS} -O0 -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${BASE_C_FLAGS} -O3 -march=native -DNDEBUG")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} ${BASE_LD_FLAGS}")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} ${BASE_LD_FLAGS}")

SET(OLD_BUILD_TESTING ${BUILD_TESTING})
SET(BUILD_TESTING False)
add_subdirectory(external/gflags)
SET(BUILD_TESTING ${OLD_BUILD_TESTING})

configure_file(src/run_tests.py ${CMAKE_BINARY_DIR} COPYONLY)

################################
# Encode/decode library
################################
add_library(gene_encode STATIC src/comp0019lib.c src/comp0019.c src/decomp0019.c)

add_executable(encode src/encode.c)
target_link_libraries(encode gene_encode)

add_executable(decode src/decode.c)
target_link_libraries(decode gene_encode)

add_executable(lzw_test src/lzw_test.cc)
target_link_libraries(lzw_test gflags gene_encode)

add_custom_target(test-all WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND python ./run_tests.py
  DEPENDS gene_encode encode decode lzw_test)
