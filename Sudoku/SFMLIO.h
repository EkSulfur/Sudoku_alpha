#ifndef SFMLIO_H
#define SFMLIO_H

#include <SFML/Graphics.hpp>
#include "IOInterface.h"
#include <vector>
#include <string>
#include "Cell.h"

class SFMLIO : public IOInterface {
public:
    SFMLIO();
    ~SFMLIO();

    // 显示棋盘
    void displayBoard(const std::vector<std::vector<Cell*>>& board) override;

    // 显示信息
    void displayInfo(const int id, const std::string difficulty) override;

    // 显示消息
    void displayMessage(const std::string& message) override;

    // 获取用户输入
    std::string getUserInput() override;

    // 获取用户操作并返回操作向量
    std::vector<int> getOperation() override;

    // 获取位置，返回向量
    std::vector<int> getPosition() override;

    // 获取数，返回一个整数
    int getNumber() override;

    // 显示菜单，返回用户选择
    int displayMenu(const std::vector<std::string>& options) override;

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text messageText;
    sf::RectangleShape cellOutline;

    void drawBoard(const std::vector<std::vector<Cell*>>& board);
    int getUserChoiceFromMenu(const std::vector<std::string>& options);
    std::vector<int> getUserPosition();
    int getUserInputNumber();
};

#endif // SFMLIO_H
