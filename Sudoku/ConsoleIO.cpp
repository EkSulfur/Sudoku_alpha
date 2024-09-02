#include "ConsoleIO.h"

void ConsoleIO::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

std::string ConsoleIO::getUserInput() const {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleIO::displayBoard(const std::vector<int>& board) const {
    for (size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i] << " ";
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }
}
