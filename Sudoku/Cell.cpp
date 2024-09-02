#include "Cell.h"
#include <algorithm>
#include <iostream>

// 构造函数
Cell::Cell() : value(0) {
    // 初始化候选值为1到9
    for (int i = 1; i <= 9; ++i) {
        candidates.push_back(i);
    }
}

// 获取当前的值
int Cell::getValue() const {
    return value;
}

// 设置当前的值
void Cell::setValue(int val) {
    if (val >= 1 && val <= 9) {
        value = val;
        candidates.clear(); // 设置值后，清空候选值
    }
    else if (val == 0) { //如果设置为0代表没有填
        value = val; //value为0，代表没有填
        for (int i = 1; i <= 9; ++i) { //候选值设置为所有的数
            candidates.push_back(i);
        }
    }
    else {
        std::cerr << "Invalid value. It must be between 1 and 9." << std::endl;
    }
}

// 获取候选值
const std::vector<int>& Cell::getCandidates() const {
    return candidates;
}

// 删除候选值
void Cell::removeCandidate(int candidate) {
    auto it = std::find(candidates.begin(), candidates.end(), candidate);
    if (it != candidates.end()) {
        candidates.erase(it);
    }
}

// 判断某个候选值是否存在
bool Cell::hasCandidate(int candidate) const {
    return std::find(candidates.begin(), candidates.end(), candidate) != candidates.end();
}

// 重置候选值
void Cell::resetCandidates() {
    candidates.clear();
    for (int i = 1; i <= 9; ++i) {
        candidates.push_back(i);
    }
}

// 判断当前格子是否已确定值
bool Cell::isSolved() const {
    return value != 0;
}
