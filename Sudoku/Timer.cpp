#include "Timer.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

// 构造函数
Timer::Timer() : start_time(steady_clock::now()) {}

// 开始计时
void Timer::start() {
    start_time = steady_clock::now();
}

// 获取经过的秒数
long Timer::getElapsedSeconds() const {
    auto current_time = steady_clock::now();
    return static_cast<long>(duration_cast<seconds>(current_time - start_time).count());

}

// 显示时间
void Timer::displayTime() const {
    long elapsed_seconds = getElapsedSeconds();
    int minutes = static_cast<int>(elapsed_seconds / 60);
    int seconds = static_cast<int>(elapsed_seconds % 60);

    cout << "时间已用: " << minutes << " 分 " << seconds << " 秒" << endl;

}
