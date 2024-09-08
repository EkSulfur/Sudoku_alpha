#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include <iostream>

class ConsoleIO : public IOInterface {
public:
    void displayMessage(const std::string& message) const override;
    std::string getUserInput() const override;
    void displayBoard(const std::vector<std::vector<Cell*>>& board) const override;
    int displayMenu(const std::vector<std::string>& options) const override;
};

#endif // CONSOLE_IO_H