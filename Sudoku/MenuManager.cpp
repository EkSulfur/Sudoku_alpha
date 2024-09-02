#include "MenuManager.h"
#include <iostream>

void MenuManager::addMenuItem(const std::string& name, std::function<void()> action) {
    int index = menuItems.size() + 1;  // ÿ���������ʱ������һ���µı��
    menuItems[name] = action;
    menuIndexes[index] = name;  // �������˵������ƹ���
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
        std::cout << item.first << ". " << item.second << std::endl;  // ��ʾ��ź�����
    }
}

void MenuManager::executeMenuItem(const std::string& input) const {
    int index = 0;
    try {
        index = std::stoi(input);  // ���Խ�����ת��Ϊ����
    }
    catch (...) {
        index = -1;  // ���ת��ʧ�ܣ���index����Ϊ��Чֵ
    }

    if (index > 0 && menuIndexes.find(index) != menuIndexes.end()) {
        // ���������Ǳ�ţ����Ҹñ�Ŵ���
        auto name = menuIndexes.at(index);
        menuItems.at(name)();
    }
    else if (menuItems.find(input) != menuItems.end()) {
        // ���������ǲ˵�������
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
    return -1;  // ���δ�ҵ��򷵻�-1
}
