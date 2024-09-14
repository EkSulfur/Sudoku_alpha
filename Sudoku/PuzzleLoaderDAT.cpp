#include "PuzzleLoaderDAT.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

// 加载数独棋盘
bool PuzzleLoaderDAT::loadPuzzle(const std::string& filename, int gameID,
    std::vector<std::vector<int>>& board, std::string& difficulty) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return false;
    }

    std::string line;
    bool puzzleFound = false;

    // 查找对应ID的数独数据
    while (std::getline(file, line)) {
        if (line.find("ID: " + std::to_string(gameID)) != std::string::npos) {
            puzzleFound = true;
            break;
        }
    }

    if (!puzzleFound) {
        std::cerr << "错误：未找到ID为 " << gameID << " 的数独。" << std::endl;
        return false;
    }

    // 读取难度
    if (!std::getline(file, line) || line.find("Difficulty: ") == std::string::npos) {
        std::cerr << "错误：无法读取难度信息。" << std::endl;
        return false;
    }
    difficulty = line.substr(12);  // 提取难度信息

    // 跳过 'Board:' 行
    if (!std::getline(file, line) || line != "Board:") {
        std::cerr << "错误：数独棋盘格式不正确，缺少 'Board:' 行。" << std::endl;
        return false;
    }

    // 读取数独棋盘
    board.resize(9, std::vector<int>(9, 0));
    for (int i = 0; i < 9; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "错误：数独棋盘数据不完整。" << std::endl;
            return false;
        }
        std::stringstream ss(line);
        for (int j = 0; j < 9; ++j) {
            if (!(ss >> board[i][j])) {
                std::cerr << "错误：读取数独棋盘时发生错误。" << std::endl;
                return false;
            }
        }
    }

    return true;
}

// 保存数独棋盘
bool PuzzleLoaderDAT::savePuzzle(const std::string& filename, int gameID,
    const std::vector<std::vector<int>>& board, const std::string& difficulty) {
    std::ifstream fileIn(filename);
    std::stringstream buffer;
    std::string content;
    bool puzzleFound = false;

    // 读取文件内容到 buffer
    if (fileIn.is_open()) {
        buffer << fileIn.rdbuf();
        fileIn.close();
        content = buffer.str();
    }

    // 构建新的数独内容
    std::string newPuzzleEntry;
    newPuzzleEntry += "ID: " + std::to_string(gameID) + "\n";
    newPuzzleEntry += "Difficulty: " + difficulty + "\n";
    newPuzzleEntry += "Board:\n";
    for (const auto& row : board) {
        for (int val : row) {
            newPuzzleEntry += std::to_string(val) + " ";
        }
        newPuzzleEntry += "\n";
    }
    newPuzzleEntry += "---\n";

    // 查找并替换或追加数独数据
    std::size_t idPos = content.find("ID: " + std::to_string(gameID));
    if (idPos != std::string::npos) {
        // 找到相同的ID并替换该部分数独数据
        std::size_t nextPuzzlePos = content.find("ID: ", idPos + 1);
        if (nextPuzzlePos == std::string::npos) {
            nextPuzzlePos = content.size();
        }
        content.replace(idPos, nextPuzzlePos - idPos, newPuzzleEntry);
    }
    else {
        // 如果未找到，追加新数独到文件末尾
        content += newPuzzleEntry;
    }

    // 将修改后的内容写回文件
    std::ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return false;
    }
    fileOut << content;
    fileOut.close();

    return true;
}

// 加载候选数
// 加载候选数
bool PuzzleLoaderDAT::loadCandidates(const std::string& filename, int gameID,
    std::map<std::pair<int, int>, std::vector<int>>& candidates) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开候选数文件 " << filename << std::endl;
        return false;
    }

    std::string line;
    bool puzzleFound = false;

    // 查找候选数部分
    while (std::getline(file, line)) {
        if (line.find("ID_" + std::to_string(gameID)) != std::string::npos) {
            puzzleFound = true;
            break;
        }
    }

    if (!puzzleFound) {
        std::cerr << "错误：未找到ID为 " << gameID << " 的候选数。" << std::endl;
        return false;
    }

    // 读取候选数数据
    while (std::getline(file, line)) {
        if (line.find("---") != std::string::npos) {
            break; // 结束候选数部分
        }

        std::stringstream ss(line);
        char leftParen, rightParen, comma1;
        int row, col;
        std::string candidateStr;

        // 解析 (row, col)
        if (!(ss >> leftParen >> row >> comma1 >> col >> rightParen)) {
            std::cerr << "错误：解析行和列时失败：" << line << std::endl;
            continue;
        }

        // 检查预期的字符
        if (leftParen != '(' || comma1 != ',' || rightParen != ')') {
            std::cerr << "错误：候选数行格式无效：" << line << std::endl;
            continue;
        }

        // 跳过右括号后的逗号和空白
        ss >> std::ws; // 跳过空白
        if (ss.peek() == ',') {
            ss.get(); // 读取逗号
        }
        ss >> std::ws; // 跳过额外的空白

        // 读取剩余的候选数字符串
        ss >> std::ws; // 跳过空白
        std::getline(ss, candidateStr);

        // 去除可能的前导空白
        candidateStr.erase(0, candidateStr.find_first_not_of(" \t"));

        // 检查候选数字符串格式
        if (candidateStr.empty() || candidateStr.front() != '[' || candidateStr.back() != ']') {
            std::cerr << "错误：候选数格式无效：" << candidateStr << std::endl;
            continue;
        }

        // 去掉方括号
        candidateStr = candidateStr.substr(1, candidateStr.size() - 2);

        std::vector<int> candidateList;
        std::stringstream candidateStream(candidateStr);
        int candidate;

        // 解析候选数字
        while (candidateStream >> candidate) {
            candidateList.push_back(candidate);
            if (candidateStream.peek() == ',') {
                candidateStream.ignore();
            }
        }

        // 存储到候选数映射中
        candidates[std::make_pair(row - 1, col - 1)] = candidateList;
    }

    return true;
}


// 保存候选数
bool PuzzleLoaderDAT::saveCandidates(const std::string& filename, int gameID,
    const std::map<std::pair<int, int>, std::vector<int>>& candidates) {
    std::ifstream fileIn(filename);
    std::stringstream buffer;
    std::string content;

    // 读取文件内容到 buffer
    if (fileIn.is_open()) {
        buffer << fileIn.rdbuf();
        fileIn.close();
        content = buffer.str();
    }

    // 构建新的候选数部分
    std::string newCandidateEntry;
    newCandidateEntry += "ID_" + std::to_string(gameID) + "\n";
    for (const auto& candidate : candidates) {
        newCandidateEntry += "(" + std::to_string(candidate.first.first + 1) + ", "
            + std::to_string(candidate.first.second + 1) + "),[";
        for (size_t i = 0; i < candidate.second.size(); ++i) {
            newCandidateEntry += std::to_string(candidate.second[i]);
            if (i != candidate.second.size() - 1) {
                newCandidateEntry += ", ";
            }
        }
        newCandidateEntry += "]\n";
    }
    newCandidateEntry += "---\n";

    // 查找并替换或追加候选数数据
    std::size_t idPos = content.find("ID_" + std::to_string(gameID));
    if (idPos != std::string::npos) {
        std::size_t nextCandidatePos = content.find("ID_", idPos + 1);
        if (nextCandidatePos == std::string::npos) {
            nextCandidatePos = content.size();
        }
        // 替换现有的候选数条目
        content.replace(idPos, nextCandidatePos - idPos, newCandidateEntry);
    }
    else {
        // 如果未找到，追加新的候选数到文件末尾
        content += newCandidateEntry;
    }

    // 将修改后的内容写回文件
    std::ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return false;
    }
    fileOut << content;
    fileOut.close();

    return true;
}
