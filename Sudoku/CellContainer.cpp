#include "CellContainer.h"
#include <unordered_set>

// ���캯��
CellContainer::CellContainer() {}

// ���Cell��������
void CellContainer::addCell(Cell* cell) {
    cells.push_back(cell);
}

// ��ȡ�����е�����Cell
const std::vector<Cell*>& CellContainer::getCells() const {
    return cells;
}

// �ж������Ƿ���Ч����ÿ��Cell��ֵ��1��9֮���Ҳ��ظ���
bool CellContainer::isValid() const {
    std::unordered_set<int> uniqueValues;
    for (const auto& cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (uniqueValues.find(value) != uniqueValues.end()) {
                return false; // ���ظ�ֵ
            }
            uniqueValues.insert(value);
        }
    }
    return true; // û���ظ�ֵ
}

// �ж������Ƿ�����ɣ���ÿ��Cell����һ��ȷ����ֵ��
bool CellContainer::isSolved() const {
    for (const auto& cell : cells) {
        if (!cell->isSolved()) {
            return false; // ����δȷ����Cell
        }
    }
    return true;
}

// ��������Cell�ĺ�ѡֵ
void CellContainer::resetCandidates() {
    for (auto& cell : cells) {
        cell->resetCandidates();
    }
}
