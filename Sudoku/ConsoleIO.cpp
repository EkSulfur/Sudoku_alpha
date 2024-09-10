#include "ConsoleIO.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

/*
9月8日
完成ConsoleIO类
by lwh
添加getPosition和getNumber函数，拆分getOperation原有的功能
实际上getNumber好像没啥用，getPosition是为了适应去除该位置之前填入的数的功能
9月10日
目前需要完成的任务：
理解Sudoku.cpp中的play函数，使用的Command Pattern
区分是否fixed的cell的数的颜色
显示候选数
在数独中显示行、列
美化界面（次要）
by lch
*/

using namespace std;

void ConsoleIO::displayMessage(const string& message) {
    cout << message << endl;
}

string ConsoleIO::getUserInput() {
    string input;
    getline(cin, input);
    return input;
}

void ConsoleIO::displayBoard(const vector<vector<Cell>>& board) {
    cout << "\n 当前数独棋盘: \n";
    int size = board.size(); // 棋盘大小，通常是 9

    // 打印顶部分隔线
    cout << " -------------------------\n";

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // 打印行的分隔线
            if (j % 3 == 0) cout << " | ";

            if (board[i][j].getValue() == 0)
                cout << ". ";  // 显示空位为点
            else
                cout << board[i][j].getValue() << " ";
        }
        cout << "|";  // 行尾加上分隔符
        cout << endl;

        // 每 3 行后打印一次分隔线
        if ((i + 1) % 3 == 0) {
            cout << " -------------------------\n";
        }
    }
}

int ConsoleIO::displayMenu(const vector<string>& options) {
    cout << "\n=============================" << endl;
    cout << "|    请选择一个操作：        |" << endl;

    for (size_t i = 0; i < options.size(); ++i) {
        cout << "|    " << i + 1 << ". " << options[i] << endl;
    }

    cout << "=============================" << endl;

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        cout << "无效输入，请选择正确的选项: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除错误输入
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清理换行符
    return choice;
}

void ConsoleIO::displayInfo(const int id, const string difficulty) {
    cout << "当前游戏难度: " << difficulty << endl;
    cout << "用户ID: " << id << endl;
    cout << "你可以进行以下操作: " << endl;
    cout << "1. 填入数字" << endl;
    cout << "2. 查看当前状态" << endl;
    cout << "3. 退出游戏" << endl;
}

vector<int> ConsoleIO::getOperation() {
    vector<int> operation;
    // 9月8日 修复冗余的代码和输出 by lch
    int row, col, num;
    cout << "请输入你要填入的行 (1-9): ";
    while (!(cin >> row) || row < 1 || row > 9) {
        cout << "无效输入，请输入正确的行号 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入你要填入的列 (1-9): ";
    while (!(cin >> col) || col < 1 || col > 9) {
        cout << "无效输入，请输入正确的列号 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入你要填入的数字 (1-9): ";
    while (!(cin >> num) || num < 1 || num > 9) {
        cout << "无效输入，请输入正确的数字 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //operation.push_back(1); // 1 代表填数操作
    operation.push_back(row);
    operation.push_back(col);
    operation.push_back(num);

    return operation;
}

vector<int> ConsoleIO::getPosition() {
    vector<int> operation;
    int row, col;
    cout << "请输入你要填入的行 (1-9): ";
    while (!(cin >> row) || row < 1 || row > 9) {
        cout << "无效输入，请输入正确的行号 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入你要填入的列 (1-9): ";
    while (!(cin >> col) || col < 1 || col > 9) {
        cout << "无效输入，请输入正确的列号 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    operation.push_back(row);
    operation.push_back(col);
    return operation;
}

int ConsoleIO::getNumber()
{
    int num;
    cout << "请输入你要填入的数字 (1-9): ";
    while (!(cin >> num) || num < 1 || num > 9) {
        cout << "无效输入，请输入正确的数字 (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return num;
}
