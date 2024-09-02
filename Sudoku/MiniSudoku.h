#ifndef MINI_SUDOKU_H
#define MINI_SUDOKU_H

#include "Block.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include <string>

class MiniSudoku {
private:
    int id;
    std::string difficulty;
    Block block;
    IOInterface* io;              // ָ��IO�ӿڵ�ָ��
    MenuManager menuManager;      // ����˵���ʵ��
    PuzzleLoader* puzzleLoader;   // ��Ŀ���������ָ��

    // ��ʼ��Block�����ó�ʼ��ʾ
    void initializeBlock(const std::vector<int>& boardData);

    // ��ʾ��ǰBlock״̬
    void displayBlock() const;

    // ���ò˵���
    void setupMenu();

public:
    // ���캯��
    MiniSudoku(IOInterface* ioInterface, PuzzleLoader* loader);

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

#endif // MINI_SUDOKU_H
