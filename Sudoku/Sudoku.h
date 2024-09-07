
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

/*
9��7��
ɾ��Sudoku���е�displayboard������ί�и�io��
ɾ��start������ԭ�й��ܰ�����play��
�޸Ķ�������ķ���ֵ��void���ͱ�Ϊbool����
����Զ����º�ѡֵ����
ɾ�����ò˵����
*/

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
    void initializeBoard(const std::vector<std::vector<int>>& boardData);

public:
    // ���캯��
    Sudoku(IOInterface* ioInterface, PuzzleLoader* loader);

    // ���ļ�������Ϸ����
    bool loadFromFile(int gameID);

    // ���浱ǰ��Ϸ���ļ�
    bool saveToFile(int gameID);

    //����Ϸ
    void play();

    // ����ĳ����Ԫ���ֵ
    bool setCellValue(int row, int col, int value);

    // ���ĳ����Ԫ��ĺ�ѡֵ
    bool addCellCandidate(int row, int col, int candidate);

    // ɾ��ĳ����Ԫ��ĺ�ѡֵ
    bool removeCellCandidates(int row, int col, int candidate);

    // �Զ�����ÿ��Cell�еĺ�ѡֵ
    bool autoUpdateCandidates();

    // �����Ϸ�Ƿ����
    bool checkIfSolved() const;

    // ������Ϸ
    bool reset();
};

#endif // SUDOKU_H
