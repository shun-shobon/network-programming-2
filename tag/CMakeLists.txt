cmake_minimum_required(VERSION 3.1)
project(tag LANGUAGES C)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tag-server server.c session.c)
target_link_libraries(tag-server mylib ${CURSES_LIBRARIES})
add_executable(tag-client client.c session.c)
target_link_libraries(tag-client mylib ${CURSES_LIBRARIES})
