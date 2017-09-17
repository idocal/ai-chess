CC = gcc
COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors

OUT_DIR = $(PWD)/bin
EXEC = $(OUT_DIR)/chessprog
GUI_DIR = $(PWD)/gui

VPATH := $(GUI_DIR)

CONSOLE_OBJS = main.o CommandParsing.o GameAux.o GameMoves.o GameRepresentation.o \
GameStates.o MatchManagement.o Matrix.o MinMaxNode.o MinMaxTree.o MovesStack.o \
PieceRules.o Scoring.o XMLLoadParser.o XMLSaveParser.o

GUI_OBJS = Widget.o GenericWindow.o WindowNode.o WindowsStack.o WelcomeWindow.o \
SettingWindow.o LoadGamesWindow.o DifficultyWindow.o ColorWindow.o PiecesWidget.o \
GameAuxGUI.o GameWindow.o GuiManager.o



GUI_OBJS = GenericWindow.o WindowNode.o WindowsStack.o WelcomeWindow.o \
SettingWindow.o LoadGamesWindow.o DifficultyWindow.o ColorWindow.o PiecesWidget.o \
GameAuxGUI.o GameWindow.o GuiManager.o


all: $(EXEC)
	mv *.o $(OUT_DIR)
$(EXEC): $(CONSOLE_OBJS)
	$(CC) $(COMP_FLAG) -o $@ $(CONSOLE_OBJS)
main.o: MatchManagement.h GameAux.h
	$(CC) $(COMP_FLAG) -c $*.c




Widget.o:  Widget.h config.h
	$(CC) $(COMP_FLAG) -c $(GUI_DIR)/$*.c
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

