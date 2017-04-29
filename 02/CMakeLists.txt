cmake_minimum_required(VERSION 3.7)
project(NimGame)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c main_aux.c main_aux.h sp_nim.c sp_nim.h)
add_executable(NimGame ${SOURCE_FILES})