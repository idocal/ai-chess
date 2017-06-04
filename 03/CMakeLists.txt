cmake_minimum_required(VERSION 3.7)
project(03)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c SPFIARGame.c SPArrayList.c SPArrayListUnitTest.c SPFAIRParser.c SPFAIRParserUnitTest.c SPFAIRParser.h SPFIARGame.h unit_test_util.h SPMainAux.h SPMiniMax.h SPMiniMaxNode.h SPMiniMaxNode.c SPMiniMax.c SPMainAux.c)
add_executable(03 ${SOURCE_FILES})