#include "SudokuController.h"
#include "BasicCommands.h"
#include "OperationRecorder.h"
#include <fstream>

SudokuController::SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface)
    : sudoku(sudokuModel), io(ioInterface),
    isRunning(true),operationRecorder(sudokuModel) {
    // 初始化菜单选项
    menuManager.addOption("输入一个数", new InputNumberCommand(sudoku, io, &operationRecorder));
    menuManager.addOption("擦去一个数", new EraseNumberCommand(sudoku, io, &operationRecorder));
    menuManager.addOption("输入候选数", new AddCandidateCommand(sudoku, io));
    menuManager.addOption("删除候选数", new RemoveCandidateCommand(sudoku, io));
    menuManager.addOption("自动更新候选数", new AutoUpdateCandidatesCommand(sudoku, io));
    menuManager.addOption("保存游戏", new SaveGameCommand(sudoku, io, sudoku->getID()));
    menuManager.addOption("重置游戏", new ResetGameCommand(sudoku, io));
    menuManager.addOption("自动填入唯一候选数", new AutoSetNumberCommand(sudoku));
    menuManager.addOption("返回上一步对值的修改", new BackCommand(sudoku, io, &operationRecorder));
    menuManager.addOption("撤销返回上一步", new RevokeBackCommand(sudoku, io, &operationRecorder));
    menuManager.addOption("退出游戏", new ExitGameCommand(io, &isRunning));
}


void SudokuController::startGame(){
    int id;

    // 加载循环
    while (true) {
        // 选择游戏存档ID
        io->displayMessage("请选择存档编号：");
        std::string input = io->getUserInput();

        // 尝试将用户输入转换为整数ID
        try {
            id = std::stoi(input);  // 将输入的字符串转换为整数ID
        }
        catch (const std::invalid_argument&) {
            io->displayMessage("无效的输入，请输入正确的存档编号。");
            continue;
        }

        PuzzleData puzzleData(id);

        // 加载游戏
        if (!sudoku->loadFromFile(puzzleData)) {
            io->displayMessage("无法加载数独游戏。");
            continue;
        }
        else break;
    }

    // 游戏主循环
    while (isRunning) {
        io->displayInfo(sudoku->getID(), sudoku->getDifficulty());
        io->displayBoard(sudoku->getBoard());

        if (sudoku->checkIfSolved()) {
            io->displayMessage("恭喜！你已经完成了数独！");
            break;
        }

        // 显示菜单并处理用户选择
        handleMenuSelection();
    }
}


void SudokuController::handleMenuSelection() {
    // 通过MenuManager显示菜单并执行对应的命令
    menuManager.displayMenu(io);
}