#include "GameApplication.h"
#include "IOInterface.h"
#include "PuzzleLoader.h"
#include "Sudoku.h"
#include "SudokuController.h"

// 封装整个游戏
GameApplication::GameApplication(GameComponentsFactory* factory)
    : factory(factory), io(nullptr), puzzleLoader(nullptr), sudoku(nullptr), controller(nullptr) {
    // 使用工厂创建组件
    io = factory->createIOInterface();
    puzzleLoader = factory->createPuzzleLoader();
    sudoku = factory->createSudoku(puzzleLoader);
    controller = factory->createController(sudoku, io);
}

GameApplication::~GameApplication() {
    // 清理资源
    delete controller;
    delete sudoku;
    delete puzzleLoader;
    delete io;
    delete factory;
}

void GameApplication::startGame() {
    controller->startGame();
}
