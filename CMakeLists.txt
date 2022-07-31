cmake_minimum_required(VERSION 3.18)

project(ticktock VERSION 0.4.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# zlib dependency
find_package(ZLIB REQUIRED)

# pthread dependency
find_package(Threads REQUIRED)

file(GLOB_RECURSE TICKTOCK_SRC_FILES src/*.cpp)
list(REMOVE_ITEM TICKTOCK_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# ticktock library
add_library(ticktock ${TICKTOCK_SRC_FILES})
add_library(ticktock::ticktock ALIAS ticktock)
target_include_directories(ticktock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ticktock
        PUBLIC
        ZLIB::ZLIB
        Threads::Threads
        )

# tt executable
add_executable(tt ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(tt ticktock)