#ifndef GUI_GAME_COMPONENTS_FACTORY_H
#define GUI_GAME_COMPONENTS_FACTORY_H

// 未来可能如果未来需要支持其他平台或变种，例如 GUI 版本，可以创建新的工厂类如下

/*
#include "GameComponentsFactory.h"
#include "GUIIO.h"
#include "PuzzleLoaderXML.h"
#include "Sudoku.h"
#include "SudokuController.h"

class GUIGameComponentsFactory : public GameComponentsFactory {
public:
    IOInterface* createIOInterface() override {
        return new GUIIO();
    }

    PuzzleLoader* createPuzzleLoader() override {
        return new PuzzleLoaderXML();
    }

    Sudoku* createSudoku(PuzzleLoader* loader) override {
        return new Sudoku(loader);
    }

    SudokuController* createController(Sudoku* sudoku, IOInterface* io) override {
        return new SudokuController(sudoku, io);
    }
};
*/

#endif // !GUI_GAME_COMPONENTS_FACTORY_H
