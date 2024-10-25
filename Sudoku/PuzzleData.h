#ifndef PUZZLE_DATA_H
#define PUZZLE_DATA_H

#include <vector>
#include <string>


// 封装所有与数独棋盘相关的信息到 PuzzleData 类
struct PuzzleData {
public:
    std::string filename = "Puzzles.dat";  // 设置缺省的文件名
    int gameID;
    std::vector<std::vector<int>> board;
    std::string difficulty;
    // 由于实现了单例模式的StateManager中有Timer和Counter，将二者从此处移除
    // 把PuzzleData从class改为结构体，移除所有没用的构造函数
};
#endif // PUZZLE_DATA_H