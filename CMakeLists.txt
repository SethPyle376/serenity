cmake_minimum_required (VERSION 2.6)
project (Application)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ldl")
include_directories(include)

file(GLOB MAINSOURCES src/*.cpp)
file(GLOB SOURCE src/*.c)

add_executable(Application ${SOURCE} ${MAINSOURCES})

if (UNIX)
target_link_libraries(Application ${CMAKE_DL_LIBS})
endif (UNIX)
