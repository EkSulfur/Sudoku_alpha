#include "Cell.h"
#include <algorithm>
#include <iostream>

/*
9月5日修改：
Cell中添加fixed数据成员，如果为正则不可修改
添加带参的构造函数
将修改函数改为返回bool类型
9月6日：
重写候选值，candidates应为10维向量，每维元素仅可为0或1，代表对应索引是否是候选值
*/

// 构造函数
Cell::Cell() : value(0) {
    // 初始化候选值，创建一个大小为10的向量
    for (int i = 1; i <= 10; ++i) {
        candidates.push_back(1); //值为1代表对应索引的数是候选值
    }
    fixed = 0;
}

//带参构造函数
Cell::Cell(int val) :value(val)
{
    fixed = 1; //值不可改变
    //鉴于candidates为vector类型，这里可以不初始化（应该）
}

// 获取当前的值
int Cell::getValue() const {
    return value;
}

// 设置当前的值
bool Cell::setValue(int val) {
    if (this->fixed == 1) return 0; //值固定，修改失败
    if (val >= 1 && val <= 9) {
        value = val;
        resetCandidates(0); // 设置值后，清空候选值
    }
    else if (val == 0) { //如果设置为0代表没有填
        value = val; //value为0，代表没有填
        resetCandidates(); //候选值设置为所有的数
    }
    else {
        std::cerr << "Invalid value. It must be between 1 and 9." << std::endl;
    }
    return 1; //修改成功
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
    return candidates[candidate];
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