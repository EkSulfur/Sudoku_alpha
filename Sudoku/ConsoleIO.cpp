#include "ConsoleIO.h"
#include "Cell.h"
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
ConsoleIO::ConsoleIO() : start_time(std::chrono::steady_clock::now()), move_count(0) {}

// 初始化计时器和步数统计
void ConsoleIO::startGame() {
    start_time = std::chrono::steady_clock::now();  // 记录游戏开始时间
    move_count = 0;                    // 重置操作次数
    displayMessage(COLOR_GREEN "游戏开始！祝你好运！" COLOR_RESET);
}

// 增加步数统计
void ConsoleIO::incrementMoveCount() {
    move_count++;
}

// 显示当前时间和步数
void ConsoleIO::displayTimeAndMoves() {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

    int minutes = static_cast<int>(elapsed_seconds / 60);
    int seconds = static_cast<int>(elapsed_seconds % 60);

    cout << COLOR_BLUE << "\n时间已用: " << minutes << " 分 " << seconds << " 秒";
    cout << "\n步数: " << move_count << COLOR_RESET << endl;
}

// 显示消息
void ConsoleIO::displayMessage(const string& message) {
    cout << message << endl;
}

// 获取用户输入
string ConsoleIO::getUserInput() {
    string input;
    getline(cin, input);
    return input;
}

// 显示棋盘并显示时间和步数
void ConsoleIO::displayBoard(const vector<vector<Cell>>& board) {
    displayTimeAndMoves();  // 显示时间和步数

    cout << "\n" << COLOR_YELLOW << "========================== 当前数独棋盘 ==========================" << COLOR_RESET << "\n";
    int size = static_cast<int>(board.size());

    // 调整列号的对齐
    cout << "     ";  // 留出行号的空格
    for (int i = 0; i < size; ++i) {
        cout << "  C " << i + 1 << "  ";  // 增加空格，保证对齐
    }
    cout << "\n    -----------------------------------------------------------------\n";

    for (int i = 0; i < size; ++i) {
        for (int sub_row = 0; sub_row < 3; ++sub_row) {
            if (sub_row == 1) {
                cout << "R" << setw(2) << i + 1 << " ";  // 对齐行号
            }
            else {
                cout << "    ";
            }

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

        if (1) {
            cout << "    -----------------------------------------------------------------\n";
        }
    }
}

// 显示菜单
int ConsoleIO::displayMenu(const vector<string>& options) {
    displayTimeAndMoves();  // 显示时间和步数

    cout << COLOR_YELLOW << "\n=============================" << endl;
    cout << "|    请选择一个操作：        |" << endl;

    for (size_t i = 0; i < options.size(); ++i) {
        cout << "|    " << i + 1 << ". " << options[i] << endl;
    }

    cout << "=============================" << COLOR_RESET << endl;

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        cout << COLOR_RED "无效输入，请选择正确的选项: " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// 显示游戏信息
void ConsoleIO::displayInfo(const int id, const string difficulty) {
    cout << COLOR_YELLOW << "当前游戏难度: " << difficulty << endl;
    cout << "用户ID: " << id << COLOR_RESET << endl;
}

// 获取用户操作
vector<int> ConsoleIO::getOperation() {
    vector<int> operation;
    int row, col, num;

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

    cout << COLOR_YELLOW "请输入你要填入的数字 (1-9): " COLOR_RESET;
    while (!(cin >> num) || num < 1 || num > 9) {
        cout << COLOR_RED "无效输入，请输入正确的数字 (1-9): " COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    incrementMoveCount();

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

    incrementMoveCount();

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

    incrementMoveCount();

    return num;
}
