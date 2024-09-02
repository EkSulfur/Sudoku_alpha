#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <functional>
#include <map>
#include <string>

class MenuManager {
private:
    std::map<std::string, std::function<void()>> menuItems;  // �˵������������ӳ��
    std::map<int, std::string> menuIndexes;  // �˵����������ӳ��

    // �������ƻ�ȡ�˵�����
    int getMenuIndexByName(const std::string& name) const;

public:
    // ��Ӳ˵���
    void addMenuItem(const std::string& name, std::function<void()> action);

    // �Ƴ��˵���
    void removeMenuItem(const std::string& name);

    // ��ʾ�˵�
    void displayMenu() const;

    // ִ�в˵���
    void executeMenuItem(const std::string& input) const;
};

#endif // MENU_MANAGER_H
