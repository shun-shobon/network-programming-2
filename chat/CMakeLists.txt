cmake_minimum_required(VERSION 3.1)
project(chat LANGUAGES C)

add_executable(server server.c)
add_executable(client client.c)
