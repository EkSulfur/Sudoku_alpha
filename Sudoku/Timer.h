#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    void start();  // 开始计时
    long getElapsedSeconds() const;  // 获取经过的秒数
    void displayTime() const;  // 显示时间

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;  // 开始时间
};

#endif // TIMER_H

