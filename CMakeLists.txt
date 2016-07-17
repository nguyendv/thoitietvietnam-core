cmake_minimum_required(VERSION 3.2)

project("CoreClient")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-c++11-extensions")

set(THIRD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty)

set (CATCH_DIR ${THIRD_PARTY}/catch)

set (SQLITE_CPP_DIR ${THIRD_PARTY}/sqlitecpp)

file(GLOB sqlitecpp_src 
  ${SQLITE_CPP_DIR}/src/*.cpp
  ${SQLITE_CPP_DIR}/sqlite3/sqlite3.c               
)

add_library(coreclient      
  src/appstate.cpp
  ${sqlitecpp_src}
)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CATCH_DIR}
  ${SQLITE_CPP_DIR}/include
  ${SQLITE_CPP_DIR}/sqlite3
)

enable_testing()
add_subdirectory(test)
