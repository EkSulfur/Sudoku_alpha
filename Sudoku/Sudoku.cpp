#include "Sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

void Sudoku::play()
{
	// ѡ��id����
	// ��Ĭ��idΪ1
	/*
	��Ϸ�������̣�
	�ȶ�ȡid �ټ������̣���ʼ��Ϸ
	��ȥid������ݣ�����ʵ��
	*/
	int id = 1;
	std::vector<std::vector<int>> board;
	puzzleLoader->loadPuzzle("Puzzles.dat", id, board, difficulty);  //����������Ϣ
}
