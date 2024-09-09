#include "SFMLIO.h"
#include <iostream>

SFMLIO::SFMLIO() : window(sf::VideoMode(600, 600), "Sudoku Game") {
    // ��������
    if (!font.loadFromFile("FandolSong-Regular.ttf")) {
        std::cerr << "�޷���������" << std::endl;
    }

    // ����Ĭ����Ϣ�ı���ʽ
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::White);

    // �������̸��ӱ߿�
    cellOutline.setSize(sf::Vector2f(60, 60));
    cellOutline.setFillColor(sf::Color::Transparent);
    cellOutline.setOutlineThickness(1);
    cellOutline.setOutlineColor(sf::Color::Black);
}

SFMLIO::~SFMLIO() {
    if (window.isOpen()) {
        window.close();
    }
}

// ��ʾ����
void SFMLIO::displayBoard(const std::vector<std::vector<Cell*>>& board) {
    window.clear(sf::Color::White);

    // ��������
    drawBoard(board);

    window.display();
}

void SFMLIO::drawBoard(const std::vector<std::vector<Cell*>>& board) {
    int size = board.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cellOutline.setPosition(j * 60, i * 60);
            window.draw(cellOutline);

            if (board[i][j]->getValue() != 0) {
                sf::Text cellValue(std::to_string(board[i][j]->getValue()), font, 24);
                cellValue.setFillColor(sf::Color::Black);
                cellValue.setPosition(j * 60 + 20, i * 60 + 10);
                window.draw(cellValue);
            }
        }
    }
}

// ��ʾ��Ϣ
void SFMLIO::displayInfo(const int id, const std::string difficulty) {
    std::string info = "�û�ID: " + std::to_string(id) + "\n�Ѷ�: " + difficulty;
    displayMessage(info);
}

// ��ʾ��Ϣ
void SFMLIO::displayMessage(const std::string& message) {
    window.clear();
    messageText.setString(message);
    window.draw(messageText);
    window.display();
}

// ��ȡ�û�����
std::string SFMLIO::getUserInput() {
    std::string inputText;
    sf::Text userInputDisplay;
    userInputDisplay.setFont(font);
    userInputDisplay.setCharacterSize(24);
    userInputDisplay.setFillColor(sf::Color::Black);
    userInputDisplay.setPosition(10, 10);  // �����ı���ʾ��λ��

    displayMessage("�������ı����� Enter ��������");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";  // ������ڹرգ��򷵻ؿ��ַ���
            }

            // �����ı������¼�
            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);

                // �����˸��ɾ���ַ�
                if (inputChar == 8 && !inputText.empty()) {  // 8 ���˸��
                    inputText.pop_back();  // ɾ�����һ���ַ�
                }
                // ����Ƿ��� Enter �� (�س���)
                else if (inputChar == '\r' || inputChar == '\n') {  // �س���������
                    return inputText;
                }
                // ���˿����ַ���ֻ���ܿɴ�ӡ�ַ�
                else if (inputChar >= 32 && inputChar <= 126) {
                    inputText += inputChar;  // ��ӵ������ַ�����
                }

                // ������ʾ���û������ı�
                userInputDisplay.setString(inputText);
            }
        }

        window.clear(sf::Color::White);  // ����
        window.draw(userInputDisplay);   // ��ʾ�û���ǰ������ı�
        window.display();                // ˢ����ʾ
    }

    return inputText;  // ������ڱ��رգ����ص�ǰ�����������
}

// ��ȡ��������
std::vector<int> SFMLIO::getOperation() {
    displayMessage("��ѡ��һ�����ӣ�Ȼ����������");

    // ��ȡ�û�����ĸ���λ��
    std::vector<int> position = getUserPosition();

    // ��ȡ�û����������
    int number = getUserInputNumber();

    // ���ز��������������С��к����������
    return { position[0], position[1], number };
}

// ��ȡλ��
std::vector<int> SFMLIO::getPosition() {
    displayMessage("��ѡ��һ������");

    // ��ȡ�û�����ĸ���λ��
    return getUserPosition();
}

std::vector<int> SFMLIO::getUserPosition() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return { -1, -1 }; // �رմ���ʱ������Чλ��
            }

            // ����������¼�
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // ���������к���
                int row = mouseY / 60;
                int col = mouseX / 60;

                if (row >= 0 && row < 9 && col >= 0 && col < 9) {
                    return { row + 1, col + 1 };  // ����1-9��Χ
                }
            }
        }
        window.clear(sf::Color::White);
        window.display();
    }
    return { -1, -1 };  // Ĭ�Ϸ�����Чλ��
}

// ��ȡ��
int SFMLIO::getNumber() {
    return getUserInputNumber();
}

int SFMLIO::getUserInputNumber() {
    displayMessage("������һ������ (1-9)");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;  // ������Ч����
            }

            // ������������¼�
            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);
                if (inputChar >= '1' && inputChar <= '9') {
                    return inputChar - '0';
                }
            }
        }
        window.clear(sf::Color::White);
        window.display();
    }
    return -1;  // Ĭ�Ϸ�����Ч����
}

// ��ʾ�˵�
int SFMLIO::displayMenu(const std::vector<std::string>& options) {
    return getUserChoiceFromMenu(options);
}

int SFMLIO::getUserChoiceFromMenu(const std::vector<std::string>& options) {
    displayMessage("��ѡ��һ��ѡ��");

    while (window.isOpen()) {
        window.clear();
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text optionText(options[i], font, 24);
            optionText.setPosition(100, i * 40 + 50);  // ÿ��ѡ��֮����40����
            optionText.setFillColor(sf::Color::Black);
            window.draw(optionText);
        }
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;  // ������Чѡ��
            }

            // ����������¼����жϵ���Ĳ˵���
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseY = event.mouseButton.y;
                int choice = mouseY / 40;
                if (choice >= 0 && choice < static_cast<int>(options.size())) {
                    return choice + 1;
                }
            }

            // ������������¼�
            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);
                if (inputChar >= '1' && inputChar <= '9') {
                    int choice = inputChar - '0';
                    if (choice > 0 && choice <= static_cast<int>(options.size())) {
                        return choice;
                    }
                }
            }
        }
    }

    return -1;  // Ĭ�Ϸ�����Чѡ��
}
