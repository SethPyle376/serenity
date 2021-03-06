set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required (VERSION 2.6)
project (Application)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -ldl")
include_directories(include)
include_directories(include/Engine/renderer)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/sdl/include")

if (UNIX)
find_package(SDL2 REQUIRED)
endif (UNIX)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB MAINSOURCES src/*.cpp)
file(GLOB SUBSOURCES src/*/*/*.cpp)
file(GLOB SOURCE src/*/*/*.c)

add_executable(Application ${SOURCE} ${MAINSOURCES} ${SUBSOURCES})

if (UNIX)
target_link_libraries(Application ${CMAKE_DL_LIBS})
endif (UNIX)

if (WIN32)
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/sdl/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/sdl/lib/x64/SDL2main.lib")
endif (WIN32)

target_link_libraries(Application ${SDL2_LIBRARIES})

