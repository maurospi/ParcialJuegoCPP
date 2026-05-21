cmake_minimum_required(VERSION 3.10)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(DungeonGame ${SOURCES})

if(WIN32)
    target_link_libraries(DungeonGame winmm)
endif()

set_target_properties(DungeonGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
