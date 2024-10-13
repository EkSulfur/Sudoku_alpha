#ifndef CONSOLE_GAMECOMPONENTS_FACTORY_H
#define CONSOLE_GAMECOMPONENTS_FACTORY_H

#include "GameComponentsFactory.h"
#include "ConsoleIO.h"
#include "PuzzleLoaderDAT.h"
#include "Sudoku.h"
#include "SudokuController.h"

// 具体工厂类
class ConsoleGameComponentsFactory : public GameComponentsFactory {
public:
    IOInterface* createIOInterface() override {
        return new ConsoleIO();
    }

    PuzzleLoader* createPuzzleLoader() override {
        return new PuzzleLoaderDAT();
    }

    // 实现创建数独游戏实例的方法
    Sudoku* createSudoku(PuzzleLoader* loader) override {
        return new Sudoku(loader);
    }

    // 实现创建控制器实例的方法
    SudokuController* createController(Sudoku* sudoku, IOInterface* io) override {
        return new SudokuController(sudoku, io);
    }
};

#endif // !CONSOLE_GAMECOMPONENTS_FACTORY_H
