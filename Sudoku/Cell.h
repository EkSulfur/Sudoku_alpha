#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
private:
    int value; // 当前的值，如果未确定则为 0
    std::vector<int> candidates; // 候选值

public:
    // 构造函数
    Cell();

    // 获取当前的值
    int getValue() const;

    // 设置当前的值
    void setValue(int val);

    // 获取候选值
    const std::vector<int>& getCandidates() const;

    // 删除候选值
    void removeCandidate(int candidate);

    // 判断某个候选值是否存在
    bool hasCandidate(int candidate) const;

    // 重置候选值
    void resetCandidates();

    // 判断当前格子是否已确定值
    bool isSolved() const;
};

#endif // CELL_H
