// master.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "MiniSudoku.h"
#include "ConsoleIO.h"
#include "PuzzleLoaderDAT.h"

int main() {
    // ��������̨��������ӿ�
    ConsoleIO consoleIO;

    // ����DAT��ʽ��PuzzleLoader
    PuzzleLoaderDAT puzzleLoader;

    // ����MiniSudoku��Ϸʵ��
    MiniSudoku game(&consoleIO, &puzzleLoader);

    // ���ļ��м�����Ϸ����
    int gameID = 1;  // ��������Ҫ����IDΪ1����Ϸ
    if (!game.loadFromFile(gameID)) {
        consoleIO.displayMessage("Failed to load the game. Exiting...");
        return 1;
    }

    // ������Ϸ
    game.start();

    return 0;
}


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
