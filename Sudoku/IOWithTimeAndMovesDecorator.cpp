// 装饰器模式（未启用）
#include "IOWithTimeAndMovesDecorator.h"
#include <iostream>

IOWithTimeAndMovesDecorator::IOWithTimeAndMovesDecorator(IOInterface* io)
    : io(io), move_count(0) {
    // 初始化游戏开始时间
    start_time = std::chrono::steady_clock::now();
}

IOWithTimeAndMovesDecorator::~IOWithTimeAndMovesDecorator() {
    delete io; // 记得删除被装饰的对象，防止内存泄漏
}

void IOWithTimeAndMovesDecorator::startGame() {
    start_time = std::chrono::steady_clock::now();
    move_count = 0;
}

// 重写 displayBoard 方法，添加时间和步数显示
void IOWithTimeAndMovesDecorator::displayBoard(const std::vector<std::vector<Cell>>& board) const {
    // 计算经过的时间
    auto now = std::chrono::steady_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();

    // 显示时间和步数
    std::cout << "时间：" << elapsed_seconds << " 秒，步数：" << move_count << std::endl;

    // 调用被装饰对象的 displayBoard 方法
    io->displayBoard(board);
}

// 其他方法直接调用被装饰对象的方法
void IOWithTimeAndMovesDecorator::displayInfo(const int id, const std::string difficulty) {
    io->displayInfo(id, difficulty);
}

void IOWithTimeAndMovesDecorator::displayMessage(const std::string& message) const {
    io->displayMessage(message);
}

std::string IOWithTimeAndMovesDecorator::getUserInput() {
    std::string input = io->getUserInput();
    return input;
}

std::vector<int> IOWithTimeAndMovesDecorator::getOperation() {
    auto op = io->getOperation();
    return op;
}

std::vector<int> IOWithTimeAndMovesDecorator::getPosition() {
    return io->getPosition();
}

int IOWithTimeAndMovesDecorator::getNumber() {
    return io->getNumber();
}

void IOWithTimeAndMovesDecorator::displayMenu(const std::vector<std::string>& options) {
    io->displayMenu(options);
}
