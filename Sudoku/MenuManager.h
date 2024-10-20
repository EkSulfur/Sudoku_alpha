// MenuManager.h
#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Command.h"
#include "IOInterface.h"
#include <vector>

class MenuManager {
protected:
    std::vector<std::pair<std::string, Command*>> options;  // 菜单选项和对应的命令

public:
    // 析构函数声明为虚函数，确保子类析构函数被正确调用
    virtual ~MenuManager();

    // 添加菜单选项及对应的命令
    void addOption(const std::string& optionText, Command* command);

    // 显示菜单并获取用户选择
    int displayMenu(IOInterface* io);

    // 清空菜单选项
    void clearOptions();

    // 纯虚函数，用于构建菜单
    virtual void buildMenu() = 0;
};

#endif // MENU_MANAGER_H
