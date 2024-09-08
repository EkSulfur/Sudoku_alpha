#include "ConsoleIO.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void ConsoleIO::displayMessage(const string& message) const {
    cout << message << endl;
}

string ConsoleIO::getUserInput() const {
    string input;
    getline(cin, input);
    return input;
}

void ConsoleIO::displayBoard(const vector<vector<Cell*>>& board) const {
    cout << "\n 当前数独棋盘: \n";
    int size = board.size(); // 棋盘大小，通常是 9

    // 打印顶部分隔线
    cout << " -------------------------\n";

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // 打印行的分隔线
            if (j % 3 == 0) cout << " | ";

            if (board[i][j]->getValue() == 0)
                cout << ". ";  // 显示空位为点
            else
                cout << board[i][j]->getValue() << " ";
        }
        cout << "|";  // 行尾加上分隔符
        cout << endl;

        // 每 3 行后打印一次分隔线
        if ((i + 1) % 3 == 0) {
            cout << " -------------------------\n";
        }
    }
}

int ConsoleIO::displayMenu(const vector<string>& options) const {
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

void ConsoleIO::displayInfo(const int id, const string difficulty) const {
    cout << "当前游戏难度: " << difficulty << endl;
    cout << "用户ID: " << id << endl;
    cout << "你可以进行以下操作: " << endl;
    cout << "1. 填入数字" << endl;
    cout << "2. 查看当前状态" << endl;
    cout << "3. 退出游戏" << endl;
}

vector<int> ConsoleIO::getOperation() const {
    vector<int> operation;
    int command;

    cout << "请输入你要进行的操作（1: 填数, 2: 查看状态, 3: 退出游戏）: ";
    while (!(cin >> command) || (command < 1 || command > 3)) {
        cout << "无效输入，请输入数字（1, 2 或 3）: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除错误输入
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清理换行符

    if (command == 1) {
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

        operation.push_back(1); // 1 代表填数操作
        operation.push_back(row);
        operation.push_back(col);
        operation.push_back(num);
    }
    else if (command == 2) {
        operation.push_back(2); // 2 代表查看状态操作
    }
    else if (command == 3) {
        operation.push_back(3); // 3 代表退出游戏操作
    }

    return operation;
}
