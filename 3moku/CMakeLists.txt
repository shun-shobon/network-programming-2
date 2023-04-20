cmake_minimum_required(VERSION 3.1)
project(3moku LANGUAGES C)

add_executable(3moku-server server.c goban.c)
target_link_libraries(3moku-server mylib)
add_executable(3moku-client client.c goban.c)
target_link_libraries(3moku-client mylib)
