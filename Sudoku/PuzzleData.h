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

    // 无参构造函数
    PuzzleData() { gameID = 1;} // 设置默认id，这里应该无关紧要（后续会修改）

    // 构造函数，不需要日期和玩家ID
    PuzzleData(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty)
        : filename(filename), gameID(gameID), board(board), difficulty(difficulty) {}

    // 默认构造函数（可以选择性启用扩展字段）
    PuzzleData(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board)
        : filename("Puzzles.dat"), gameID(gameID), board(board), difficulty("easy") {}

    PuzzleData(int gameID)
        : filename("Puzzles.dat"), gameID(gameID), difficulty("easy") {}
};
#endif // PUZZLE_DATA_H