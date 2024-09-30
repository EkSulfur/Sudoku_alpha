﻿#ifndef BASICCOMMANNDS_H
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
#include "OperationRecorder.h"

// 输入一个数的命令
class InputNumberCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
    OperationRecorder* operationRecorder;
public:
    InputNumberCommand(Sudoku* s, IOInterface* ioInterface, OperationRecorder* operationRecorder) : sudoku(s),
        io(ioInterface),operationRecorder(operationRecorder) {}

    void execute() override;
};

// 擦去一个数的命令
class EraseNumberCommand : public Command {
private:
    Sudoku* sudoku;
    IOInterface* io;
    OperationRecorder* operationRecorder;
public:
    EraseNumberCommand(Sudoku* s, IOInterface* ioInterface, OperationRecorder* operationRecorder) : sudoku(s),
        io(ioInterface),operationRecorder(operationRecorder) {}

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
    bool *isRunning;
public:
    // 先设置isRunning默认参数为nullptr
    ExitGameCommand(IOInterface* ioInterface, bool *isRunning = nullptr) : io(ioInterface),isRunning(isRunning) {}

    void execute() override;
};


// 自动把唯一候选数填充上的命令
class AutoSetNumberCommand : public Command {
private:
    Sudoku* sudoku;
public:
    AutoSetNumberCommand(Sudoku* s) : sudoku(s) {}

    void execute() override;
};

// 返回上一操作的命令
class BackCommand : public Command {


};
#endif 