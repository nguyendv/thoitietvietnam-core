cmake_minimum_required(VERSION 3.2)

project("TestCoreClient")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-c++11-extensions")

add_executable(testcoreclient      
                        src/testcoreclient.cpp
                            )
target_link_libraries(testcoreclient coreclient)
add_test(testcoreclient testcoreclient)
