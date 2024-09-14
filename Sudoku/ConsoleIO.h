#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include <iostream>
#include <vector>
#include <chrono>

class ConsoleIO : public IOInterface {
public:
    ConsoleIO();
    // 显示棋盘
    void displayBoard(const std::vector<std::vector<Cell>>& board) override;

    // 显示信息
    void displayInfo(const int id, const std::string difficulty) override;

    // 显示消息
    void displayMessage(const std::string& message) override;

    // 获取用户输入
    std::string getUserInput() override;

    // 获取用户操作并返回操作向量
    std::vector<int> getOperation() override;

    // 获取位置，返回向量
    std::vector<int> getPosition() override;

    // 获取数，返回一个整数
    int getNumber() override;

    // 显示菜单，返回用户选择
    int displayMenu(const std::vector<std::string>& options) override;

    // 开始游戏，初始化计时器和步数统计
    void startGame();

    // 增加步数统计
    void incrementMoveCount();

    // 显示当前时间和步数
    void displayTimeAndMoves();

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time; // 游戏开始时间
    int move_count; // 操作次数
};

#endif // CONSOLE_IO_H
