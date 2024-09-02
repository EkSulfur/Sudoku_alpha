#include "MenuManager.h"
#include <iostream>

void MenuManager::addMenuItem(const std::string& name, std::function<void()> action) {
    int index = menuItems.size() + 1;  // 每次添加新项时，分配一个新的编号
    menuItems[name] = action;
    menuIndexes[index] = name;  // 将编号与菜单项名称关联
}

void MenuManager::removeMenuItem(const std::string& name) {
    auto it = menuItems.find(name);
    if (it != menuItems.end()) {
        int index = getMenuIndexByName(name);
        menuItems.erase(it);
        menuIndexes.erase(index);
    }
}

void MenuManager::displayMenu() const {
    std::cout << "Menu Options:" << std::endl;
    for (const auto& item : menuIndexes) {
        std::cout << item.first << ". " << item.second << std::endl;  // 显示编号和名称
    }
}

void MenuManager::executeMenuItem(const std::string& input) const {
    int index = 0;
    try {
        index = std::stoi(input);  // 尝试将输入转换为整数
    }
    catch (...) {
        index = -1;  // 如果转换失败，将index设置为无效值
    }

    if (index > 0 && menuIndexes.find(index) != menuIndexes.end()) {
        // 如果输入的是编号，并且该编号存在
        auto name = menuIndexes.at(index);
        menuItems.at(name)();
    }
    else if (menuItems.find(input) != menuItems.end()) {
        // 如果输入的是菜单项名称
        menuItems.at(input)();
    }
    else {
        std::cerr << "Invalid menu option: " << input << std::endl;
    }
}

int MenuManager::getMenuIndexByName(const std::string& name) const {
    for (const auto& item : menuIndexes) {
        if (item.second == name) {
            return item.first;
        }
    }
    return -1;  // 如果未找到则返回-1
}
