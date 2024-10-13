#ifndef GAME_COMPONENTS_FACTORY_H
#define GAME_COMPONENTS_FACTORY_H

#include "IOInterface.h"
#include "Sudoku.h"
#include "PuzzleLoader.h"
#include "SudokuController.h"

// 抽象工厂，创建一个抽象的工厂接口，用于创建相关的对象
class GameComponentsFactory {
public:
    virtual ~GameComponentsFactory() = default;

    // 创建输入输出接口
    virtual IOInterface* createIOInterface() = 0;

    // 创建题目加载器
    virtual PuzzleLoader* createPuzzleLoader() = 0;

    // 创建数独游戏实例
    virtual Sudoku* createSudoku(PuzzleLoader* loader) = 0;

    // 创建控制器实例
    virtual SudokuController* createController(Sudoku* sudoku, IOInterface* io) = 0;
};


#endif