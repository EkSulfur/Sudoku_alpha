#include "CellContainer.h"
#include <unordered_set>

// 构造函数
CellContainer::CellContainer() {}

// 添加Cell到容器中
void CellContainer::addCell(Cell* cell) {
    cells.push_back(cell);
}

// 获取容器中的所有Cell
const std::vector<Cell*>& CellContainer::getCells() const {
    return cells;
}

// 判断容器是否有效（即每个Cell的值在1到9之间且不重复）
bool CellContainer::isValid() const {
    std::unordered_set<int> uniqueValues;
    for (const auto& cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (uniqueValues.find(value) != uniqueValues.end()) {
                return false; // 有重复值
            }
            uniqueValues.insert(value);
        }
    }
    return true; // 没有重复值
}

// 判断容器是否已完成（即每个Cell都有一个确定的值）
bool CellContainer::isSolved() const {
    for (const auto& cell : cells) {
        if (!cell->isSolved()) {
            return false; // 存在未确定的Cell
        }
    }
    return true;
}

// 重置所有Cell的候选值
void CellContainer::resetCandidates() {
    for (auto& cell : cells) {
        cell->resetCandidates();
    }
}

bool CellContainer::hasValue(int value) const
{
    if (value < 1 || value > 9) return false;
    
    // 遍历所有Cell，检查是否有Cell的值等于给定的值
    for (const Cell* cell : cells) {
        if (cell->getValue() == value) {
            return true;  // 找到值为value的Cell
        }
    }
    return false;  // 没有找到值为value的Cell
}
