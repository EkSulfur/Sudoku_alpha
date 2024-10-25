#ifndef CELL_H
#define CELL_H

#include <vector>

/*
9月5日修改：
Cell中添加fixed数据成员，如果为正则不可修改
添加带参的构造函数
将修改函数改为返回bool类型  
9月6日：
重写候选值相关的函数
9月7日：
修改候选值相关的函数
10月7日：
将函数签名放在类的前面，添加setFixed函数（更改单元格里的值是否固定），在setValue函数中
添加force参数，强制修改值并把fixed设为1（考虑后续可能要求在游戏中基于原有的数独生成新数独或覆盖已有的
，让类的适应性更强）
*/

class Cell {
public:
    // 构造函数
    Cell();

    // 带参构造函数，构造棋盘时调用
    Cell(int val);

    // 获取当前的值
    int getValue() const;

    // 设置当前的值
    bool setValue(int val, bool force=false);

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

    // 判断该数是否可以改动
    bool isFixed() const;

    // 设置数是否可以改动
    void setFixed(bool new_fixed);
private:
    int value; // 当前的值，如果未确定则为 0
    std::vector<int> candidates; // 候选值
    bool fixed;
};

#endif // CELL_H