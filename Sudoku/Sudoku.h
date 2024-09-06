
#ifndef SUDOKU_H
#define SUDOKU_H
/*
������Ϸ����
*/
#include "Cell.h"
#include "Block.h"
#include "Row.h"
#include "Column.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include <string>
#include <vector>

class Sudoku {
private:
    std::vector<std::vector<Cell*>> board;  // 9x9��Cellָ�����
    std::vector<Row> rows;                  // 9��Row
    std::vector<Column> columns;            // 9��Column
    std::vector<Block> blocks;              // 9��Block
    int id;
    std::string difficulty;
    IOInterface* io;              // ָ��IO�ӿڵ�ָ��
    MenuManager menuManager;      // ����˵���ʵ��
    PuzzleLoader* puzzleLoader;   // ��Ŀ���������ָ��

    // ��ʼ��Board�����ó�ʼ��ʾ
    void initializeBoard(const std::vector<int>& boardData);

    // ��ʾ��ǰBoard״̬
    void displayBoard() const;

    // ���ò˵���
    void setupMenu();

public:
    // ���캯��
    Sudoku(IOInterface* ioInterface, PuzzleLoader* loader);

    // ���ļ�������Ϸ����
    bool loadFromFile(int gameID);

    // ���浱ǰ��Ϸ���ļ�
    bool saveToFile(int gameID);

    // ��ʼ��Ϸ
    void start();

    // ����ĳ����Ԫ���ֵ
    void setCellValue(int row, int col, int value);

    // �����Ϸ�Ƿ����
    bool checkIfSolved() const;

    // ������Ϸ
    void reset();
};

#endif // SUDOKU_H
