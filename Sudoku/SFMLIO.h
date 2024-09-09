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

    // ��ʾ����
    void displayBoard(const std::vector<std::vector<Cell*>>& board) override;

    // ��ʾ��Ϣ
    void displayInfo(const int id, const std::string difficulty) override;

    // ��ʾ��Ϣ
    void displayMessage(const std::string& message) override;

    // ��ȡ�û�����
    std::string getUserInput() override;

    // ��ȡ�û����������ز�������
    std::vector<int> getOperation() override;

    // ��ȡλ�ã���������
    std::vector<int> getPosition() override;

    // ��ȡ��������һ������
    int getNumber() override;

    // ��ʾ�˵��������û�ѡ��
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
