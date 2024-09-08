#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "PuzzleLoader.h"

class PuzzleLoaderDAT : public PuzzleLoader {
public:
    bool loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        std::string line;
        bool puzzleFound = false;
        while (std::getline(file, line)) {
            if (line.find("ID: " + std::to_string(gameID)) != std::string::npos) {
                puzzleFound = true;
                break;
            }
        }

        if (!puzzleFound) {
            std::cerr << "Error: Puzzle with ID " << gameID << " not found." << std::endl;
            return false;
        }

        // 读取难度
        std::getline(file, line);
        if (line.find("Difficulty: ") != std::string::npos) {
            difficulty = line.substr(12);  // 提取难度
        }

        // 跳过 'Board:' 行
        std::getline(file, line);

        // 读取棋盘
        board.resize(9, std::vector<int>(9, 0));
        for (int i = 0; i < 9; ++i) {
            std::getline(file, line);
            std::stringstream ss(line);
            for (int j = 0; j < 9; ++j) {
                ss >> board[i][j];
            }
        }

        return true;
    }

    bool savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty) override {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        file << "ID: " << gameID << std::endl;
        file << "Difficulty: " << difficulty << std::endl;
        file << "Board:" << std::endl;

        for (const auto& row : board) {
            for (int val : row) {
                file << val << " ";
            }
            file << std::endl;
        }

        file << "---" << std::endl;
        return true;
    }
};
