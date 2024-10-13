#include "Cursor.h"

// 获取当前光标位置
COORD Cursor::getCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.dwCursorPosition;
    }
    COORD invalid = { -1, -1 };
    return invalid;
}

// 设置光标位置
void Cursor::setCursorPosition(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD temp_pos;
    temp_pos.X = x;
    temp_pos.Y = y;
    SetConsoleCursorPosition(hConsole, temp_pos);
}

// 保存光标位置
void Cursor::saveCursorPosition()
{
    this->pos = getCursorPosition();
    return;
}

// 获取光标位置
void Cursor::resumeCursorPosition()
{
    setCursorPosition(pos.X, pos.Y);
    return;
}
