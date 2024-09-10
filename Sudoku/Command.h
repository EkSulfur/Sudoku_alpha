#ifndef COMMAND_H
#define COMMAND_H

/*
9月10日
命令模式，接口类
by lch
*/

class Command {
public:
    virtual void execute() = 0;  // 定义一个纯虚函数
    virtual ~Command() = default;
};

#endif