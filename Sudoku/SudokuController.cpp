// SudokuController.cpp
#include "SudokuController.h"
#include "BasicCommands.h"
#include "OperationRecorder.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <set>

// 辅助函数：修剪字符串
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
}

static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

// 构造函数
SudokuController::SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface)
    : sudoku(sudokuModel), io(ioInterface), archieve(1),
    isSudokuRunning(true), isRunning(true), timer(), counter(), operationRecorder(sudokuModel) {
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

// 获取所有可用的 ID，确保去重
bool SudokuController::getAvailableIDs(std::vector<int>& availableIDs) {
    std::ifstream infile(this->SAVE_FILE_PATH); // 使用 this-> 确保访问成员变量
    if (!infile.is_open()) {
        this->io->displayMessage("无法打开存档文件：" + this->SAVE_FILE_PATH);
        return false;
    }

    std::string line;
    std::set<int> idSet;

    while (std::getline(infile, line)) {
        trim(line); // 修剪行的前导和尾随空格
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
        this->io->displayMessage("存档文件中未找到任何ID。");
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

// 开始游戏的实现
void SudokuController::startGame() {
    int id;
    int minID, maxID;

    // 获取ID范围
    if (!getIDRange(minID, maxID)) {
        this->io->displayMessage("无法获取存档的ID范围，请检查存档文件。"); // 使用 this->io
        return; // 根据需求选择其他处理方式
    }

    // 获取所有可用的 ID
    std::vector<int> availableIDs;
    if (!getAvailableIDs(availableIDs)) {
        this->io->displayMessage("无法获取存档的ID，请检查存档文件。");
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
            this->io->displayMessage("无效的输入，请输入正确的存档编号。");
            continue;
        }

        // 检查ID是否在有效范围内
        if (id < minID || id > maxID) {
            this->io->displayMessage("输入的存档编号不在有效范围内。");
            continue;
        }

        // 检查ID是否在可用的 ID 列表中
        if (std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end()) {
            this->io->displayMessage("输入的存档编号不存在。");
            continue;
        }

        PuzzleData puzzleData(id);

        // 加载游戏
        if (!this->sudoku->loadFromFile(puzzleData)) {
            this->io->displayMessage("无法加载数独游戏。请确保存档编号正确且文件格式无误。");
            continue;
        }
        else break;
    }

    // 开始计时器
    this->timer.start();

    // 游戏主循环
    while (this->isSudokuRunning) {
        this->io->displayInfo(this->sudoku->getID(), this->sudoku->getDifficulty());
        this->io->displayBoard(this->sudoku->getBoard());
        this->displayTimeAndMoves();  // 显示时间和步数

        if (this->sudoku->checkIfSolved()) {
            this->io->displayMessage("恭喜！你已经完成了数独！");
            break;
        }

        // 显示菜单并处理用户选择
        this->handleMenuSelection();
    }
}

// 处理菜单选择的实现
void SudokuController::handleMenuSelection() {
    int choice = this->gameMenuManager.displayMenu(this->io);

    // 增加操作次数
    this->counter.increment();

    // 显示当前时间和步数
    this->displayTimeAndMoves();
}

// 显示时间和步数的实现
void SudokuController::displayTimeAndMoves() {
    this->timer.displayTime();
    this->counter.displayCount();
}
