#include "SFMLIO.h"
#include <iostream>

SFMLIO::SFMLIO() : window(sf::VideoMode(600, 600), "Sudoku Game") {
    // 加载字体
    if (!font.loadFromFile("FandolSong-Regular.ttf")) {
        std::cerr << "无法加载字体" << std::endl;
    }

    // 设置默认消息文本样式
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::White);

    // 设置棋盘格子边框
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

// 显示棋盘
void SFMLIO::displayBoard(const std::vector<std::vector<Cell*>>& board) {
    window.clear(sf::Color::White);

    // 绘制棋盘
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

// 显示信息
void SFMLIO::displayInfo(const int id, const std::string difficulty) {
    std::string info = "用户ID: " + std::to_string(id) + "\n难度: " + difficulty;
    displayMessage(info);
}

// 显示消息
void SFMLIO::displayMessage(const std::string& message) {
    window.clear();
    messageText.setString(message);
    window.draw(messageText);
    window.display();
}

// 获取用户输入
std::string SFMLIO::getUserInput() {
    std::string inputText;
    sf::Text userInputDisplay;
    userInputDisplay.setFont(font);
    userInputDisplay.setCharacterSize(24);
    userInputDisplay.setFillColor(sf::Color::Black);
    userInputDisplay.setPosition(10, 10);  // 设置文本显示的位置

    displayMessage("请输入文本，按 Enter 键结束：");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";  // 如果窗口关闭，则返回空字符串
            }

            // 处理文本输入事件
            if (event.type == sf::Event::TextEntered) {
                char inputChar = static_cast<char>(event.text.unicode);

                // 处理退格键删除字符
                if (inputChar == 8 && !inputText.empty()) {  // 8 是退格键
                    inputText.pop_back();  // 删除最后一个字符
                }
                // 检查是否是 Enter 键 (回车键)
                else if (inputChar == '\r' || inputChar == '\n') {  // 回车结束输入
                    return inputText;
                }
                // 过滤控制字符，只接受可打印字符
                else if (inputChar >= 32 && inputChar <= 126) {
                    inputText += inputChar;  // 添加到输入字符串中
                }

                // 更新显示的用户输入文本
                userInputDisplay.setString(inputText);
            }
        }

        window.clear(sf::Color::White);  // 清屏
        window.draw(userInputDisplay);   // 显示用户当前输入的文本
        window.display();                // 刷新显示
    }

    return inputText;  // 如果窗口被关闭，返回当前已输入的内容
}

// 获取操作向量
std::vector<int> SFMLIO::getOperation() {
    displayMessage("请选择一个格子，然后输入数字");

    // 获取用户点击的格子位置
    std::vector<int> position = getUserPosition();

    // 获取用户输入的数字
    int number = getUserInputNumber();

    // 返回操作向量，包含行、列和输入的数字
    return { position[0], position[1], number };
}

// 获取位置
std::vector<int> SFMLIO::getPosition() {
    displayMessage("请选择一个格子");

    // 获取用户点击的格子位置
    return getUserPosition();
}

std::vector<int> SFMLIO::getUserPosition() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return { -1, -1 }; // 关闭窗口时返回无效位置
            }

            // 处理鼠标点击事件
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // 计算点击的行和列
                int row = mouseY / 60;
                int col = mouseX / 60;

                if (row >= 0 && row < 9 && col >= 0 && col < 9) {
                    return { row + 1, col + 1 };  // 返回1-9范围
                }
            }
        }
        window.clear(sf::Color::White);
        window.display();
    }
    return { -1, -1 };  // 默认返回无效位置
}

// 获取数
int SFMLIO::getNumber() {
    return getUserInputNumber();
}

int SFMLIO::getUserInputNumber() {
    displayMessage("请输入一个数字 (1-9)");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;  // 返回无效数字
            }

            // 处理键盘输入事件
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
    return -1;  // 默认返回无效数字
}

// 显示菜单
int SFMLIO::displayMenu(const std::vector<std::string>& options) {
    return getUserChoiceFromMenu(options);
}

int SFMLIO::getUserChoiceFromMenu(const std::vector<std::string>& options) {
    displayMessage("请选择一个选项");

    while (window.isOpen()) {
        window.clear();
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text optionText(options[i], font, 24);
            optionText.setPosition(100, i * 40 + 50);  // 每个选项之间留40像素
            optionText.setFillColor(sf::Color::Black);
            window.draw(optionText);
        }
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;  // 返回无效选项
            }

            // 处理鼠标点击事件，判断点击的菜单项
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseY = event.mouseButton.y;
                int choice = mouseY / 40;
                if (choice >= 0 && choice < static_cast<int>(options.size())) {
                    return choice + 1;
                }
            }

            // 处理键盘输入事件
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

    return -1;  // 默认返回无效选项
}
