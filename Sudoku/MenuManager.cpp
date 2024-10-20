// MenuManager.cpp
#include "MenuManager.h"

// 添加菜单选项及对应的命令
void MenuManager::addOption(const std::string& optionText, Command* command) {
    options.emplace_back(optionText, command);
}

// 显示菜单并获取用户选择
int MenuManager::displayMenu(IOInterface* io) {
    // 如果菜单还未构建，调用构建函数
    if (options.empty()) {
        buildMenu();
    }

    // 显示菜单选项
    for (size_t i = 0; i < options.size(); ++i) {
        io->displayMessage(std::to_string(i + 1) + ". " + options[i].first);
    }

    // 获取用户选择
    int choice;
    std::string input = io->getUserInput();

    try {
        choice = std::stoi(input);
    }
    catch (...) {
        io->displayError("无效输入，请输入数字。");
        return -1;
    }

    if (choice >= 1 && choice <= static_cast<int>(options.size())) {
        options[choice - 1].second->execute();  // 执行对应的命令
    }
    else {
        io->displayError("无效选项，请重试。");
    }
    return choice;
}

// 清空菜单选项
void MenuManager::clearOptions() {
    for (auto& option : options) {
        delete option.second;
    }
    options.clear();
}

// 析构函数实现
MenuManager::~MenuManager() {
    clearOptions();
}
