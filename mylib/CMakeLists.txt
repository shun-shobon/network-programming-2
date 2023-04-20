cmake_minimum_required(VERSION 3.1)
project(mylib LANGUAGES C)

add_library(mylib STATIC setup_server.c setup_client.c chop_newilne.c)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
