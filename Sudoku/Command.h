#ifndef COMMAND_H
#define COMMAND_H

/*
9月10日
命令模式，接口类
 
*/

class Command {
public:
    virtual void execute() = 0;  // 定义一个纯虚函数

    virtual ~Command() = default;

    // 禁止拷贝构造函数和赋值操作符，并将构造函数设置为保护

    Command(const Command&) = delete;

    Command& operator=(const Command&) = delete;

protected:
    Command() {};
};

#endif