#ifndef PUZZLE_LOADER_H
#define PUZZLE_LOADER_H

#include <vector>
#include <string>

/*
9月6日
目前是gpt写的
小豪负责先理解内部逻辑，再检查不合理处
最好能写单元测试查看这些函数能否正常工作
技术上的问题多问gpt，写好提示词
by lch
添加id参数
*/

class PuzzleLoader {
public:
    virtual ~PuzzleLoader() = default;

    // 从外部资源加载数独棋盘
    // 参数：board 是 9x9 的 Cell 矩阵，难度由 difficulty 传递
    virtual bool loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty) = 0;

    // 将数独棋盘保存到外部资源
    // 参数：board 是 9x9 的 Cell 矩阵，difficulty 是当前难度
    virtual bool savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty) = 0;
};

#endif // PUZZLE_LOADER_H
