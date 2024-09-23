#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "PuzzleLoaderDAT.h"

bool PuzzleLoaderDAT::loadPuzzle(PuzzleData& data) {
    std::ifstream file(data.filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << data.filename << std::endl;
        return false;
    }

    std::string line;
    bool puzzleFound = false;
    while (std::getline(file, line)) {
        // 查找目标ID
        if (line.find("ID: " + std::to_string(data.gameID)) != std::string::npos) {
            puzzleFound = true;
            break;
        }
    }

    if (!puzzleFound) {
        std::cerr << "Error: Puzzle with ID " << data.gameID << " not found." << std::endl;
        return false;
    }

    // 读取难度
    std::getline(file, line);
    if (line.find("Difficulty: ") != std::string::npos) {
        data.difficulty = line.substr(12);  // 提取难度
    }

    // 跳过 'Board:' 行
    std::getline(file, line);

    // 读取棋盘
    data.board.resize(9, std::vector<int>(9, 0));
    for (int i = 0; i < 9; ++i) {
        std::getline(file, line);
        std::stringstream ss(line);
        for (int j = 0; j < 9; ++j) {
            ss >> data.board[i][j];
        }
    }

    return true;
}
bool PuzzleLoaderDAT::savePuzzle(const PuzzleData& data) {
    std::ifstream fileIn(data.filename);
    std::stringstream buffer;
    std::string line;
    bool puzzleFound = false;

    // 读取文件内容到 buffer
    if (fileIn.is_open()) {
        buffer << fileIn.rdbuf();
        fileIn.close();
    }

    // 构建新的数独条目
    std::string newPuzzleEntry;
    newPuzzleEntry += "ID: " + std::to_string(data.gameID) + "\n";
    newPuzzleEntry += "Difficulty: " + data.difficulty + "\n";
    newPuzzleEntry += "Board:\n";
    for (const auto& row : data.board) {
        for (int val : row) {
            newPuzzleEntry += std::to_string(val) + " ";
        }
        newPuzzleEntry += "\n";
    }
    newPuzzleEntry += "---\n";

    // 读取文件内容为字符串
    std::string content = buffer.str();
    std::size_t idPos = content.find("ID: " + std::to_string(data.gameID));

    if (idPos != std::string::npos) {
        // 找到相同的gameID，替换该部分的数独数据
        std::size_t nextPuzzlePos = content.find("ID: ", idPos + 1); // 找到下一个 Puzzle
        if (nextPuzzlePos == std::string::npos) {
            nextPuzzlePos = content.size(); // 如果没有下一个ID, 替换到文件末尾
        }

        // 替换原有数独数据
        content.replace(idPos, nextPuzzlePos - idPos, newPuzzleEntry);
        puzzleFound = true;
    }
    else {
        // 没有找到相同的gameID，追加到文件末尾
        content += newPuzzleEntry;
    }

    // 将更新后的内容写回文件
    std::ofstream fileOut(data.filename);
    if (!fileOut.is_open()) {
        std::cerr << "Error: Could not open file " << data.filename << std::endl;
        return false;
    }
    fileOut << content;
    fileOut.close();

    return true;
}
