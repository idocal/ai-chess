CC = gcc
COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors

OUT_DIR = $(PWD)/bin
EXEC = $(OUT_DIR)/chessprog
GUI_DIR = $(PWD)/gui

VPATH := $(GUI_DIR)

CONSOLE_OBJS = main.o CommandParsing.o GameAux.o GameMoves.o GameRepresentation.o \
GameStates.o MatchManagement.o Matrix.o MinMaxNode.o MinMaxTree.o MovesStack.o \
PieceRules.o Scoring.o XMLLoadParser.o XMLSaveParser.o mainConsole.o

GUI_OBJS = Widget.o GenericWindow.o WindowNode.o WindowsStack.o WelcomeWindow.o \
SettingsWindow.o LoadGamesWindow.o DifficultyWindow.o ColorWindow.o PiecesWidget.o \
GameAuxGUI.o GameWindow.o GuiManager.o mainGUI.o

SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main


all: $(EXEC)
	mv *.o $(OUT_DIR)
$(EXEC): $(CONSOLE_OBJS) $(GUI_OBJS)
	$(CC) $(COMP_FLAG) $(SDL_LIB) -o $@ $(CONSOLE_OBJS) $(GUI_OBJS)




main.o: mainConsole.h mainGUI.h
	$(CC) $(COMP_FLAG) -c mainConsole.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c mainGUI.c

mainConsole.o: mainConsole.h MatchManagement.h GameAux.h
	$(CC) $(COMP_FLAG) -c $*.c

mainGUI.o: mainGUI.h MatchManagement.h WelcomeWindow.h GuiManager.h
	$(CC) $(COMP_FLAG) -c MatchManagement.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/WelcomeWindow.c $(GUI_DIR)/GuiManager.c mainGUI.c

GuiManager.o: GuiManager.h WelcomeWindow.h SettingsWindow.h DifficultyWindow.h ColorWindow.h GameWindow.h LoadGameWindow.h WindowsStack.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/$*.c

GameWindow.o: GameWindow.h GameAuxGUI.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/$*.c $(shell pkg-config --cflags --libs sdl2)

GameAuxGUI.o: GameAuxGUI.h PiecesWidget.h Widget.h GameMoves.h GameAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/GameAuxGUI.c $(GUI_DIR)/PiecesWidget.c $(GUI_DIR)/Widget.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c GameMoves.c GameAux.c

ColorWindow.o: ColorWindow.h GenericWindow.h MatchManagement.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/ColorWindow.c $(GUI_DIR)/GenericWindow.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c MatchManagement.c

DifficultyWindow.o: DifficultyWindow.h GenericWindow.h MatchManagement.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $(GUI_DIR)/DifficultyWindow.c $(GUI_DIR)/GenericWindow.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c MatchManagement.c

LoadGamesWindow.o: LoadGamesWindow.h GenericWindow.h MatchManagement.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/LoadGamesWindow.c $(GUI_DIR)/GenericWindow.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c MatchManagement.c

SettingsWindow.o: SettingsWindow.h GenericWindow.h MatchManagement.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/SettingsWindow.c $(GUI_DIR)/GenericWindow.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c MatchManagement.c

WelcomeWindow.o: WelcomeWindow.h GenericWindow.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/$*.c $(shell pkg-config --cflags --libs sdl2)

WindowsStack.o: WindowsStack.h WindowNode.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/$*.c $(shell pkg-config --cflags --libs sdl2)

WindowNode.o: WindowNode.h GenericWindow.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/$*.c $(shell pkg-config --cflags --libs sdl2)

PiecesWidget.o: PiecesWidget.h GenericWindow.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/$*.c $(shell pkg-config --cflags --libs sdl2)

GenericWindow.o: GenericWindow.h GameAux.h Widget.h XMLLoadParser.h XMLSaveParser.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/GenericWindow.c $(GUI_DIR)/Widget.c $(shell pkg-config --cflags --libs sdl2)
	$(CC) $(COMP_FLAG) -c GameAux.c XMLLoadParser.c XMLSaveParser.c

Widget.o: Widget.h config.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/Widget.c $(shell pkg-config --cflags --libs sdl2)

GameAux.o: GameAux.h MatchManagement.h MovesStack.h CommandParsing.h PieceRules.h GameStates.h XMLLoadParser.h XMLSaveParser.h MinMaxTree.h
	$(CC) $(COMP_FLAG) -c $*.c

MinMaxTree.o: MinMaxTree.h MinMaxNode.h Scoring.h PieceRules.h GameStates.h
	$(CC) $(COMP_FLAG) -c $*.c

MinMaxNode.o: MinMaxNode.h GameMoves.h
	$(CC) $(COMP_FLAG) -c $*.c

XMLLoadParser.o: XMLLoadParser.h MatchManagement.h
	$(CC) $(COMP_FLAG) -c $*.c

XMLSaveParser.o: XMLSaveParser.h MatchManagement.h
	$(CC) $(COMP_FLAG) -c $*.c

Scoring.o: Scoring.h PieceRules.h
	$(CC) $(COMP_FLAG) -c $*.c

GameStates.o: GameStates.h GameMoves.h PieceRules.h
	$(CC) $(COMP_FLAG) -c $*.c

PieceRules.o: PieceRules.h GameMoves.h
	$(CC) $(COMP_FLAG) -c $*.c

MovesStack.o: MovesStack.h GameMoves.h
	$(CC) $(COMP_FLAG) -c $*.c

MatchManagement.o: MatchManagement.h GameMoves.h
	$(CC) $(COMP_FLAG) -c $*.c

CommandParsing.o: CommandParsing.h GameMoves.h
	$(CC) $(COMP_FLAG) -c $*.c

GameMoves.o: GameMoves.h GameRepresentation.h
	$(CC) $(COMP_FLAG) -c $*.c

GameRepresentation.o: GameRepresentation.h Matrix.h
	$(CC) $(COMP_FLAG) -c $*.c

Matrix.o: Matrix.h
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OUT_DIR)/*.o $(EXEC)

