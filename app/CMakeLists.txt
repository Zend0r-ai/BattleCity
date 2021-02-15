cmake_minimum_required(VERSION 3.17)

include_directories(inc)

# compile

include_directories(../Framework/inc)

add_subdirectory(src)

add_executable(BattleCity main.cpp)

target_link_libraries(BattleCity PRIVATE src SDL2Test)
