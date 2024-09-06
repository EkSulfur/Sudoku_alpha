#include "PuzzleLoaderDAT.h"
#include <iostream>
#include <sstream>

bool PuzzleLoaderDAT::loadPuzzle(const std::string& filename, std::vector<std::vector<int>>& board, std::string& difficulty) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    board.resize(9, std::vector<int>(9, 0));  // 初始化9x9矩阵

    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        if (line.find("Difficulty:") != std::string::npos) {
            difficulty = line.substr(11);  // 解析难度
        }
        else if (row < 9) {
            std::stringstream ss(line);
            for (int col = 0; col < 9; ++col) {
                ss >> board[row][col];
            }
            ++row;
        }
    }

    file.close();
    return true;
}

bool PuzzleLoaderDAT::savePuzzle(const std::string& filename, const std::vector<std::vector<int>>& board, const std::string& difficulty) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    file << "Difficulty: " << difficulty << std::endl;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            file << board[row][col] << " ";
        }
        file << std::endl;
    }

    file.close();
    return true;
}
