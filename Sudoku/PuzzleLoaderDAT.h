#ifndef PUZZLELOADERDAT_H
#define PUZZLELOADERDAT_H

#include <vector>
#include <string>
#include "PuzzleLoader.h"


class PuzzleLoaderDAT : public PuzzleLoader {
public:
    // 实现加载数独棋盘的功能，传递封装了元数据的 PuzzleData
    bool loadPuzzle(PuzzleData& data) override;

    // 实现保存数独棋盘的功能，传递封装了元数据的 PuzzleData
    bool savePuzzle(const PuzzleData& data) override;
};

#endif // PUZZLELOADERDAT_H
