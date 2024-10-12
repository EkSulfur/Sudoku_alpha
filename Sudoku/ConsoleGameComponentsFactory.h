#ifndef CONSOLEGAMECOMPONENTSFACTORY
#define CONSOLEGAMECOMPONENTSFACTORY

#include "GameComponentsFactory.h"
#include "ConsoleIO.h"
#include "PuzzleLoaderDAT.h"
#include "Sudoku.h"
#include "SudokuController.h"

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

#endif // !CONSOLEGAMECOMPONENTSFACTORY
