#ifndef CURSOR_H
#define CURSOR_H

#include <windows.h>
#undef min
#undef max

class Cursor {
public:
	// 获取当前光标位置
	COORD getCursorPosition();

	// 设置光标位置
	void setCursorPosition(int x, int y);

	// 保存光标位置
	void saveCursorPosition();

	// 恢复保存的光标位置
	void resumeCursorPosition();

private:
	COORD pos;
};

#endif // !CURSOR_H
