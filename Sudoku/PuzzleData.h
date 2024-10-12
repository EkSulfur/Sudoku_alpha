#ifndef PUZZLE_DATA_H
#define PUZZLE_DATA_H

#include <vector>
#include <string>

// 封装所有与数独棋盘相关的信息到 PuzzleData 类
class PuzzleData {
public:
    std::string filename;
    int gameID;
    std::vector<std::vector<int>> board;
    std::string difficulty;
    int boardSize;  // 棋盘的大小

    // 无参构造函数，默认9x9棋盘
    PuzzleData() : filename("Puzzles.dat"), gameID(1), boardSize(9), difficulty("easy") {
        board.resize(boardSize, std::vector<int>(boardSize, 0));
    }

    // 带有自定义棋盘大小的构造函数
    PuzzleData(int gameID, int boardSize = 9)
        : filename("Puzzles.dat"), gameID(gameID), boardSize(boardSize), difficulty("easy") {
        board.resize(boardSize, std::vector<int>(boardSize, 0));
    }

    // 带有自定义棋盘大小和其他信息的构造函数
    PuzzleData(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty)
        : filename(filename), gameID(gameID), board(board), difficulty(difficulty), boardSize(board.size()) {}
};

#endif // PUZZLE_DATA_H
