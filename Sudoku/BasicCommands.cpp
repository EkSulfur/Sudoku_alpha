#include "BasicCommands.h"

/*
9月10日
完成基础指令的执行函数的实现
by lch
9月11日
关于添加数存在bug:不会检查是否合法、冲突
可以添加自动设置唯一候选数的菜单项
国庆前一次课
添加返回、撤销返回命令
10月7日
修改退出游戏逻辑，从直接exit修改为将isRunning设置为0
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
        operationRecorder->RecordSetValue(row, col, value);
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
        int origin = sudoku->getBoard()[row - 1][col - 1].getValue();
        if (!sudoku->setCellValue(row, col, 0)) {
            io->displayMessage("无法擦去该位置的数。");
        }
        operationRecorder->RecordDelValue(row, col, origin);
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
    *isRunning = false;
    return;
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
            // operationRecorder->RecordSetValue(i, j, the_candidate);
        }
    }
    return;  //自动更新好，返回true
}

void BackCommand::execute()
{
    // 判断栈是否为空
    if (operationRecorder->getTop() == 0) {
        io->displayMessage("不存在上一个操作");
    }
    // 解析上一步和填数、删除有关的操作
    int op_num = atoi(operationRecorder->GetOperationBackward().c_str());
    int operation = (op_num / 1000) % 10;
    int row = (op_num / 100) % 10;
    int col = (op_num / 10) % 10;
    int value = op_num % 10;
    switch (operation)
    {
    case 1:
        // 上一步为添加某个数的情况
        if (!sudoku->setCellValue(row, col, 0)) {
            io->displayMessage("返回失败");
        }
        // 对应操作为撤销那个数
        break;
    case 2:
        // 上一步为去除某个数的情况
        if (!sudoku->setCellValue(row, col, value)) {
            io->displayMessage("返回失败");
        }
        // 对应操作为恢复这个数
        break;
    default:
        io->displayMessage("错误：未经行任何操作");
        break;
    }
}

void RevokeBackCommand::execute()
{
    // 判断top是否指向最上面的元素
    if (operationRecorder->getTop() >= operationRecorder->getSize()) {
        io->displayMessage("不存在下一个操作");
        return;
    }
    // 解析上一步和填数、删除有关的操作
    int op_num = atoi(operationRecorder->GetOperationForward().c_str());
    int operation = (op_num / 1000) % 10;
    int row = (op_num / 100) % 10;
    int col = (op_num / 10) % 10;
    int value = op_num % 10;
    switch (operation)
    {
    case 1:
        // 上一步为添加某个数的情况
        if (!sudoku->setCellValue(row, col, value)) {
            io->displayMessage("返回失败");
        }
        // 对应操作为恢复那个数
        break;
    case 2:
        // 上一步为去除某个数的情况
        if (!sudoku->setCellValue(row, col, 0)) {
            io->displayMessage("返回失败");
        }
        // 对应操作为去除这个数
        break;
    default:
        io->displayMessage("错误：未经行任何操作");
        break;
    }
}
