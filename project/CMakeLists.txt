cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES mainConsole.c GameRepresentation.h GameRepresentation.c MovesStack.h MovesStack.c MatchManagement.h MatchManagement.c CommandParsing.h CommandParsing.c PieceRules.c PieceRules.h XMLSaveParser.h XMLSaveParser.c Matrix.c Matrix.h GameAux.c GameAux.h XMLLoadParser.h XMLLoadParser.c GameStates.c GameStates.h GameMoves.c GameMoves.h MinMaxNode.c MinMaxNode.h Scoring.c Scoring.h MinMaxTree.c MinMaxTree.h gui/GenericWindow.c gui/GenericWindow.h gui/WelcomeWindow.c gui/WelcomeWindow.h gui/Widget.c gui/Widget.h mainGUI.c gui/GuiManager.c gui/GuiManager.h gui/SettingsWindow.c gui/SettingsWindow.h gui/WindowNode.c gui/WindowNode.h gui/WindowsStack.c gui/WindowsStack.h gui/DifficultyWindow.c gui/DifficultyWindow.h gui/ColorWindow.c gui/ColorWindow.h gui/GameWindow.c gui/GameWindow.h gui/PiecesWidget.c gui/PiecesWidget.h gui/GameAuxGUI.c gui/GameAuxGUI.h gui/config.h gui/LoadGamesWindow.c gui/LoadGamesWindow.h)

add_executable(project ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
