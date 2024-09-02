#include "PuzzleLoaderDAT.h"
#include <iostream>
#include <vector>
#include <cassert>

// 测试 loadPuzzle 功能
void testLoadPuzzle() {
    PuzzleLoaderDAT loader;
    std::vector<int> board;
    std::string difficulty;

    // 测试成功加载
    bool result = loader.loadPuzzle("MiniPuzzles.dat", 1, board, difficulty);
    assert(result == true);
    assert(difficulty == "Easy");
    assert(board.size() == 9);
    assert(board[0] == 5);
    assert(board[1] == 3);
    assert(board[4] == 7);

    std::cout << "testLoadPuzzle passed!" << std::endl;

    // 测试加载不存在的ID
    result = loader.loadPuzzle("MiniPuzzles.dat", 3, board, difficulty);
    assert(result == false);

    std::cout << "testLoadPuzzle with invalid ID passed!" << std::endl;

    // 测试加载不存在的文件
    result = loader.loadPuzzle("nonexistent.dat", 1, board, difficulty);
    assert(result == false);

    std::cout << "testLoadPuzzle with nonexistent file passed!" << std::endl;
}

// 测试 savePuzzle 功能
void testSavePuzzle() {
    PuzzleLoaderDAT loader;
    std::vector<int> board = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::string difficulty = "Hard";

    // 测试保存新游戏
    bool result = loader.savePuzzle("MiniPuzzles.dat", 3, board, difficulty);
    assert(result == true);

    // 验证保存后能够成功加载
    std::vector<int> loadedBoard;
    std::string loadedDifficulty;
    result = loader.loadPuzzle("MiniPuzzles.dat", 3, loadedBoard, loadedDifficulty);
    assert(result == true);
    assert(loadedDifficulty == "Hard");
    assert(loadedBoard == board);

    std::cout << "testSavePuzzle passed!" << std::endl;
}

//int main() {
//    // 运行测试
//    testLoadPuzzle();
//    testSavePuzzle();
//
//    return 0;
//}
