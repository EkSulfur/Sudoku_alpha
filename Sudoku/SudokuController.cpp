// SudokuController.cpp
#include "SudokuController.h"
#include "StateManager.h"
#include "Trimmer.h"
#include "MainMenuManager.h"
#include "GameMenuManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <ctime>


// 构造函数
SudokuController::SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface)
    : sudoku(sudokuModel), io(ioInterface),
    isSudokuRunning(true), isRunning(true), operationRecorder(sudokuModel) {

    // 初始化主菜单和游戏菜单 具体的菜单项的构建放入菜单类中，与控制类分离
    mainMenuManager = new MainMenuManager(this, io, &isRunning);
    gameMenuManager = new GameMenuManager(sudoku, io, &operationRecorder, &isSudokuRunning);
}

// 析构函数
SudokuController::~SudokuController() {
    delete mainMenuManager;
    delete gameMenuManager;
}

// 主程序循环，包括主菜单
void SudokuController::start() {
    while (isRunning) {
        io->displayMessage("***Sudoku-Alpha-ver-2.0***");
        mainMenuManager->displayMenu(io);
        // 菜单选项的动作已经在对应的命令中执行，无需额外处理
    }
}

// 开始新游戏的实现
void SudokuController::startGame() {
    // 加载游戏
	loadGame();

    // 开始游戏循环
    gameLoop();
}

// 载入游戏的实现
void SudokuController::loadGame() {
    int id;
    int minID, maxID;

    // 获取ID范围
    if (!getIDRange(minID, maxID)) {
        this->io->displayError("无法获取存档的ID范围，请检查存档文件。");
        return;
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
        id = io->getNumber();

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
        if (!(sudoku->loadFromFileToData(*puzzleData))) {
            this->io->displayError("加载失败");
            continue;
        }

        if (!this->sudoku->loadFromData(*puzzleData)) {
            this->io->displayError("无法把数据传递到sudoku中");
            continue;
        }
        else break;
    }
}

// 游戏主循环的实现
void SudokuController::gameLoop() {
    // 开始计时器
    StateManager::getInstance().timer.start();
    io->startGame();
    isSudokuRunning = true;

    // 游戏主循环
    while (isSudokuRunning) {
        io->displayBoard(sudoku->getBoard());
        if (sudoku->checkIfSolved()) {
            PuzzleData* puzzleData = &StateManager::getInstance().puzzleData;
            io->displayInfo(*puzzleData);
            io->displayEndGame();
            break;
        }

        PuzzleData* puzzleData = &StateManager::getInstance().puzzleData;
        io->displayInfo(*puzzleData);
        // 显示菜单并处理用户选择
        handleMenuSelection();
    }
}

// 处理菜单选择的实现
void SudokuController::handleMenuSelection() {
    gameMenuManager->displayMenu(io);

    // 增加操作次数
    StateManager::getInstance().counter.increment();
}

// 获取所有可用的 ID，确保去重
bool SudokuController::getAvailableIDs(std::vector<int>& availableIDs) {
    const std::string path = StateManager::getInstance().puzzleData.filename;
    std::ifstream infile(path);
    if (!infile.is_open()) {
        this->io->displayError("无法打开存档文件：" + path);
        return false;
    }

    std::string line;
    std::set<int> idSet;

    while (std::getline(infile, line)) {
        Trimmer trimmer;
        trimmer.trim(line);
        if (line.find("ID:") == 0) {
            std::istringstream iss(line.substr(3)); // 跳过 "ID:"
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
