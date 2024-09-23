#ifndef IO_INTERFACE_H
#define IO_INTERFACE_H

#include <string>
#include <vector>
#include "Cell.h"

/*
9月6日
初步定义IOInterface类的主要接口，相关实现工作由lwh完成
由于IOInterface为接口类，实际的修改应该在ConsoleIO中完成
displayMenu中目前应该至少有开始游戏、退出等选项
建议添加displaInfo函数，显示目前难度、id，和玩家可以做出的选项（填入数等）
建议添加一个读取操作的函数getOperation，返回一个vectot<int>类型的操作向量，代表每次用户的操作
比如用户输入1想填数，输入了R1 C1 1，代表对应位置想填1，建议函数返回向量[1, 1, 1, 1]代表进行了对应操作
其它操作定义时应该用注释说明
相较于getUserInput我感觉getOperation更符合类之间职责的分离
by lch
9月7日
修改getOperation的作用（代码没变）主要使用场景是填数或者移除候选数时输入坐标和数字，应该是一个三维的向量
by lch
9月9日
把所有const的函数改为非const的，适应SFMLIO中的变化
*/


// IOInterface: 由负责界面交互的同事来实现
class IOInterface {
public:
    virtual ~IOInterface() = default;

    // 显示棋盘
    virtual void displayBoard(const std::vector<std::vector<Cell>>& board) = 0;

    //显示信息
    virtual void displayInfo(const int id, const std::string difficulty) = 0;

    // 显示消息
    virtual void displayMessage(const std::string& message) = 0;

    // 获取用户输入
    virtual std::string getUserInput() = 0;

    // 获取操作，返回向量
    virtual std::vector<int> getOperation() = 0;

    // 获取位置，返回向量
    virtual std::vector<int> getPosition() = 0;

    // 获取数，返回一个整数
    virtual int getNumber() = 0;

    // 显示菜单，返回用户选择
    virtual int displayMenu(const std::vector<std::string>& options) = 0;
    
    //禁止拷贝构造函数
    IOInterface(const IOInterface&) = delete;

    //禁止赋值操作符
    IOInterface& operator=(const IOInterface&) = delete;
    
    //禁止构造函数
    IOInterface() = delete;
};

#endif // IO_INTERFACE_H
