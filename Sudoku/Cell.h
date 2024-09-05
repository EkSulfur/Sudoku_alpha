#ifndef CELL_H
#define CELL_H

#include <vector>

/*
9��5���޸ģ�
Cell�����fixed���ݳ�Ա�����Ϊ���򲻿��޸�
��Ӵ��εĹ��캯��
���޸ĺ�����Ϊ����bool���� by lch
*/

class Cell {
private:
    int value; // ��ǰ��ֵ�����δȷ����Ϊ 0
    std::vector<int> candidates; // ��ѡֵ
    bool fixed;
public:
    // ���캯��
    Cell();

    // ���ι��캯������������ʱ����
    Cell(int val);

    // ��ȡ��ǰ��ֵ
    int getValue() const;

    // ���õ�ǰ��ֵ
    bool setValue(int val);

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
