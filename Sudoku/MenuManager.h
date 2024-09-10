#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Command.h"
#include "IOInterface.h"
#include <vector>
#include <cstring>

/*
9月10日
添加MenuManager类，组合Command类，实现命令模式，更好地适应未来可能会添加菜单选项的变化
by lch
*/

class MenuManager {
private:
    std::vector<std::pair<std::string, Command*>> options;  // 菜单选项和对应的命令
public:
    // 添加菜单选项及对应的命令
    void addOption(const std::string& optionText, Command* command);

    // 显示菜单并获取用户选择
    int displayMenu(IOInterface* io) const;

    // 清空菜单选项
    void clearOptions();

    ~MenuManager();
};

#endif // MENU_MANAGER_H
