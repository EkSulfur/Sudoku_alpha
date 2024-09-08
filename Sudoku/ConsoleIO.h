#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include <iostream>
#include <vector>

class ConsoleIO : public IOInterface {
public:
    // 显示棋盘
    void displayBoard(const std::vector<std::vector<Cell*>>& board) const override;

    // 显示信息
    void displayInfo(const int id, const std::string difficulty) const override;

    // 显示消息
    void displayMessage(const std::string& message) const override;

    // 获取用户输入
    std::string getUserInput() const override;

    // 获取用户操作并返回操作向量
    std::vector<int> getOperation() const override;

    // 显示菜单，返回用户选择
    int displayMenu(const std::vector<std::string>& options) const override;
};

#endif // CONSOLE_IO_H
