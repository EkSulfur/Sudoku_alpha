#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include <iostream>

class ConsoleIO : public IOInterface {
public:
    void displayMessage(const std::string& message) const override;
    std::string getUserInput() const override;
    void displayBoard(const std::vector<int>& board) const override;
};

#endif // CONSOLE_IO_H
