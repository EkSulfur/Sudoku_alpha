// master.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include "Sudoku.h"
//#include "ConsoleIO.h"
#include "PuzzleLoaderDAT.h"

//int main() {
//    // 创建控制台输入输出接口
//    ConsoleIO consoleIO;
//
//    // 创建DAT格式的PuzzleLoader
//    PuzzleLoaderDAT puzzleLoader;
//
//    // 创建Sudoku游戏实例
//    Sudoku game(&consoleIO, &puzzleLoader);
//
//    game.play();
//
//    return 0;
// 
// 
// 
// 
//}


#include <iostream>
#include <vector>
#include <string>


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

int main() {
    testPuzzleLoader();
    return 0;
}




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
