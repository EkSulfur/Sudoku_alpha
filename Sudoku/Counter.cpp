#include "Counter.h"
#include <iostream>

using namespace std;

// 构造函数
Counter::Counter() : move_count(0) {}

// 增加步数
void Counter::increment() {
    ++move_count;
}

// 获取当前步数
int Counter::getCount() const {
    return move_count;
}

// 显示步数
void Counter::displayCount() const {
    cout << "步数: " << move_count << endl;
}
