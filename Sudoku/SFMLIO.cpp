#include "SFMLIO.h"
#include <iostream>

#include "SFMLIO.h"
#include <iostream>

// 构造函数
SFMLIO::SFMLIO() : window(sf::VideoMode(600, 600), "Sudoku Game") {
    // 加载字体
    if (!font.loadFromFile("NotoSerifSC-Regular.otf")) {
        std::cerr << "无法加载字体" << std::endl;
    }

    // 设置默认消息文本样式
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::White);

    // 设置棋盘格子边框
    cellOutline.setSize(sf::Vector2f(60, 60));  // 格子大小为60x60
    cellOutline.setFillColor(sf::Color::Transparent);
    cellOutline.setOutlineThickness(1);
    cellOutline.setOutlineColor(sf::Color::White);
}

// 析构函数
SFMLIO::~SFMLIO() {
    if (window.isOpen()) {
        window.close();
    }
}

// 显示棋盘
void SFMLIO::displayBoard(const std::vector<std::vector<Cell*>>& board) {
    window.clear(sf::Color::Black);  // 背景色设为黑色
    int gridSize = 9;
    int cellSize = 60;  // 每个格子的像素大小
    int fontSize = 12;  // 候选数字的字体大小
    int valueFontSize = 24;  // 已确定数字的字体大小

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // 计算每个格子的绘制位置
            int x = j * cellSize;
            int y = i * cellSize;
            cellOutline.setPosition(x, y);

            // 绘制边框
            window.draw(cellOutline);

            // 获取当前单元格
            Cell* cell = board[i][j];

            if (cell->isSolved()) {
                // 已确定的数值，绘制在格子中心
                sf::Text cellValue;
                cellValue.setFont(font);
                cellValue.setCharacterSize(valueFontSize);  // 设置字符大小为24
                cellValue.setFillColor(sf::Color::Green);  // 颜色设为绿色
                cellValue.setString(std::to_string(cell->getValue()));  // 显示该格子的值
                cellValue.setPosition(x + cellSize / 3, y + cellSize / 4);  // 将文本居中
                window.draw(cellValue);
            }
            else {
                // 候选数处理
                const std::vector<int>& candidates = cell->getCandidates();
                for (int k = 1; k <= 9; ++k) {
                    if (cell->hasCandidate(k)) {
                        // 每个候选数都按位置绘制到格子的某个小区域
                        sf::Text candidateText;
                        candidateText.setFont(font);
                        candidateText.setCharacterSize(fontSize);  // 设置候选数字体大小
                        candidateText.setFillColor(sf::Color::White);  // 颜色为白色
                        candidateText.setString(std::to_string(k));

                        // 计算候选数字在格子内的位置 (3x3 小格子内布局)
                        int candidateX = x + ((k - 1) % 3) * (cellSize / 3) + 10;
                        int candidateY = y + ((k - 1) / 3) * (cellSize / 3) + 5;

                        candidateText.setPosition(candidateX, candidateY);
                        window.draw(candidateText);  // 绘制候选数字
                    }
                }
            }
        }
    }

    // 绘制粗线来区分 3x3 区块
    sf::RectangleShape thickLine;
    thickLine.setFillColor(sf::Color::White);
    thickLine.setSize(sf::Vector2f(4, 600));  // 竖线
    for (int k = 1; k <= 2; ++k) {
        thickLine.setPosition(k * 3 * cellSize, 0);
        window.draw(thickLine);
    }
    thickLine.setSize(sf::Vector2f(600, 4));  // 横线
    for (int k = 1; k <= 2; ++k) {
        thickLine.setPosition(0, k * 3 * cellSize);
        window.draw(thickLine);
    }

    window.display();  // 刷新窗口显示
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
