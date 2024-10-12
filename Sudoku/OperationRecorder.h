/*
9月30日添加，用于记录必要的操作，以满足撤回操作的功能
因为数独游戏中主要的操作是填数和撤回数，所以目前只考虑记录这两个操作
操作信息以字符串形式保存，第一个数字为操作类型
2代表去除某个数，后面两个跟行、列，最后为去除的数原来是什么（无意义）
1代表添加某个数，后面两个跟行、列、添加的数
*/
#ifndef OPERATION_RECORDER_H
#define OPERATION_RECORDER_H
#include "Sudoku.h"
#include <vector>
#include <string>
class OperationRecorder{
public:
	OperationRecorder(Sudoku* sudoku);
	bool RecordSetValue(int row, int col, int num);
	bool RecordDelValue(int row, int col, int num);
	std::string GetOperationBackward(void);
	std::string GetOperationForward(void);
	bool UpdateOperation(void);
	int getTop(void) const;
	int getSize(void) const;
private:
	Sudoku* sudoku;
	int top;
	std::vector<std::string> operations;
};

#endif