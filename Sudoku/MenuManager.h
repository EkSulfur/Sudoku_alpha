#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <functional>
#include <map>
#include <string>

class MenuManager {
private:
    std::map<std::string, std::function<void()>> menuItems;  // 菜单项名称与操作映射
    std::map<int, std::string> menuIndexes;  // 菜单编号与名称映射

    // 根据名称获取菜单项编号
    int getMenuIndexByName(const std::string& name) const;

public:
    // 添加菜单项
    void addMenuItem(const std::string& name, std::function<void()> action);

    // 移除菜单项
    void removeMenuItem(const std::string& name);

    // 显示菜单
    void displayMenu() const;

    // 执行菜单项
    void executeMenuItem(const std::string& input) const;
};

#endif // MENU_MANAGER_H
