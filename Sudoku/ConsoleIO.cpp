#include "ConsoleIO.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void ConsoleIO::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

std::string ConsoleIO::getUserInput() const {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleIO::displayBoard(const std::vector<std::vector<Cell*>>& board) const {
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

int ConsoleIO::displayMenu(const std::vector<std::string>& options) const {
    cout << "\n=============================" << endl;
    cout << "|    请选择一个操作：        |" << endl;

    for (size_t i = 0; i < options.size(); ++i) {
        cout << "|    " << i + 1 << ". " << options[i] << endl;
    }

    cout << "=============================" << endl;

    int choice;
    cin >> choice;
    return choice;
}