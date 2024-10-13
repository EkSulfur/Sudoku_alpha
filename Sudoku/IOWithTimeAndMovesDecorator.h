// 装饰器模式（未启用）
#ifndef IOWITHTIMEANDMOVESDECORATOR_H
#define IOWITHTIMEANDMOVESDECORATOR_H

#include "IOInterface.h"
#include <chrono>

class IOWithTimeAndMovesDecorator : public IOInterface {
public:
    IOWithTimeAndMovesDecorator(IOInterface* io);
    ~IOWithTimeAndMovesDecorator();

    // 重写 IOInterface 的所有方法
    void displayBoard(const std::vector<std::vector<Cell>>& board) const override;
    void displayInfo(const int id, const std::string difficulty) override;
    void displayMessage(const std::string& message) const override;
    std::string getUserInput() override;
    std::vector<int> getOperation() override;
    std::vector<int> getPosition() override;
    int getNumber() override;
    void displayMenu(const std::vector<std::string>& options) override;

    // 开始游戏，初始化计时器和步数统计
    void startGame();

private:
    IOInterface* io; // 被装饰的对象
    std::chrono::time_point<std::chrono::steady_clock> start_time; // 游戏开始时间
    int move_count; // 操作次数
};

#endif // IOWITHTIMEANDMOVESDECORATOR_H
