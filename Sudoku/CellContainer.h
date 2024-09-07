#ifndef CELL_CONTAINER_H
#define CELL_CONTAINER_H

#include <vector>
#include "Cell.h"

class CellContainer {
protected:
    std::vector<Cell*> cells; // 使用指针数组，以便操作具体的Cell对象

public:
    // 构造函数
    CellContainer();

    // 添加Cell到容器中
    void addCell(Cell* cell);

    // 获取容器中的所有Cell
    const std::vector<Cell*>& getCells() const;

    // 判断容器是否有效（即每个Cell的值在1到9之间且不重复）
    bool isValid() const;

    // 判断容器是否已完成（即每个Cell都有一个确定的值）
    bool isSolved() const;

    // 重置所有Cell的候选值
    void resetCandidates();

    // 查看CellContainer中是否存在某一值
    bool hasValue(int value) const;
};

#endif // CELL_CONTAINER_H
