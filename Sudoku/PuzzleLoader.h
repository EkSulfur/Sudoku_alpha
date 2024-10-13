#ifndef PUZZLE_LOADER_H
#define PUZZLE_LOADER_H

#include <vector>
#include <string>
#include "PuzzleData.h"
/*
9月6日
小豪负责先理解内部逻辑，再检查不合理处
最好能写单元测试查看这些函数能否正常工作
by lch
添加id参数
*/

// 封装所有与数独棋盘相关的信息到 PuzzleData 类


class PuzzleLoader {
public:
    virtual ~PuzzleLoader() = default;

    // 从外部资源加载数独棋盘
    // 参数：PuzzleData 封装数独棋盘及其元数据信息
    virtual bool loadPuzzle(PuzzleData& data) = 0;

    // 将数独棋盘保存到外部资源

    // 参数：PuzzleData 封装数独棋盘及其元数据信息
    virtual bool savePuzzle(const PuzzleData& data) = 0;
};

#endif // PUZZLE_LOADER_H