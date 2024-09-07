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
9��7�գ�
setValue���޸ĺ�ѡֵ
���ι��캯������ӹ��ں�ѡֵ�ĳ�ʼ��
����resetCandidates
���addCandidates����
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
Cell::Cell(int val):value(val)
{   
    if (val != 0) {
        for (int i = 1; i <= 10; ++i) {
            candidates.push_back(1); //ֵΪ0�����Ӧ�������Ǻ�ѡֵ
        }
    }
    else {
        for (int i = 1; i <= 10; ++i) {
            candidates.push_back(1); //ֵΪ1�����Ӧ���������Ǻ�ѡֵ
        }
    }
    fixed = 1; //ֵ���ɸı�
    //����candidatesΪvector���ͣ�������Բ���ʼ����Ӧ�ã�
}

// ��ȡ��ǰ��ֵ
int Cell::getValue() const {
    return value;
}

// ���õ�ǰ��ֵ
bool Cell::setValue(int val) {
    if (this->fixed == 1) {
        //�˴�Ŀǰȱ�������ʾ�����ڴ˴���ӿ���Sudoku.cpp�����
        return 0; //ֵ�̶����޸�ʧ��
    }
    //9��7���޸ģ�����ֵ����Ҫ��պ�ѡֵ������û�б�Ҫ���ҷ��ػ�����������������Ҫ��ʾ֮ǰ�ĺ�ѡֵ
    //if (val >= 1 && val <= 9) {
    //    value = val;
    //    resetCandidates(0); // ����ֵ����պ�ѡֵ
    //}
    else if (val == 0) { //�������Ϊ0����û����
        value = val; //valueΪ0������û����
        // resetCandidates(); //��ѡֵ����Ϊ���е�����9��7��ȥ��
    }
    else {
        //�˴������ʾ�����ڴ˴���ӿ���Sudoku.cpp�����
        std::cerr << "Invalid value. It must be between 1 and 9." << std::endl;
    }
    return 1; //�޸ĳɹ�
}

// ��ȡ��ѡֵ
const std::vector<int>& Cell::getCandidates() const {
    return candidates;
}

bool Cell::addCandidate(int candidate)
{
    if (candidate < 1 || candidate > 9) return false;
    candidates[candidate] = 1; //��Ӧ������Ϊ1�����Ǻ�ѡֵ
    return true;
}

// ɾ����ѡֵ
bool Cell::removeCandidate(int candidate) {
    if (candidate < 1 || candidate > 9) return false;
    candidates[candidate] = 0; //��Ӧ������Ϊ0�����Ǻ�ѡֵ
    return true;
}

// �ж�ĳ����ѡֵ�Ƿ����
bool Cell::hasCandidate(int candidate) const {
    return candidates[candidate];
}

// ���ú�ѡֵ
void Cell::resetCandidates() {
    for (int i = 1; i <= 10; ++i) {
        candidates[i] = 1; //����ѡֵ����Ϊ����ѡ
    }
}

// �жϵ�ǰ�����Ƿ���ȷ��ֵ
bool Cell::isSolved() const {
    return value != 0;
}
