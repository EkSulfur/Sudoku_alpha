#include "OperationRecorder.h"

// 初始化函数
OperationRecorder::OperationRecorder(Sudoku* sudoku):sudoku(sudoku)
{
	top = 0;
}

// 记录设置值的函数
// 注意此处row, col都是从1开始
bool OperationRecorder::RecordSetValue(int row, int col, int num)
{
	// 检查操作是否合法
	if (row < 1 || row > 9) return false;
	if (col < 1 || col > 9) return false;
	if (num < 1 || num > 9) return false;
	int op_code = 1000 + row * 100 + col * 10 + num;
	operations.push_back(std::to_string(op_code));
	top += 1;
	return true;
}

// 记录删除值的函数
// 注意此处row, col都是从1开始
bool OperationRecorder::RecordDelValue(int row, int col, int num)
{
	// 检查操作是否合法
	if (row < 1 || row > 9) return false;
	if (col < 1 || col > 9) return false;
	if (num < 1 || num > 9) return false;
	int op_code = 2000 + row * 100 + col * 10 + num;
	operations.push_back(std::to_string(op_code));
	top += 1;
	return true;
}

std::string OperationRecorder::GetLastOperation(void)
{
	top -= 1;
	return operations[top];
}

bool OperationRecorder::UpdateOperation(void)
{
	try {
		// 删除top之后的操作记录
		while (operations.size() > top) {
			operations.pop_back();
		}
	}
	catch (...) {
		return false;
	}
	return true;
}