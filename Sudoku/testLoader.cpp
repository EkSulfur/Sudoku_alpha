#include "testLoader.h"
#include <iostream>

/*
����Loader�������
*/

// ��ӡ�������̵ĸ�������
void printBoard(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// ���Ժ���
void testPuzzleLoader() {
    PuzzleLoaderDAT loader;
    std::vector<std::vector<int>> board;
    std::string difficulty;

    // ���Լ�����������
    if (loader.loadPuzzle("puzzles.dat", 1, board, difficulty)) {
        std::cout << "�������سɹ����Ѷ�Ϊ: " << difficulty << std::endl;
        printBoard(board);
    }
    else {
        std::cerr << "��������ʧ�ܣ�" << std::endl;
    }

    // �޸����̣�����Ϊ�µ�����
    std::vector<std::vector<int>> newBoard = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    std::string newDifficulty = "�е�";

    // �����µ���������
    if (loader.savePuzzle("puzzles.dat", 2, newBoard, newDifficulty)) {
        std::cout << "��������ɹ���IDΪ 2���Ѷ�Ϊ: " << newDifficulty << std::endl;
    }
    else {
        std::cerr << "��������ʧ�ܣ�" << std::endl;
    }

    // �ٴμ��ظոձ������������֤�����Ƿ�ɹ�
    if (loader.loadPuzzle("puzzles.dat", 2, board, difficulty)) {
        std::cout << "ID Ϊ 2 ���������سɹ����Ѷ�Ϊ: " << difficulty << std::endl;
        printBoard(board);
    }
    else {
        std::cerr << "���� ID Ϊ 2 ������ʧ�ܣ�" << std::endl;
    }
}