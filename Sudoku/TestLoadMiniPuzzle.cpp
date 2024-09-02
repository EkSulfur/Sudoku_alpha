#include "PuzzleLoaderDAT.h"
#include <iostream>
#include <vector>
#include <cassert>

// ���� loadPuzzle ����
void testLoadPuzzle() {
    PuzzleLoaderDAT loader;
    std::vector<int> board;
    std::string difficulty;

    // ���Գɹ�����
    bool result = loader.loadPuzzle("MiniPuzzles.dat", 1, board, difficulty);
    assert(result == true);
    assert(difficulty == "Easy");
    assert(board.size() == 9);
    assert(board[0] == 5);
    assert(board[1] == 3);
    assert(board[4] == 7);

    std::cout << "testLoadPuzzle passed!" << std::endl;

    // ���Լ��ز����ڵ�ID
    result = loader.loadPuzzle("MiniPuzzles.dat", 3, board, difficulty);
    assert(result == false);

    std::cout << "testLoadPuzzle with invalid ID passed!" << std::endl;

    // ���Լ��ز����ڵ��ļ�
    result = loader.loadPuzzle("nonexistent.dat", 1, board, difficulty);
    assert(result == false);

    std::cout << "testLoadPuzzle with nonexistent file passed!" << std::endl;
}

// ���� savePuzzle ����
void testSavePuzzle() {
    PuzzleLoaderDAT loader;
    std::vector<int> board = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::string difficulty = "Hard";

    // ���Ա�������Ϸ
    bool result = loader.savePuzzle("MiniPuzzles.dat", 3, board, difficulty);
    assert(result == true);

    // ��֤������ܹ��ɹ�����
    std::vector<int> loadedBoard;
    std::string loadedDifficulty;
    result = loader.loadPuzzle("MiniPuzzles.dat", 3, loadedBoard, loadedDifficulty);
    assert(result == true);
    assert(loadedDifficulty == "Hard");
    assert(loadedBoard == board);

    std::cout << "testSavePuzzle passed!" << std::endl;
}

//int main() {
//    // ���в���
//    testLoadPuzzle();
//    testSavePuzzle();
//
//    return 0;
//}
