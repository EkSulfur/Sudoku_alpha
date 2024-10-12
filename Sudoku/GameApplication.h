#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <memory>
#include "GameComponentsFactory.h"

// 应用类：封装整个游戏，使用智能指针，使得资源管理更加安全，避免了内存泄漏的风险
class GameApplication {
public:
    GameApplication(std::unique_ptr<GameComponentsFactory> factory);

    void startGame();

private:
    std::unique_ptr<GameComponentsFactory> factory;
    std::unique_ptr<IOInterface> io;
    std::unique_ptr<PuzzleLoader> puzzleLoader;
    std::unique_ptr<Sudoku> game;
    std::unique_ptr<SudokuController> controller;
};

#endif // GAMEAPPLICATION_H