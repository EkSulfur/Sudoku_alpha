#ifndef IO_INTERFACE_H
#define IO_INTERFACE_H

#include <vector>
#include <string>

class IOInterface {
public:
    virtual void displayMessage(const std::string& message) const = 0;
    virtual std::string getUserInput() const = 0;
    virtual void displayBoard(const std::vector<int>& board) const = 0;
    virtual ~IOInterface() = default;
};

#endif // IO_INTERFACE_H
