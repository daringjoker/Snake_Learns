cmake_minimum_required(VERSION 3.12)
project(dlibprac)

set(CMAKE_CXX_STANDARD 14)

add_executable(snake  main.cpp snake.cpp snake.h food.cpp food.h paras.h snakeai.cpp snakeai.h)

target_link_libraries(snake SDL2 SDL2main)
