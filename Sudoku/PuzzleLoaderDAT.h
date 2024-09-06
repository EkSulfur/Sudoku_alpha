#ifndef PUZZLE_LOADER_DAT_H
#define PUZZLE_LOADER_DAT_H

#include "PuzzleLoader.h"
#include <fstream>
#include <vector>
#include <string>

class PuzzleLoaderDAT : public PuzzleLoader {
public:
    // ʵ�ּ��ع��ܣ���.dat�ļ��м�����������
    bool loadPuzzle(const std::string& filename, std::vector<std::vector<int>>& board, std::string& difficulty) override;

    // ʵ�ֱ��湦�ܣ����������̱��浽.dat�ļ���
    bool savePuzzle(const std::string& filename, const std::vector<std::vector<int>>& board, const std::string& difficulty) override;
};

#endif // PUZZLE_LOADER_DAT_H
