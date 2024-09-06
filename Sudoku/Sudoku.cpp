#include "Sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

void Sudoku::play()
{
	// 选择id操作
	// 先默认id为1
	/*
	游戏加载流程：
	先读取id 再加载棋盘，开始游戏
	略去id相关内容，后续实现
	*/
	int id = 1;
	std::vector<std::vector<int>> board;
	puzzleLoader->loadPuzzle("Puzzles.dat", id, board, difficulty);  //加载棋盘信息
}
