#ifndef COUNTER_H
#define COUNTER_H

class Counter {
public:
    Counter();
    void increment();  // 增加步数
    int getCount() const;  // 获取当前步数
    void displayCount() const;  // 显示步数

private:
    int move_count;  // 步数
};

#endif // COUNTER_H
