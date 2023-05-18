cmake_minimum_required(VERSION 3.1)
project(mtalk LANGUAGES C)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(mtalk-server server.c session.c sessionman.c)
target_link_libraries(mtalk-server mylib ${CURSES_LIBRARIES})
add_executable(mtalk-client client.c session.c sessionman.c)
target_link_libraries(mtalk-client mylib ${CURSES_LIBRARIES})
