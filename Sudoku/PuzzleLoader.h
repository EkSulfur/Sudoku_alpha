#ifndef PUZZLE_LOADER_H
#define PUZZLE_LOADER_H

#include <vector>
#include <string>

/*
9��6��
Ŀǰ��gptд��
С������������ڲ��߼����ټ�鲻����
�����д��Ԫ���Բ鿴��Щ�����ܷ���������
�����ϵ��������gpt��д����ʾ��
by lch
���id����
*/

class PuzzleLoader {
public:
    virtual ~PuzzleLoader() = default;

    // ���ⲿ��Դ������������
    // ������board �� 9x9 �� Cell �����Ѷ��� difficulty ����
    virtual bool loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty) = 0;

    // ���������̱��浽�ⲿ��Դ
    // ������board �� 9x9 �� Cell ����difficulty �ǵ�ǰ�Ѷ�
    virtual bool savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty) = 0;
};

#endif // PUZZLE_LOADER_H
