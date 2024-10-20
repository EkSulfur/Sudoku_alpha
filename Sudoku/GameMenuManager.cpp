// GameMenuManager.cpp
#include "GameMenuManager.h"
#include "BasicCommands.h"

GameMenuManager::GameMenuManager(Sudoku* sudoku, IOInterface* io, OperationRecorder* operationRecorder, bool* isSudokuRunning)
    : sudoku(sudoku), io(io), operationRecorder(operationRecorder), isSudokuRunning(isSudokuRunning) {}

void GameMenuManager::buildMenu() {
    addOption("输入一个数", new InputNumberCommand(sudoku, io, operationRecorder));
    addOption("擦去一个数", new EraseNumberCommand(sudoku, io, operationRecorder));
    addOption("输入候选数", new AddCandidateCommand(sudoku, io));
    addOption("删除候选数", new RemoveCandidateCommand(sudoku, io));
    addOption("自动更新候选数", new AutoUpdateCandidatesCommand(sudoku, io));
    addOption("保存游戏", new SaveGameCommand(sudoku, io, sudoku->getID()));
    addOption("重置游戏", new ResetGameCommand(sudoku, io));
    addOption("自动填入唯一候选数", new AutoSetNumberCommand(sudoku));
    addOption("撤销上一步对值的修改", new BackCommand(sudoku, io, operationRecorder));
    addOption("重做上一步对值的修改", new RevokeBackCommand(sudoku, io, operationRecorder));
    addOption("退出游戏", new ExitCommand(io, isSudokuRunning));
}
