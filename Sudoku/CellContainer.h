#ifndef CELL_CONTAINER_H
#define CELL_CONTAINER_H

#include <vector>
#include "Cell.h"

class CellContainer {
protected:
    std::vector<Cell*> cells; // ʹ��ָ�����飬�Ա���������Cell����

public:
    // ���캯��
    CellContainer();

    // ���Cell��������
    void addCell(Cell* cell);

    // ��ȡ�����е�����Cell
    const std::vector<Cell*>& getCells() const;

    // �ж������Ƿ���Ч����ÿ��Cell��ֵ��1��9֮���Ҳ��ظ���
    bool isValid() const;

    // �ж������Ƿ�����ɣ���ÿ��Cell����һ��ȷ����ֵ��
    bool isSolved() const;

    // ��������Cell�ĺ�ѡֵ
    void resetCandidates();

    // �鿴CellContainer���Ƿ����ĳһֵ
    bool hasValue(int value) const;
};

#endif // CELL_CONTAINER_H
