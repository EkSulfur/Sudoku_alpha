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

int ConsoleIO::displayMenu(const vector<string>& options) const {
    cout << "\n=============================" << endl;
    cout << "|    ��ѡ��һ��������        |" << endl;

    for (size_t i = 0; i < options.size(); ++i) {
        cout << "|    " << i + 1 << ". " << options[i] << endl;
    }

    cout << "=============================" << endl;

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        cout << "��Ч���룬��ѡ����ȷ��ѡ��: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �����������
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �����з�
    return choice;
}

void ConsoleIO::displayInfo(const int id, const string difficulty) const {
    cout << "��ǰ��Ϸ�Ѷ�: " << difficulty << endl;
    cout << "�û�ID: " << id << endl;
    cout << "����Խ������²���: " << endl;
    cout << "1. ��������" << endl;
    cout << "2. �鿴��ǰ״̬" << endl;
    cout << "3. �˳���Ϸ" << endl;
}

vector<int> ConsoleIO::getOperation() const {
    vector<int> operation;
    int command;

    cout << "��������Ҫ���еĲ�����1: ����, 2: �鿴״̬, 3: �˳���Ϸ��: ";
    while (!(cin >> command) || (command < 1 || command > 3)) {
        cout << "��Ч���룬���������֣�1, 2 �� 3��: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �����������
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �����з�

    if (command == 1) {
        int row, col, num;
        cout << "��������Ҫ������� (1-9): ";
        while (!(cin >> row) || row < 1 || row > 9) {
            cout << "��Ч���룬��������ȷ���к� (1-9): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "��������Ҫ������� (1-9): ";
        while (!(cin >> col) || col < 1 || col > 9) {
            cout << "��Ч���룬��������ȷ���к� (1-9): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "��������Ҫ��������� (1-9): ";
        while (!(cin >> num) || num < 1 || num > 9) {
            cout << "��Ч���룬��������ȷ������ (1-9): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        operation.push_back(1); // 1 ������������
        operation.push_back(row);
        operation.push_back(col);
        operation.push_back(num);
    }
    else if (command == 2) {
        operation.push_back(2); // 2 ����鿴״̬����
    }
    else if (command == 3) {
        operation.push_back(3); // 3 �����˳���Ϸ����
    }

    return operation;
}
