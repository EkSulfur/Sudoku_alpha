#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "PuzzleLoaderDAT.h"

bool PuzzleLoaderDAT::loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty){
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

bool PuzzleLoaderDAT::savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty){
    std::ifstream fileIn(filename);
    std::stringstream buffer;
    bool puzzleFound = false;
    std::string line;

    // 读取文件内容到 buffer
    if (fileIn.is_open()) {
        buffer << fileIn.rdbuf();
        fileIn.close();
    }

    // 构建要保存的新数独数据，其中未确定的数字使用0表示
    std::string newPuzzleEntry;
    newPuzzleEntry += "ID: " + std::to_string(gameID) + "\n";
    newPuzzleEntry += "Difficulty: " + difficulty + "\n";
    newPuzzleEntry += "Board:\n";
    for (const auto& row : board) {
        for (int val : row) {
            newPuzzleEntry += std::to_string(val) + " ";  // 将玩家的状态保存
        }
        newPuzzleEntry += "\n";
    }
    newPuzzleEntry += "---\n";

    std::string content = buffer.str();
    std::size_t idPos = content.find("ID: " + std::to_string(gameID));

    if (idPos != std::string::npos) {
        // 找到了相同的 gameID，替换这部分的数独数据
        std::size_t nextPuzzlePos = content.find("ID: ", idPos + 1); // 找到下一个 Puzzle
        if (nextPuzzlePos == std::string::npos) {
            // 如果没有下一个 Puzzle，替换到文件末尾
            nextPuzzlePos = content.size();
        }

        // 替换原有的数独
        content.replace(idPos, nextPuzzlePos - idPos, newPuzzleEntry);
        puzzleFound = true;
    }
    else {
        // 没有找到相同的 gameID，追加新数独到文件末尾
        content += newPuzzleEntry;
    }

    // 将修改后的内容写回文件
    std::ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    fileOut << content;
    fileOut.close();

    return true;
}
