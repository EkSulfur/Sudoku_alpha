#ifndef PUZZLELOADERDAT_H
#define PUZZLELOADERDAT_H

#include <vector>
#include <string>
#include <map>
#include <utility>  // for std::pair
#include "PuzzleLoader.h"

// PuzzleLoaderDAT 继承自 PuzzleLoader，并实现了从 .dat 文件加载和保存数独的功能。
class PuzzleLoaderDAT : public PuzzleLoader {
public:
    // 从 .dat 文件加载数独棋盘
    // 参数：filename 是文件路径，gameID 是数独游戏ID，board 是 9x9 的棋盘矩阵，difficulty 是游戏难度
    bool loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty) override;

    // 将数独棋盘保存到 .dat 文件
    // 参数：filename 是文件路径，gameID 是数独游戏ID，board 是 9x9 的棋盘矩阵，difficulty 是当前难度
    bool savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty) override;

    // 从 .dat 文件加载候选数
    // 参数：filename 是候选数文件路径，gameID 是数独游戏ID，candidates 存储每个空格的候选数
    bool loadCandidates(const std::string& filename, int gameID, std::map<std::pair<int, int>, std::vector<int>>& candidates);

    // 将候选数保存到 .dat 文件
    // 参数：filename 是候选数文件路径，gameID 是数独游戏ID，candidates 存储每个空格的候选数
    bool saveCandidates(const std::string& filename, int gameID, const std::map<std::pair<int, int>, std::vector<int>>& candidates);
};

#endif // PUZZLELOADERDAT_H
