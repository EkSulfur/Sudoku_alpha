#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IOInterface.h"
#include <iostream>
#include <vector>

class ConsoleIO : public IOInterface {
public:
    // ��ʾ����
    void displayBoard(const std::vector<std::vector<Cell*>>& board) const override;

    // ��ʾ��Ϣ
    void displayInfo(const int id, const std::string difficulty) const override;

    // ��ʾ��Ϣ
    void displayMessage(const std::string& message) const override;

    // ��ȡ�û�����
    std::string getUserInput() const override;

    // ��ȡ�û����������ز�������
    std::vector<int> getOperation() const override;

    // ��ʾ�˵��������û�ѡ��
    int displayMenu(const std::vector<std::string>& options) const override;
};

#endif // CONSOLE_IO_H
