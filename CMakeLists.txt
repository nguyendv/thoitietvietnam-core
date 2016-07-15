cmake_minimum_required(VERSION 3.2)

project("CoreClient")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-c++11-extensions")

set (CATCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/catch)
add_library(coreclient      
                        src/coreclient.cpp
                            )

include_directories (
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_CURRENT_SOURCE_DIR}/include
                        ${CATCH_DIR}
                    )

enable_testing()
add_subdirectory(test)
