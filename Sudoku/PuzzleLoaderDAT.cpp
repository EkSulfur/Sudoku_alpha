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

    // ��ȡ�Ѷ�
    std::getline(file, line);
    if (line.find("Difficulty: ") != std::string::npos) {
        difficulty = line.substr(12);  // ��ȡ�Ѷ�
    }

    // ���� 'Board:' ��
    std::getline(file, line);

    // ��ȡ����
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

    // ��ȡ�ļ����ݵ� buffer
    if (fileIn.is_open()) {
        buffer << fileIn.rdbuf();
        fileIn.close();
    }

    // ����Ҫ��������������ݣ�����δȷ��������ʹ��0��ʾ
    std::string newPuzzleEntry;
    newPuzzleEntry += "ID: " + std::to_string(gameID) + "\n";
    newPuzzleEntry += "Difficulty: " + difficulty + "\n";
    newPuzzleEntry += "Board:\n";
    for (const auto& row : board) {
        for (int val : row) {
            newPuzzleEntry += std::to_string(val) + " ";  // ����ҵ�״̬����
        }
        newPuzzleEntry += "\n";
    }
    newPuzzleEntry += "---\n";

    std::string content = buffer.str();
    std::size_t idPos = content.find("ID: " + std::to_string(gameID));

    if (idPos != std::string::npos) {
        // �ҵ�����ͬ�� gameID���滻�ⲿ�ֵ���������
        std::size_t nextPuzzlePos = content.find("ID: ", idPos + 1); // �ҵ���һ�� Puzzle
        if (nextPuzzlePos == std::string::npos) {
            // ���û����һ�� Puzzle���滻���ļ�ĩβ
            nextPuzzlePos = content.size();
        }

        // �滻ԭ�е�����
        content.replace(idPos, nextPuzzlePos - idPos, newPuzzleEntry);
        puzzleFound = true;
    }
    else {
        // û���ҵ���ͬ�� gameID��׷�����������ļ�ĩβ
        content += newPuzzleEntry;
    }

    // ���޸ĺ������д���ļ�
    std::ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    fileOut << content;
    fileOut.close();

    return true;
}
