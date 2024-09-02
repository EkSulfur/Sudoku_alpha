#include "MiniSudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

// ���캯��
MiniSudoku::MiniSudoku(IOInterface* ioInterface, PuzzleLoader* loader)
    : io(ioInterface), puzzleLoader(loader), id(0), difficulty("Unknown") {
    setupMenu();  // ���ò˵���
    initializeBlock(std::vector<int>(9, 0));  // ��ʼ��BlockΪȫ0
}

// ��ʼ��Block�����ó�ʼ��ʾ
void MiniSudoku::initializeBlock(const std::vector<int>& boardData) {
    if (block.getCells().empty()) {
        for (int i = 0; i < 9; ++i) {
            block.addCell(new Cell());  // ��̬����Cell������ӵ�Block��
        }
    }

    for (int i = 0; i < 9; ++i) {
        block.getCells()[i]->setValue(boardData[i]);
    }
}

// ��ʾ��ǰBlock״̬
void MiniSudoku::displayBlock() const {
    io->displayMessage("Game ID: " + std::to_string(id) + " | Difficulty: " + difficulty);
    std::vector<int> board;
    for (const auto& cell : block.getCells()) {
        board.push_back(cell->getValue());
    }
    io->displayBoard(board);
}

// ���ò˵���
void MiniSudoku::setupMenu() {
    menuManager.addMenuItem("Set Value", [this]() {
        io->displayMessage("Enter row (1-3), column (1-3), and value (1-9): ");
        int row, col, value;
        std::cin >> row >> col >> value;
        setCellValue(row, col, value);
        });

    menuManager.addMenuItem("Reset Game", [this]() {
        reset();
        });

    menuManager.addMenuItem("Save Game", [this]() {
        saveToFile(this->id);
        });

    menuManager.addMenuItem("Quit", [this]() {
        io->displayMessage("Quitting game.");
        exit(0);
        });
}

// ���ļ�������Ϸ����
bool MiniSudoku::loadFromFile(int gameID) {
    std::vector<int> boardData;
    if (puzzleLoader->loadPuzzle("MiniPuzzles.dat", gameID, boardData, difficulty)) {
        id = gameID;
        initializeBlock(boardData);
        return true;
    }
    else {
        io->displayMessage("Failed to load game.");
        return false;
    }
}

// ���浱ǰ��Ϸ���ļ�
bool MiniSudoku::saveToFile(int gameID) {
    std::vector<int> boardData;
    for (const auto& cell : block.getCells()) {
        boardData.push_back(cell->getValue());
    }
    return puzzleLoader->savePuzzle("puzzles.dat", gameID, boardData, difficulty);
}

// ����ĳ����Ԫ���ֵ
void MiniSudoku::setCellValue(int row, int col, int value) {
    int index = (row - 1) * 3 + (col - 1); // Convert 2D index to 1D
    if (index >= 0 && index < 9) {
        block.getCells()[index]->setValue(value);
    }
    else {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}

// �����Ϸ�Ƿ����
bool MiniSudoku::checkIfSolved() const {
    return block.isSolved() && block.isValid();
}

// ������Ϸ
void MiniSudoku::reset() {
    block.resetCandidates();
    // �������������¼��س�ʼֵ��ִ���������ò���
}

// ��ʼ��Ϸ
void MiniSudoku::start() {
    while (!checkIfSolved()) {
        displayBlock();
        menuManager.displayMenu();
        io->displayMessage("Select an option:");
        std::string option = io->getUserInput();
        menuManager.executeMenuItem(option);
    }

    io->displayMessage("Congratulations! You solved the MiniSudoku!");
}
