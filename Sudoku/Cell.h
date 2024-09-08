#ifndef CELL_H
#define CELL_H

#include <vector>

/*
9月5日修改：
Cell中添加fixed数据成员，如果为正则不可修改
添加带参的构造函数
将修改函数改为返回bool类型 by lch
9月6日：
重写候选值相关的函数
9月7日：
修改候选值相关的函数
*/

class Cell {
private:
    int value; // 当前的值，如果未确定则为 0
    std::vector<int> candidates; // 候选值
    bool fixed;
public:
    // 构造函数
    Cell();

    // 带参构造函数，构造棋盘时调用
    Cell(int val);

    // 获取当前的值
    int getValue() const;

    // 设置当前的值
    bool setValue(int val);

    // 获取候选值
    const std::vector<int>& getCandidates() const;

    // 添加候选值
    bool addCandidate(int candidate);

    // 删除候选值
    bool removeCandidate(int candidate);

    // 判断某个候选值是否存在
    bool hasCandidate(int candidate) const;

    // 重置候选值
    void resetCandidates();

    // 判断当前格子是否已确定值
    bool isSolved() const;
};

#endif // CELL_H