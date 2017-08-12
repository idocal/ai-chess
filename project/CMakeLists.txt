cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c GameRepresenation.h GameRepresenation.c MovesStack.h MovesStack.c MatchManagement.h MatchManagement.c CommandParsing.h CommandParsing.c PieceRules.c PieceRules.h)
add_executable(project ${SOURCE_FILES})