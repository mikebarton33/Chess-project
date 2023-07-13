cmake_minimum_required(VERSION 3.8)
project(BAR0692_chess)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

add_compile_options(-Wall -Wextra -pedantic)

add_executable(BAR0692_chess main.cpp Board.cpp Figure.cpp Position.cpp Game.cpp Game.h)

add_executable(tests tests.cpp Board.cpp Figure.cpp Position.cpp)
