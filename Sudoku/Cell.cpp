#include "Cell.h"
#include <algorithm>
#include <iostream>

/*
9��5���޸ģ�
Cell�����fixed���ݳ�Ա�����Ϊ���򲻿��޸�
��Ӵ��εĹ��캯��
���޸ĺ�����Ϊ����bool����
9��6�գ�
��д��ѡֵ��candidatesӦΪ10ά������ÿάԪ�ؽ���Ϊ0��1�������Ӧ�����Ƿ��Ǻ�ѡֵ
*/

// ���캯��
Cell::Cell() : value(0) {
    // ��ʼ����ѡֵ������һ����СΪ10������
    for (int i = 1; i <= 10; ++i) {
        candidates.push_back(1); //ֵΪ1�����Ӧ���������Ǻ�ѡֵ
    }
    fixed = 0;
}

//���ι��캯��
Cell::Cell(int val) :value(val)
{
    fixed = 1; //ֵ���ɸı�
    //����candidatesΪvector���ͣ�������Բ���ʼ����Ӧ�ã�
}

// ��ȡ��ǰ��ֵ
int Cell::getValue() const {
    return value;
}

// ���õ�ǰ��ֵ
bool Cell::setValue(int val) {
    if (this->fixed == 1) return 0; //ֵ�̶����޸�ʧ��
    if (val >= 1 && val <= 9) {
        value = val;
        resetCandidates(0); // ����ֵ����պ�ѡֵ
    }
    else if (val == 0) { //�������Ϊ0����û����
        value = val; //valueΪ0������û����
        resetCandidates(); //��ѡֵ����Ϊ���е���
    }
    else {
        std::cerr << "Invalid value. It must be between 1 and 9." << std::endl;
    }
    return 1; //�޸ĳɹ�
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
    return candidates[candidate];
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