﻿#include "MenuManager.h"
#include <iostream>
#include <vector>
#include <string>
/*
9月10日
完成MenuManager类的函数实现
*/

// 添加菜单选项及对应的命令
void MenuManager::addOption(const std::string& optionText, Command* command)
{
    options.emplace_back(optionText, command);
}

// 显示菜单并获取用户选择
int MenuManager::displayMenu(IOInterface* io) const
{
    std::vector<std::string> newOptions;
    // 遍历原来的 options，将 pair 中的 string 提取到 newOptions 中
    for (const auto& option : options) {
        newOptions.push_back(option.first);
    }

    io->displayMenu(newOptions);

    int choice;
    std::cin >> choice;
    if (choice >= 1 && choice <= options.size()) {
        options[choice - 1].second->execute();  // 执行对应的命令
    }
    else {
        io->displayMessage("无效选项，请重试。");
    }
    return choice;
}

// 清空菜单选项
void MenuManager::clearOptions()
{
    options.clear();
}

// 析构函数实现
MenuManager::~MenuManager()
{
    // 遍历选项容器中的每一个元素
    for (auto& option : options) {
        // 对于每个元素，删除其pair中的第二个成员（即命令对象指针）
        delete option.second;  // 确保释放所有命令对象
    }
}