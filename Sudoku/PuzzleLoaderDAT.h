#ifndef PUZZLE_LOADER_DAT_H
#define PUZZLE_LOADER_DAT_H

#include "PuzzleLoader.h"
#include <fstream>
#include <vector>
#include <string>

class PuzzleLoaderDAT : public PuzzleLoader {
public:
    // 实现加载功能，从.dat文件中加载数独棋盘
    bool loadPuzzle(const std::string& filename, std::vector<std::vector<int>>& board, std::string& difficulty) override;

    // 实现保存功能，将数独棋盘保存到.dat文件中
    bool savePuzzle(const std::string& filename, const std::vector<std::vector<int>>& board, const std::string& difficulty) override;
};

#endif // PUZZLE_LOADER_DAT_H
