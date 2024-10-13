#include "ConsoleIO.h"
#include "Cell.h"
#include "StateManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ANSI 颜色代码定义
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_YELLOW  "\033[33m"

// 构造函数的定义，初始化成员变量
ConsoleIO::ConsoleIO() : start_time(std::chrono::steady_clock::now()) {}

// 显示消息
void ConsoleIO::displayMessage(const string& message) const{
    cout << message << endl;
}

// 获取用户输入
string ConsoleIO::getUserInput() {
    string input;
    getline(cin, input);
    return input;
}

// 显示棋盘
void ConsoleIO::displayBoard(const vector<vector<Cell>>& board) const {
    cout << "\n" << COLOR_YELLOW << "========================== 当前数独棋盘 ==========================" << COLOR_RESET << "\n";
    int size = static_cast<int>(board.size());

    // 调整列号的对齐
    cout << "     ";  // 留出行号的空格
    for (int i = 0; i < size; ++i) {
        cout << "  C " << i + 1 << "  ";  // 增加空格，保证对齐
    }
    cout << "\n    -----------------------------------------------------------------\n";
    //显示标题和列号：首先打印棋盘的标题和列号
    for (int i = 0; i < size; ++i) {
        for (int sub_row = 0; sub_row < 3; ++sub_row) {
            if (sub_row == 1) {
                cout << "R" << setw(2) << i + 1 << " ";  // 对齐行号
            }
            else {
                cout << "    ";
            }
    //行号显示：在适当的位置打印行号
            for (int j = 0; j < size; ++j) {
                if (1) cout << "|";

                const Cell& cell = board[i][j];

                if (cell.getValue() == 0) {
                    vector<int> candidates = cell.getCandidates();
                    for (int k = sub_row * 3 + 1; k <= sub_row * 3 + 3; ++k) {
                        if (candidates[k]) {
                            cout << setw(2) << k;
                        }
                        else {
                            cout << setw(2) << " ";
                        }
                    }
                }
                else {
                    if (sub_row == 1) {
                        if (cell.isFixed()) {
                            cout << COLOR_GREEN << setw(6) << cell.getValue() << COLOR_RESET;  // 绿色表示固定值
                        }
                        else {
                            cout << COLOR_RED << setw(6) << cell.getValue() << COLOR_RESET;  // 红色表示用户输入值
                        }
                    }
                    else {
                        cout << setw(6) << " ";
                    }
                }
            }
            cout << " |" << endl;
        }
        //棋盘显示逻辑：根据棋盘上的每个Cell对象的状态进行展示。
        if (1) {
            cout << "    -----------------------------------------------------------------\n";
        }
    }
}//隔线：在每行之后输出分隔线，使棋盘显示更加整齐。

// 显示菜单
void ConsoleIO::displayMenu(const vector<string>& options) {

    cursor.saveCursorPosition();
    int x_offset = 90;
    int current_y = 16;

    // 移动光标到合适的位置，然后开始输出菜单
    cursor.setCursorPosition(x_offset, current_y++);
    cout << COLOR_YELLOW << "==============================";
    cursor.setCursorPosition(x_offset, current_y++);
    cout << "     请选择一个操作：         ";

    for (size_t i = 0; i < options.size(); ++i) {
        cursor.setCursorPosition(x_offset, current_y++);
        cout << "     " << i + 1 << ". " << options[i];
    }
    cursor.setCursorPosition(x_offset, current_y++);
    cout << "==============================" << COLOR_RESET;

    // 恢复到原来的光标位置
    cursor.resumeCursorPosition();
    return;
}

void ConsoleIO::startGame(){
    this->displayMessage(COLOR_GREEN "游戏开始！祝你好运！" COLOR_RESET);

}

// 显示游戏信息
void ConsoleIO::displayInfo(const int id, const string difficulty) {
    cout << COLOR_YELLOW << "当前游戏难度: " << difficulty << endl;
    cout << "用户ID: " << id << COLOR_RESET << endl;
}


// 新的显示游戏信息函数
void ConsoleIO::displayInfo(PuzzleData puzzleData){

    const int id = puzzleData.gameID;
    const string difficulty = puzzleData.difficulty;

    cursor.saveCursorPosition();
    int x_offset = 90;
    int current_y = 10; 
    cursor.setCursorPosition(x_offset, current_y++);
    cout << COLOR_YELLOW << "当前游戏难度: " << difficulty;
    cursor.setCursorPosition(x_offset, current_y++);
    cout << "用户ID: " << id << COLOR_RESET;
    cout << COLOR_BLUE;
    cursor.setCursorPosition(x_offset, current_y++);
    StateManager::getInstance().timer.displayTime();
    cursor.setCursorPosition(x_offset, current_y++);
    StateManager::getInstance().counter.displayCount();
    cout << COLOR_RESET;
    cursor.resumeCursorPosition();
}

// 获取用户操作
vector<int> ConsoleIO::getOperation() {
    vector<int> operation;
    int row, col, num;

    cout << COLOR_YELLOW "请输入你要填入的行 (1-9): " COLOR_RESET;
    while (!(cin >> row) || row < 1 || row > 9) {
        cout << COLOR_RED "无效输入，请输入正确的行号 (1-9): " COLOR_RESET;
        cin.clear();//用于清除cin的错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//跳过并丢弃当前行中剩下的非法输入，防止程序再次读取错误数据。
    }

    cout << COLOR_YELLOW "请输入你要填入的列 (1-9): " COLOR_RESET;
    while (!(cin >> col) || col < 1 || col > 9) {
        cout << COLOR_RED "无效输入，请输入正确的列号 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << COLOR_YELLOW "请输入你要填入的数字 (1-9): " COLOR_RESET;
    while (!(cin >> num) || num < 1 || num > 9) {
        cout << COLOR_RED "无效输入，请输入正确的数字 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    operation.push_back(row);
    operation.push_back(col);
    operation.push_back(num);

    return operation;
}

// 获取用户输入的位置
vector<int> ConsoleIO::getPosition() {
    vector<int> operation;
    int row, col;

    cout << COLOR_YELLOW "请输入你要填入的行 (1-9): " COLOR_RESET;
    while (!(cin >> row) || row < 1 || row > 9) {
        cout << COLOR_RED "无效输入，请输入正确的行号 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << COLOR_YELLOW "请输入你要填入的列 (1-9): " COLOR_RESET;
    while (!(cin >> col) || col < 1 || col > 9) {
        cout << COLOR_RED "无效输入，请输入正确的列号 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    operation.push_back(row);
    operation.push_back(col);
    return operation;
}

// 获取用户输入的数字
int ConsoleIO::getNumber() {
    int num;

    cout << COLOR_YELLOW "请输入你要填入的数字 (1-9): " COLOR_RESET;
    while (!(cin >> num) || num < 1 || num > 9) {
        cout << COLOR_RED "无效输入，请输入正确的数字 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    return num;
}
