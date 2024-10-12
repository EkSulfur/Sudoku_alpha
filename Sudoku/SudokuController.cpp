#include "SudokuController.h"
#include "BasicCommands.h"
#include "OperationRecorder.h"
#include <fstream>

SudokuController::SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface)
    : sudoku(sudokuModel), io(ioInterface),archieve(1),
    isSudokuRunning(true), isRunning(true), timer(), counter(),operationRecorder(sudokuModel) {
    // 初始化游戏菜单选项
    gameMenuManager.addOption("输入一个数", new InputNumberCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("擦去一个数", new EraseNumberCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("输入候选数", new AddCandidateCommand(sudoku, io));
    gameMenuManager.addOption("删除候选数", new RemoveCandidateCommand(sudoku, io));
    gameMenuManager.addOption("自动更新候选数", new AutoUpdateCandidatesCommand(sudoku, io));
    gameMenuManager.addOption("保存游戏", new SaveGameCommand(sudoku, io, sudoku->getID()));
    gameMenuManager.addOption("重置游戏", new ResetGameCommand(sudoku, io));
    gameMenuManager.addOption("自动填入唯一候选数", new AutoSetNumberCommand(sudoku));
    gameMenuManager.addOption("返回上一步对值的修改", new BackCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("撤销返回上一步", new RevokeBackCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("退出游戏", new ExitCommand(io, &isSudokuRunning));
    
    // 初始化主菜单选项
    mainMenuManager.addOption("选择游戏存档", new GetNumber(io, &archieve));
    mainMenuManager.addOption("退出程序", new ExitCommand(io, &isRunning));
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

    // 开始计时器
    timer.start();

    // 游戏主循环
    while (isSudokuRunning) {
        io->displayInfo(sudoku->getID(), sudoku->getDifficulty());
        io->displayBoard(sudoku->getBoard());
        displayTimeAndMoves();  // 显示时间和步数
        if (sudoku->checkIfSolved()) {
            io->displayMessage("恭喜！你已经完成了数独！");
            break;
        }

  
        // 显示菜单并处理用户选择
        handleMenuSelection();
    }
}


void SudokuController::handleMenuSelection() {
    int choice = gameMenuManager.displayMenu(io);

    // 增加操作次数
    counter.increment();

    // 显示当前时间和步数
    displayTimeAndMoves();
}

void SudokuController::displayTimeAndMoves() {
    timer.displayTime();
    counter.displayCount();
}