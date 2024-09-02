#include "Cell.h"
#include <algorithm>
#include <iostream>

// ���캯��
Cell::Cell() : value(0) {
    // ��ʼ����ѡֵΪ1��9
    for (int i = 1; i <= 9; ++i) {
        candidates.push_back(i);
    }
}

// ��ȡ��ǰ��ֵ
int Cell::getValue() const {
    return value;
}

// ���õ�ǰ��ֵ
void Cell::setValue(int val) {
    if (val >= 1 && val <= 9) {
        value = val;
        candidates.clear(); // ����ֵ����պ�ѡֵ
    }
    else if (val == 0) { //�������Ϊ0����û����
        value = val; //valueΪ0������û����
        for (int i = 1; i <= 9; ++i) { //��ѡֵ����Ϊ���е���
            candidates.push_back(i);
        }
    }
    else {
        std::cerr << "Invalid value. It must be between 1 and 9." << std::endl;
    }
}

// ��ȡ��ѡֵ
const std::vector<int>& Cell::getCandidates() const {
    return candidates;
}

// ɾ����ѡֵ
void Cell::removeCandidate(int candidate) {
    auto it = std::find(candidates.begin(), candidates.end(), candidate);
    if (it != candidates.end()) {
        candidates.erase(it);
    }
}

// �ж�ĳ����ѡֵ�Ƿ����
bool Cell::hasCandidate(int candidate) const {
    return std::find(candidates.begin(), candidates.end(), candidate) != candidates.end();
}

// ���ú�ѡֵ
void Cell::resetCandidates() {
    candidates.clear();
    for (int i = 1; i <= 9; ++i) {
        candidates.push_back(i);
    }
}

// �жϵ�ǰ�����Ƿ���ȷ��ֵ
bool Cell::isSolved() const {
    return value != 0;
}
