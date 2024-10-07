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
9月7日：
setValue不修改候选值
带参构造函数中添加关于候选值的初始化
修正resetCandidates
添加addCandidates函数
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
Cell::Cell(int val):value(val), fixed(0)
{   
    if (val != 0) {
        for (int i = 0; i <= 10; ++i) {  // 9月9日修改关键错误：i应该从0开始
            candidates.push_back(0); //值为0代表对应索引不是候选值
            fixed = 1; //值不可改变
        }
    }
    else {
        for (int i = 0; i <= 10; ++i) {
            candidates.push_back(1); //值为1代表对应索引的数是候选值
        }
    }
    //鉴于candidates为vector类型，这里可以不初始化（应该）
}

// 获取当前的值
int Cell::getValue() const {
    return value;
}

// 设置当前的值
bool Cell::setValue(int val, bool force) {
    if (!force) {
        if (this->fixed == 1) {
            return false; //值固定，修改失败
        }
        else {
            value = val;
        }
    }
    else {
        // 强制修改
        this->fixed = 1;
        value = val;
    }
    return true;
}

// 获取候选值
const std::vector<int>& Cell::getCandidates() const {
    return candidates;
}

bool Cell::addCandidate(int candidate)
{
    if (candidate < 1 || candidate > 9) return false;
    candidates[candidate] = 1; //对应索引设为1代表是候选值
    return true;
}

// 删除候选值
bool Cell::removeCandidate(int candidate) {
    if (candidate < 1 || candidate > 9) return false;
    candidates[candidate] = 0; //对应索引设为0代表不是候选值
    return true;
}

// 判断某个候选值是否存在
bool Cell::hasCandidate(int candidate) const {
    return candidates[candidate];
}

// 重置候选值
void Cell::resetCandidates() {
    for (int i = 1; i <= 10; ++i) {
        candidates[i] = 1; //将候选值重置为都可选
    }
}

// 判断当前格子是否已确定值
bool Cell::isSolved() const {
    return value != 0;
}

bool Cell::isFixed() const
{
    return fixed;
}

void Cell::setFixed(bool new_fixed)
{
    fixed = new_fixed ? 1 : 0;
    return;
}
