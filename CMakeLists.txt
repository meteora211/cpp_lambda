cmake_minimum_required(VERSION 3.25)
project(cpp_lambda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include(FetchContent)
FetchContent_Declare(
  range-v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3
  GIT_TAG 0.12.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
)
# https://github.com/ericniebler/range-v3/issues/1689
FetchContent_GetProperties(range-v3)
if(NOT range-v3_POPULATED)
  FetchContent_Populate(range-v3)
  add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR} EXCLUDE_FROM_ALL)
  target_include_directories(range-v3 SYSTEM INTERFACE $<BUILD_INTERFACE:${range-v3_SOURCE_DIR}/include>)
endif()

include_directories(${PROJECT_SOURCE_DIR}/common)
add_subdirectory(chpt1)
add_subdirectory(chpt2)
add_subdirectory(chpt3)
add_subdirectory(chpt4)
