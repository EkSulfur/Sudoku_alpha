#ifndef GAMECOMPONENTSFACTORY
#define GAMECOMPONENTSFACTORY

#include "IOInterface.h"
#include "Sudoku.h"
#include "PuzzleLoader.h"
#include "SudokuController.h"

// GameComponentsFactory.h
class GameComponentsFactory {
public:
    virtual ~GameComponentsFactory() = default;

    // 创建输入输出接口
    virtual IOInterface* createIOInterface() = 0;

    // 创建题目加载器
    virtual PuzzleLoader* createPuzzleLoader() = 0;

    // **新增：创建数独游戏实例**
    virtual Sudoku* createSudoku(PuzzleLoader* loader) = 0;

    // **新增：创建控制器实例**
    virtual SudokuController* createController(Sudoku* sudoku, IOInterface* io) = 0;
};


#endif