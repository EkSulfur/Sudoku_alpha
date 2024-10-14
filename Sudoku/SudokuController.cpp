// SudokuController.cpp
#include "SudokuController.h"
#include "BasicCommands.h"
#include "OperationRecorder.h"
#include "StateManager.h"
#include "Trimmer.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <set>


// 构造函数
SudokuController::SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface)
    : sudoku(sudokuModel), io(ioInterface), archieve(1),
    isSudokuRunning(true), isRunning(true), operationRecorder(sudokuModel) {
    // 初始化游戏菜单选项
    gameMenuManager.addOption("输入一个数", new InputNumberCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("擦去一个数", new EraseNumberCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("输入候选数", new AddCandidateCommand(sudoku, io));
    gameMenuManager.addOption("删除候选数", new RemoveCandidateCommand(sudoku, io));
    gameMenuManager.addOption("自动更新候选数", new AutoUpdateCandidatesCommand(sudoku, io));
    gameMenuManager.addOption("保存游戏", new SaveGameCommand(sudoku, io, sudoku->getID()));
    gameMenuManager.addOption("重置游戏", new ResetGameCommand(sudoku, io));
    gameMenuManager.addOption("自动填入唯一候选数", new AutoSetNumberCommand(sudoku));
    gameMenuManager.addOption("撤销上一步对值的修改", new BackCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("重做上一步对值的修改", new RevokeBackCommand(sudoku, io, &operationRecorder));
    gameMenuManager.addOption("退出游戏", new ExitCommand(io, &isSudokuRunning));
    
    // 初始化主菜单选项（未实现，可以后拓展）
    mainMenuManager.addOption("选择游戏存档", new GetNumber(io, &archieve));
    mainMenuManager.addOption("退出程序", new ExitCommand(io, &isRunning));
}

// 开始游戏的实现
void SudokuController::startGame() {
    int id;
    int minID, maxID;

    // 获取ID范围
    if (!getIDRange(minID, maxID)) {
        this->io->displayError("无法获取存档的ID范围，请检查存档文件。"); // 使用 this->io
        return; // 根据需求选择其他处理方式
    }

    // 获取所有可用的 ID
    std::vector<int> availableIDs;
    if (!getAvailableIDs(availableIDs)) {
        this->io->displayError("无法获取存档的ID，请检查存档文件。");
        return;
    }

    // 显示所有可用的 ID
    std::string idsList = "可用的存档编号：";
    for (size_t i = 0; i < availableIDs.size(); ++i) {
        idsList += std::to_string(availableIDs[i]);
        if (i != availableIDs.size() - 1) {
            idsList += ", ";
        }
    }
    this->io->displayMessage(idsList);

    // 加载循环
    PuzzleData* puzzleData = &StateManager::getInstance().puzzleData;
    while (true) {
        // 显示ID范围提示
        std::string prompt = "请选择存档编号 (编号 " + std::to_string(minID) + " --- " + std::to_string(maxID) + ")：";
        this->io->displayMessage(prompt);
        std::string input = this->io->getUserInput();

        // 尝试将用户输入转换为整数ID
        try {
            id = std::stoi(input);  // 将输入的字符串转换为整数ID
        }
        catch (const std::invalid_argument&) {
            this->io->displayError("无效的输入，请输入正确的存档编号。");
            continue;
        }

        // 检查ID是否在有效范围内
        if (id < minID || id > maxID) {
            this->io->displayError("输入的存档编号不在有效范围内。");
            continue;
        }

        // 检查ID是否在可用的 ID 列表中
        if (std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end()) {
            this->io->displayError("输入的存档编号不存在。");
            continue;
        }

        puzzleData->gameID = id;

        // 加载游戏
        // 调用puzzleLoader的loadPuzzle函数
        if (!(sudoku->loadFromFileToData(*puzzleData))) {
            this->io->displayError("加载失败");
        }

        if (!this->sudoku->loadFromData(*puzzleData)) {
            this->io->displayError("无法把数据传递到sudoku中");
            continue;
        }
        else break;
    }

    // 开始计时器
    StateManager::getInstance().timer.start();
    io->startGame();
    // 游戏主循环
    while (isSudokuRunning) {

        io->displayBoard(sudoku->getBoard());
        if (sudoku->checkIfSolved()) {
            io->displayInfo(*puzzleData);
            io->displayEndGame();
            break;
        }

        io->displayInfo(*puzzleData);
        // 显示菜单并处理用户选择
        this->handleMenuSelection();
    }
}

// 处理菜单选择的实现
void SudokuController::handleMenuSelection() {
    int choice = this->gameMenuManager.displayMenu(this->io);

    // 增加操作次数
    StateManager::getInstance().counter.increment();
}

// 获取所有可用的 ID，确保去重
bool SudokuController::getAvailableIDs(std::vector<int>& availableIDs) {
    const std::string path = StateManager::getInstance().puzzleData.filename;
    std::ifstream infile(path); // 使用 this-> 确保访问成员变量
    if (!infile.is_open()) {
        this->io->displayError("无法打开存档文件：" + path);
        return false;
    }

    std::string line;
    std::set<int> idSet;

    while (std::getline(infile, line)) {
        Trimmer trimmer;
        trimmer.trim(line); // 修剪行的前导和尾随空格
        // 查找以 "ID:" 开头的行
        if (line.find("ID:") == 0) {
            // 提取 ID 数值，修正 substr 起始位置
            std::istringstream iss(line.substr(4)); // 跳过 "ID: "
            int id;
            if (iss >> id) {
                idSet.insert(id);
            }
        }
    }

    infile.close();

    if (idSet.empty()) {
        this->io->displayError("存档文件中未找到任何ID。");
        return false;
    }

    // 将 set 转换为 vector
    availableIDs.assign(idSet.begin(), idSet.end());

    return true;
}

// 获取ID范围的实现
bool SudokuController::getIDRange(int& minID, int& maxID) {
    std::vector<int> availableIDs;
    if (!getAvailableIDs(availableIDs)) {
        return false;
    }

    minID = *std::min_element(availableIDs.begin(), availableIDs.end());
    maxID = *std::max_element(availableIDs.begin(), availableIDs.end());

    return true;
}