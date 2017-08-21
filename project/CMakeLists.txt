cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c GameRepresenation.h GameRepresenation.c MovesStack.h MovesStack.c MatchManagement.h MatchManagement.c CommandParsing.h CommandParsing.c PieceRules.c PieceRules.h XMLSaveParser.h XMLSaveParser.c Matrix.c Matrix.h GameAux.c GameAux.h XMLLoadParser.h XMLLoadParser.c GameStates.c GameStates.h GameMoves.c GameMoves.h SPSimpleMainWindow.h SPSimpleMainWindow.c SPWindow.h SPWindow.c Widget.h Widget.c SimpleButton.h SimpleButton.c SPCommon.h SPCommon.c)
add_executable(project ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
