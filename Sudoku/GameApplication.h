#ifndef GAMEAPPLICATION
#define GAMEAPPLICATION

#include "GameComponentsFactory.h"

class GameApplication {
public:
    GameApplication(GameComponentsFactory* factory);
    ~GameApplication();

    void startGame();

private:
    GameComponentsFactory* factory;
    IOInterface* io;
    PuzzleLoader* puzzleLoader;
    Sudoku* sudoku;
    SudokuController* controller;
};

#endif // !GAMEAPPLICATION
