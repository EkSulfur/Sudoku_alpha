#include "GameApplication.h"

// 封装整个游戏
GameApplication::GameApplication(std::unique_ptr<GameComponentsFactory> factory)
    : factory(std::move(factory)) {
    // 使用工厂创建组件
    io = std::unique_ptr<IOInterface>(this->factory->createIOInterface());
    puzzleLoader = std::unique_ptr<PuzzleLoader>(this->factory->createPuzzleLoader());
    game = std::unique_ptr<Sudoku>(this->factory->createSudoku(puzzleLoader.get()));
    controller = std::unique_ptr<SudokuController>(this->factory->createController(game.get(), io.get()));
}

void GameApplication::startGame() {
    controller->startGame();
}
