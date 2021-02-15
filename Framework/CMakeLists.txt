cmake_minimum_required(VERSION 3.17.3)

project(test)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_library(SDL2Test SHARED launch.cpp)
set_target_properties(SDL2Test PROPERTIES PUBLIC_HEADER inc/Framework.h)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})