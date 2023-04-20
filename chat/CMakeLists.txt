cmake_minimum_required(VERSION 3.1)
project(chat LANGUAGES C)

add_executable(chat-server server.c)
add_executable(chat-client client.c)
