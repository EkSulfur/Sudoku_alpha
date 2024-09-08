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
    cout << "\n ��ǰ��������: \n";
    int size = board.size(); // ���̴�С��ͨ���� 9

    // ��ӡ�����ָ���
    cout << " -------------------------\n";

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // ��ӡ�еķָ���
            if (j % 3 == 0) cout << " | ";

            if (board[i][j]->getValue() == 0)
                cout << ". ";  // ��ʾ��λΪ��
            else
                cout << board[i][j]->getValue() << " ";
        }
        cout << "|";  // ��β���Ϸָ���
        cout << endl;

        // ÿ 3 �к��ӡһ�ηָ���
        if ((i + 1) % 3 == 0) {
            cout << " -------------------------\n";
        }
    }
}

int ConsoleIO::displayMenu(const std::vector<std::string>& options) const {
    cout << "\n=============================" << endl;
    cout << "|    ��ѡ��һ��������        |" << endl;

    for (size_t i = 0; i < options.size(); ++i) {
        cout << "|    " << i + 1 << ". " << options[i] << endl;
    }

    cout << "=============================" << endl;

    int choice;
    cin >> choice;
    return choice;
}