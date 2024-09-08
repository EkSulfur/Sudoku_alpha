#include "Sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>


/*
9��7��
���ĿǰSudoku������к�������Ϸ�ڲ��߼����岿�ָ�ɣ�δ����
9��8��
����play��������Ϸ��ʼǰ���ڶ�ȡid�ͼ��ص�ѭ��
by lch
*/


void Sudoku::initializeBoard(const std::vector<std::vector<int>>& boardData)
{
    // ��ʼ��board, rows, columns, blocks
    board.resize(9, std::vector<Cell*>(9));
    rows.resize(9);
    columns.resize(9);
    blocks.resize(9);

    // ���Cell���󶨵�rows, columns��blocks��
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = boardData[i][j];  // �������л�ȡ�����ĳ�ʼֵ
            Cell* cell = new Cell(val); // ʹ��new����Cell����
            board[i][j] = cell;         // �󶨵�board����

            // �󶨵���Ӧ��row, column��block
            rows[i].addCell(cell);      // ��ӵ���Ӧ��row
            columns[j].addCell(cell);   // ��ӵ���Ӧ��column
            blocks[(i / 3) * 3 + j / 3].addCell(cell);  // ��ӵ���Ӧ��block
        }
    }
}

Sudoku::Sudoku(IOInterface* ioInterface, PuzzleLoader* loader):io(ioInterface), puzzleLoader(loader)
{
    int id = 1; //�ȳ�ʼ��idΪ1
}

bool Sudoku::loadFromFile(int gameID)
{
    std::vector<std::vector<int>> boardData; // �洢��Ŀ����
    if(!(puzzleLoader->loadPuzzle("Puzzles.dat", id, boardData, difficulty))) return false;  // ����������Ϣ
    initializeBoard(boardData);
    return true;
}

bool Sudoku::saveToFile(int gameID)
{
    std::vector<std::vector<int>> boardData(9, std::vector<int>(9));  // ����9x9��boardData����

    // �����������̣���ÿ��Cell��ֵ���浽boardData��
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardData[i][j] = board[i][j]->getValue();  // ��ÿ��Cell��ֵ����boardData
        }
    }

    // ����puzzleLoader��savePuzzle��������������Ϣ���浽�ļ���
    return puzzleLoader->savePuzzle("Puzzles.dat", gameID, boardData, difficulty);
}

void Sudoku::play() {
    //����ѭ��
    while (true) {
        // ѡ����Ϸ�浵ID
        io->displayMessage("��ѡ��浵��ţ�");
        std::string input = io->getUserInput();

        // ���Խ��û�����ת��Ϊ����ID
        try {
            id = std::stoi(input);  // ��������ַ���ת��Ϊ����ID
        }
        catch (const std::invalid_argument&) {
            io->displayMessage("��Ч�����룬��������ȷ�Ĵ浵��š�");
            continue;
        }

        // ������Ϸ
        if (!loadFromFile(id)) {
            io->displayMessage("�޷�����������Ϸ��");
            continue;
        }
        else break;
    }

    // ��Ϸѭ��
    while (true) {
        // ��ʾ��Ϸ��Ϣ�͵�ǰ����
        io->displayInfo(id, difficulty);
        io->displayBoard(board);

        // �����Ϸ�Ƿ��Ѿ����
        if (checkIfSolved()) {
            io->displayMessage("��ϲ�����Ѿ������������");
            break;
        }

        // ��ʾ�˵��������ѡ�����
        std::vector<std::string> options = {
            "����һ����",      // �û�����һ����������
            "��ȥһ����",      // ��ȥ���������
            "�����ѡ��",      // ����һ����ѡ��
            "ɾ����ѡ��",      // ɾ��һ����ѡ��
            "�Զ������ѡ��",  // �Զ��������е�Ԫ��ĺ�ѡ��
            "������Ϸ",        // ���浱ǰ��Ϸ
            "������Ϸ",        // ������Ϸ
            "�˳�"             // �˳���Ϸ
        };
        int choice = io->displayMenu(options);

        switch (choice) {
        case 1: {  // ����һ����
            io->displayMessage("������������� �� ����");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int value = operation[2];

                // ����ָ��λ�õ�Cellֵ
                if (!setCellValue(row, col, value)) {
                    io->displayMessage("��Ч���������������롣");
                }
            }
            else {
                io->displayMessage("�����ʽ���������ԡ�");
            }
            break;
        }
        case 2: {  // ��ȥһ����
            io->displayMessage("������������� �У���ȥ��Ӧλ�õ�����");
            std::vector<int> operation = io->getPosition();
            if (operation.size() == 2) {    // �����߼��ж�������
                int row = operation[0];
                int col = operation[1];

                // ��ȥָ��λ�õ�����������Ϊ 0
                if (!setCellValue(row, col, 0)) {
                    io->displayMessage("�޷���ȥ��λ�õ�����");
                }
            }
            else {
                io->displayMessage("�����ʽ���������ԡ�");
            }
            break;
        }
        case 3: {  // �����ѡ��
            io->displayMessage("������������� �� ��ѡ��");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int candidate = operation[2];

                // ���ָ��λ�õĺ�ѡ��
                if (!addCellCandidate(row, col, candidate)) {
                    io->displayMessage("�޷���Ӹú�ѡ����");
                }
            }
            else {
                io->displayMessage("�����ʽ���������ԡ�");
            }
            break;
        }
        case 4: {  // ɾ����ѡ��
            io->displayMessage("������������� �� ��ѡ����ɾ���ú�ѡ����");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int candidate = operation[2];

                // ɾ��ָ��λ�õĺ�ѡ��
                if (!removeCellCandidates(row, col, candidate)) {
                    io->displayMessage("�޷�ɾ���ú�ѡ����");
                }
            }
            else {
                io->displayMessage("�����ʽ���������ԡ�");
            }
            break;
        }
        case 5: {  // �Զ������ѡ��
            if (autoUpdateCandidates()) {
                io->displayMessage("�Զ������ѡ����ɣ�");
            }
            else {
                io->displayMessage("�޷��Զ������ѡ����");
            }
            break;
        }
        case 6: {  // ������Ϸ
            if (saveToFile(id)) {
                io->displayMessage("��Ϸ�ѳɹ����棡");
            }
            else {
                io->displayMessage("����ʧ�ܡ�");
            }
            break;
        }
        case 7: {  // ������Ϸ
            if (reset()) {
                io->displayMessage("��Ϸ�����ã�");
            }
            else {
                io->displayMessage("����ʧ�ܡ�");
            }
            break;
        }
        case 8: {  // �˳���Ϸ
            io->displayMessage("�˳���Ϸ��");
            return;
        }
        default:
            io->displayMessage("��Чѡ�������ѡ��");
        }
    }
}

bool Sudoku::setCellValue(int row, int col, int value)
{
    //���û�������ת��������
    row -= 1;
    col -= 1;

    // ��������Ƿ�Խ��
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // ���������Ϊ 0����ʾ������Ӧλ�õ���ֵ
    if (value == 0) {
        // ���ö�ӦCell��setValue��������ֵ��Ϊ0
        board[row][col]->setValue(0);  // ����ֵ
        return true;  // �����������ǺϷ���
    }

    // ���ö�ӦCell��setValue������������ֵ
    if (!board[row][col]->setValue(value)) {
        return false;
    }

    // ����Ӧ���С��кͿ��Ƿ�Ϸ�
    if (!rows[row].isValid()) {
        return false;
    }
    if (!columns[col].isValid()) {
        return false;
    }
    if (!blocks[(row / 3) * 3 + col / 3].isValid()) {
        return false;
    }

    // ������м�鶼ͨ�����򷵻�true
    return true;
}

bool Sudoku::addCellCandidate(int row, int col, int candidate)
{
    //���û�������ת��������
    row -= 1;
    col -= 1;

    // ��������Ƿ�Խ��
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // ���ö�ӦCell��addCandidate�����������ֵ
    if (!board[row][col]->addCandidate(candidate)) {
        return false;
    }

    return true;
}

bool Sudoku::removeCellCandidates(int row, int col, int candidate)
{
    //���û�������ת��������
    row -= 1;
    col -= 1;

    // ��������Ƿ�Խ��
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // ���ö�ӦCell��removeCandidate�������Ƴ���ѡֵ
    if (!board[row][col]->removeCandidate(candidate)) {
        return false;
    }

    return true;
}

bool Sudoku::autoUpdateCandidates()
{
    // �������������е�ÿ��Cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Cell* cell = board[i][j];

            // ������Cell�Ѿ�ȷ����ֵ��������
            if (cell->isSolved()) {
                continue;
            }

            // ����ÿ����ѡֵ1��9��������Ƿ���Դ���
            for (int candidate = 1; candidate <= 9; ++candidate) {
                // ����С��л�����Ѿ��������ֵ����Ӻ�ѡֵ��ɾ��
                if (rows[i].hasValue(candidate) ||
                    columns[j].hasValue(candidate) ||
                    blocks[(i / 3) * 3 + j / 3].hasValue(candidate)) {
                    cell->removeCandidate(candidate);
                }
            }
        }
    }
    return true;  //�Զ����ºã�����true
}

bool Sudoku::checkIfSolved() const
{
    // ���ÿһ��row�Ƿ��Ѿ����
    for (int i = 0; i < 9; ++i) {
        if (!rows[i].isSolved()) {
            return false;
        }
    }

    // 9��row�����������Ϸ�Ѿ����
    return true;
}

bool Sudoku::reset()
{
    std::vector<std::vector<int>> boardData; // �洢��Ŀ����

    // ����puzzleLoader����������Ŀ
    if (!puzzleLoader->loadPuzzle("Puzzles.dat", id, boardData, difficulty)) {
        return false;
    }

    // ����board���޸����е�Cell��������resetCandidates
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = boardData[i][j];              // �Ӽ��ص����ݻ�ȡ�µ�ֵ
            board[i][j]->setValue(val);             // �޸����е�Cell��ֵ
            board[i][j]->resetCandidates();         // ����Cell�ĺ�ѡֵ
        }
    }

    return true;  // ���óɹ�
}

Sudoku::~Sudoku()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            delete board[i][j];
        }
    }
}