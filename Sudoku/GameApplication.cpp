#include "GameApplication.h"
#include "PuzzleLoaderFactory.h"
#include <stdexcept>
#include <iostream>

GameApplication::GameApplication(GameComponentsFactory* factory, const std::string& format)
    : factory(factory), io(nullptr), puzzleLoader(nullptr), game(nullptr), controller(nullptr) {
    // 使用工厂创建 IO 接口
    io = factory->createIOInterface();

    // 使用 PuzzleLoaderFactory 创建适当的 PuzzleLoader
    puzzleLoader = PuzzleLoaderFactory::createPuzzleLoader(format);
    if (!puzzleLoader) {
        throw std::runtime_error("Unsupported format: " + format);
    }

    // 创建数独游戏实例
    game = factory->createSudoku(puzzleLoader);

    // 创建控制器实例
    controller = factory->createController(game, io);
}

GameApplication::~GameApplication() {
    // 清理资源
    delete controller;
    delete game;
    delete puzzleLoader;
    delete io;
    delete factory;
}

void GameApplication::startGame() {
    controller->startGame();
}
