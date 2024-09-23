#include "BasicCommands.h"

/*
9月10日
完成基础指令的执行函数的实现
by lch
9月11日
关于添加数存在bug:不会检查是否合法、冲突
可以添加自动设置唯一候选数的菜单项
*/

// 输入一个数的命令的执行函数实现
void InputNumberCommand::execute()
{
    io->displayMessage("请输入操作：行 列 数字");
    std::vector<int> operation = io->getOperation();
    if (operation.size() == 3) {
        int row = operation[0];
        int col = operation[1];
        int value = operation[2];
        if (!sudoku->setCellValue(row, col, value)) {
            io->displayMessage("无效操作。请重新输入。");
        }
    }
    else {
        io->displayMessage("输入格式错误。请重试。");
    }
}

// 擦去一个数的命令的执行函数实现
void EraseNumberCommand::execute()
{
    io->displayMessage("请输入操作：行 列（擦去对应位置的数）");
    std::vector<int> operation = io->getPosition();
    if (operation.size() == 2) {
        int row = operation[0];
        int col = operation[1];
        if (!sudoku->setCellValue(row, col, 0)) {
            io->displayMessage("无法擦去该位置的数。");
        }
    }
    else {
        io->displayMessage("输入格式错误。请重试。");
    }
}

// 保存游戏的命令的执行函数实现
void SaveGameCommand::execute()
{
    if (sudoku->saveToFile(id)) {
        io->displayMessage("游戏已成功保存！");
    }
    else {
        io->displayMessage("保存失败。");
    }
}

// 输入候选数的命令的执行函数实现
void AddCandidateCommand::execute()
{
    io->displayMessage("请输入操作：行 列 候选数");
    std::vector<int> operation = io->getOperation();
    if (operation.size() == 3) {
        int row = operation[0];
        int col = operation[1];
        int candidate = operation[2];

        // 添加指定位置的候选数
        if (!sudoku->addCellCandidate(row, col, candidate)) {
            io->displayMessage("无法添加该候选数。");
        }
    }
    else {
        io->displayMessage("输入格式错误。请重试。");
    }
}

// 删除候选数的命令的执行函数实现
void RemoveCandidateCommand::execute()
{
    io->displayMessage("请输入操作：行 列 候选数（删除该候选数）");
    std::vector<int> operation = io->getOperation();
    if (operation.size() == 3) {
        int row = operation[0];
        int col = operation[1];
        int candidate = operation[2];

        // 删除指定位置的候选数
        if (!sudoku->removeCellCandidates(row, col, candidate)) {
            io->displayMessage("无法删除该候选数。");
        }
    }
    else {
        io->displayMessage("输入格式错误。请重试。");
    }
}

// 自动补全候选数的命令的执行函数实现
void AutoUpdateCandidatesCommand::execute()
{
    // 获取棋盘
    std::vector<std::vector<Cell>> board = sudoku->getBoard();
    // 遍历数独棋盘中的每个Cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Cell* cell = &board[i][j];

            // 如果这个Cell已经确定了值，则跳过
            if (cell->isSolved()) {
                continue;
            }

            // 对于每个候选值1到9，检查它是否可以存在
            for (int candidate = 1; candidate <= 9; ++candidate) {
                // 如果行、列或块中已经有了这个值，则从候选值中删除
                if (sudoku->getRow(i).hasValue(candidate) ||
                    sudoku->getColumn(j).hasValue(candidate) ||
                    sudoku->getBlock((i / 3) * 3 + j / 3).hasValue(candidate)) {
                    if (!sudoku->removeCellCandidates(i+1, j+1, candidate)) {
                        io->displayMessage("自动补充候选数失败！");
                        return;
                    }
                }
            }
        }
    }
    io->displayMessage("自动补充候选数完成！");
}

// 重置游戏的命令的执行函数实现
void ResetGameCommand::execute()
{
    if (sudoku->reset()) {
        io->displayMessage("游戏已重置！");
    }
    else {
        io->displayMessage("重置失败。");
    }
}

// 退出游戏的命令的执行函数实现
void ExitGameCommand::execute()
{
    io->displayMessage("退出游戏。");
    exit(0);  // 直接退出程序
}


// 自动填充唯一候选数的命令
void AutoSetNumberCommand::execute()
{
    std::vector<std::vector<Cell>> board = sudoku->getBoard();
    // 遍历数独棋盘中的每个Cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Cell* cell = &board[i][j];

            // 如果这个Cell已经确定了值，则跳过
            if (cell->isSolved()) {
                continue;
            }
            int candidate_num = 0, the_candidate = 0;
            // 对于每个候选值1到9，检查它是否可以存在
            for (int candidate = 1; candidate <= 9; ++candidate) {
                if (cell->hasCandidate(candidate)) {
                    candidate_num += 1;
                    the_candidate = candidate;
                }
            }
            if (candidate_num == 1) sudoku->setCellValue(i+1, j+1, the_candidate);
        }
    }
    return;  //自动更新好，返回true
}
