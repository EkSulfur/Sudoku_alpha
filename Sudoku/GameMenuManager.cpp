// GameMenuManager.cpp
#include "GameMenuManager.h"
#include "BasicCommands.h"

GameMenuManager::GameMenuManager(Sudoku* sudoku, IOInterface* io, OperationRecorder* operationRecorder, bool* isSudokuRunning)
    : sudoku(sudoku), io(io), operationRecorder(operationRecorder), isSudokuRunning(isSudokuRunning) {}

int GameMenuManager::displayMenu(IOInterface* io)
{
    // 如果菜单还未构建，调用构建函数
    if (options.empty()) {
        buildMenu();
    }

	// 显示菜单选项
    std::vector<std::string> newOptions;
    for (const auto& option : options)
    {
        newOptions.push_back(option.first);
    }
    io->displayMenu(newOptions);

	// 获取用户选择
    int choice;
    std::string input = io->getUserInput();

    choice = io->getNumber();

    if (choice >= 1 && choice <= static_cast<int>(options.size())) {
        options[choice - 1].second->execute();  // 执行对应的命令
    }
    else {
        io->displayError("无效选项，请重试。");
    }
    return choice;
}

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

