#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
private:
    int value; // ��ǰ��ֵ�����δȷ����Ϊ 0
    std::vector<int> candidates; // ��ѡֵ

public:
    // ���캯��
    Cell();

    // ��ȡ��ǰ��ֵ
    int getValue() const;

    // ���õ�ǰ��ֵ
    void setValue(int val);

    // ��ȡ��ѡֵ
    const std::vector<int>& getCandidates() const;

    // ɾ����ѡֵ
    void removeCandidate(int candidate);

    // �ж�ĳ����ѡֵ�Ƿ����
    bool hasCandidate(int candidate) const;

    // ���ú�ѡֵ
    void resetCandidates();

    // �жϵ�ǰ�����Ƿ���ȷ��ֵ
    bool isSolved() const;
};

#endif // CELL_H
