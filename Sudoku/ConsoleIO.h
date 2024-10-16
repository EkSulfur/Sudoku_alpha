#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include "Cursor.h"
#include "Timer.h"
#include "Counter.h"
#include <iostream>
#include <vector>
#include <chrono>

class ConsoleIO : public IOInterface {
public:
    ConsoleIO();
    // 显示棋盘
    void displayBoard(const std::vector<std::vector<Cell>>& board) const override;

    // 显示信息
    void displayInfo(const int id, const std::string difficulty)  override;

    // 新的显示信息函数（利用PuzzleData类实现更好的可拓展性）
    void displayInfo(PuzzleData puzzleData) override;

    //新的显示信息函数（无参）
    void displayInfo() override;

    // 显示消息
    void displayMessage(const std::string& message) const override;

    // 显示错误
    void displayError(const std::string& error) const override;

    // 获取用户输入
    std::string getUserInput() override;

    // 获取用户操作并返回操作向量
    std::vector<int> getOperation() override;

    // 获取位置，返回向量
    std::vector<int> getPosition() override;

    // 获取数，返回一个整数
    int getNumber() override;

    // 显示菜单
    void displayMenu(const std::vector<std::string>& options) override;

    // 开始游戏，初始化计时器和步数统计
    void startGame() override;

    // 询问是否结束
    void displayEndGame() override;

    // 刷新页面（未使用）
    void refresh() override;

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time; // 游戏开始时间
    Cursor cursor; // 光标操作类
};

#endif // CONSOLE_IO_H
