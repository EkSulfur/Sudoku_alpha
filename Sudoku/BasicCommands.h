#ifndef BASICCOMMANNDS_H
#define BASICCOMMANDS_H

/*
9月10日
把一些基础的指令的命令类的定义放到一起，避免文件过于冗杂
后续若有其它菜单指令可加到这个文件里，也可新建NewCommands的.h, .cpp文件，抑或单独为每个新增的类
新建文件
by lch
*/
#include "Command.h"
#include "Sudoku.h"
#include "IOInterface.h"

// 输入一个数的命令
class InputNumberCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    InputNumberCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};

// 擦去一个数的命令
class EraseNumberCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    EraseNumberCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};

// 输入候选数的命令
class AddCandidateCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    AddCandidateCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};

// 删除候选数的命令
class RemoveCandidateCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    RemoveCandidateCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};

// 自动补全候选数的命令
class AutoUpdateCandidatesCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    AutoUpdateCandidatesCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};


// 保存游戏的命令
class SaveGameCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
    int id;
public:
    SaveGameCommand(Sudoku* s, IOInterface* ioInterface, int gameId) : sudoku(s), io(ioInterface), id(gameId) {}

    void execute() override;
};

// 重置游戏的命令
class ResetGameCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
public:
    ResetGameCommand(Sudoku* s, IOInterface* ioInterface) : sudoku(s), io(ioInterface) {}

    void execute() override;
};


// 退出游戏的命令
class ExitGameCommand : public Command {
private:
    IOInterface* io;
public:
    ExitGameCommand(IOInterface* ioInterface) : io(ioInterface) {}

    void execute() override;
};

#endif 