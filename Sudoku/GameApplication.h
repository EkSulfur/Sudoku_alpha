#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <string>
#include "GameComponentsFactory.h"
#include "PuzzleLoader.h"

class GameApplication {
public:
    GameApplication(GameComponentsFactory* factory, const std::string& format);
    ~GameApplication();

    void startGame();

private:
    GameComponentsFactory* factory;
    IOInterface* io;
    PuzzleLoader* puzzleLoader;
    Sudoku* game;
    SudokuController* controller;
};

#endif // GAMEAPPLICATION_H
