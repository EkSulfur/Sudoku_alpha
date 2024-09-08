#include "testLoader.h"
#include <iostream>

/*
测试Loader相关内容
*/

// 打印数独棋盘的辅助函数
void printBoard(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// 测试函数
void testPuzzleLoader() {
    PuzzleLoaderDAT loader;
    std::vector<std::vector<int>> board;
    std::string difficulty;

    // 测试加载数独棋盘
    if (loader.loadPuzzle("puzzles.dat", 1, board, difficulty)) {
        std::cout << "数独加载成功，难度为: " << difficulty << std::endl;
        printBoard(board);
    }
    else {
        std::cerr << "加载数独失败！" << std::endl;
    }

    // 修改棋盘，保存为新的数独
    std::vector<std::vector<int>> newBoard = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    std::string newDifficulty = "中等";

    // 保存新的数独棋盘
    if (loader.savePuzzle("puzzles.dat", 2, newBoard, newDifficulty)) {
        std::cout << "数独保存成功，ID为 2，难度为: " << newDifficulty << std::endl;
    }
    else {
        std::cerr << "保存数独失败！" << std::endl;
    }

    // 再次加载刚刚保存的数独，验证保存是否成功
    if (loader.loadPuzzle("puzzles.dat", 2, board, difficulty)) {
        std::cout << "ID 为 2 的数独加载成功，难度为: " << difficulty << std::endl;
        printBoard(board);
    }
    else {
        std::cerr << "加载 ID 为 2 的数独失败！" << std::endl;
    }
}