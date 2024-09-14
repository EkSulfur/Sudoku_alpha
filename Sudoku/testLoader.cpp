#include "PuzzleLoaderDAT.h"
#include <iostream>
#include <map>
#include <vector>
#include <exception>

// 测试读取数独棋盘
void testLoadPuzzle() {
    try {
        PuzzleLoaderDAT loader;
        std::vector<std::vector<int>> board;
        std::string difficulty;

        if (loader.loadPuzzle("puzzles.dat", 1, board, difficulty)) {
            std::cout << "成功加载数独棋盘！\n";
            std::cout << "难度：" << difficulty << "\n";
            std::cout << "棋盘：\n";
            for (const auto& row : board) {
                for (int num : row) {
                    std::cout << num << " ";
                }
                std::cout << "\n";
            }
        }
        else {
            std::cerr << "加载数独棋盘失败。请检查 puzzles.dat 是否存在且格式正确。\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "加载数独棋盘时发生错误：" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "加载数独棋盘时发生未知错误。" << std::endl;
    }
}

// 测试保存数独棋盘
void testSavePuzzle() {
    try {
        PuzzleLoaderDAT loader;
        std::vector<std::vector<int>> board = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
        std::string difficulty = "中等";

        if (loader.savePuzzle("puzzles.dat", 1, board, difficulty)) {
            std::cout << "成功保存数独棋盘！\n";
        }
        else {
            std::cerr << "保存数独棋盘失败。\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "保存数独棋盘时发生错误：" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "保存数独棋盘时发生未知错误。" << std::endl;
    }
}

// 测试读取候选数
void testLoadCandidates() {
    try {
        PuzzleLoaderDAT loader;
        std::map<std::pair<int, int>, std::vector<int>> candidates;

        if (loader.loadCandidates("puzzles.hx.dat", 1, candidates)) {
            std::cout << "成功加载候选数！\n";
            for (const auto& candidate : candidates) {
                std::cout << "(" << candidate.first.first + 1 << ", "
                    << candidate.first.second + 1 << "): [";
                for (size_t i = 0; i < candidate.second.size(); ++i) {
                    std::cout << candidate.second[i];
                    if (i != candidate.second.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << "]\n";
            }
        }
        else {
            std::cerr << "加载候选数失败。请检查 puzzles.hx.dat 是否存在且格式正确。\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "加载候选数时发生错误：" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "加载候选数时发生未知错误。" << std::endl;
    }
}

// 测试保存候选数
void testSaveCandidates() {
    try {
        PuzzleLoaderDAT loader;
        std::map<std::pair<int, int>, std::vector<int>> candidates = {
            {{1, 3}, {2, 4, 7}},
            {{2, 4}, {3, 5}},
            {{4, 5}, {1, 6}}
        };

        if (loader.saveCandidates("puzzles.hx.dat", 1, candidates)) {
            std::cout << "成功保存候选数！\n";
        }
        else {
            std::cerr << "保存候选数失败。\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "保存候选数时发生错误：" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "保存候选数时发生未知错误。" << std::endl;
    }
}

int main() {
    std::cout << "测试保存数独棋盘：\n";
    testSavePuzzle();

    std::cout << "\n测试加载数独棋盘：\n";
    testLoadPuzzle();

    std::cout << "\n测试保存候选数：\n";
    testSaveCandidates();

    std::cout << "\n测试加载候选数：\n";
    testLoadCandidates();

    return 0;
}
