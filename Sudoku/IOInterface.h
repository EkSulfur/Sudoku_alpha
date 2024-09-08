#ifndef IO_INTERFACE_H
#define IO_INTERFACE_H

#include <string>
#include <vector>
#include "Cell.h"

/*
9��6��
��������IOInterface�����Ҫ�ӿڣ����ʵ�ֹ�����lwh���
����IOInterfaceΪ�ӿ��࣬ʵ�ʵ��޸�Ӧ����ConsoleIO�����
displayMenu��ĿǰӦ�������п�ʼ��Ϸ���˳���ѡ��
�������displaInfo��������ʾĿǰ�Ѷȡ�id������ҿ���������ѡ��������ȣ�
�������һ����ȡ�����ĺ���getOperation������һ��vectot<int>���͵Ĳ�������������ÿ���û��Ĳ���
�����û�����1��������������R1 C1 1�������Ӧλ������1�����麯����������[1, 1, 1, 1]��������˶�Ӧ����
������������ʱӦ����ע��˵��
�����getUserInput�Ҹо�getOperation��������֮��ְ��ķ���
by lch
9��7��
�޸�getOperation�����ã�����û�䣩��Ҫʹ�ó��������������Ƴ���ѡ��ʱ������������֣�Ӧ����һ����ά������
by lch
*/


// IOInterface: �ɸ�����潻����ͬ����ʵ��
class IOInterface {
public:
    virtual ~IOInterface() = default;

    // ��ʾ����
    virtual void displayBoard(const std::vector<std::vector<Cell*>>& board) const = 0;


    //��ʾ��Ϣ
    virtual void displayInfo(const int id, const std::string difficulty) const = 0;

    // ��ʾ��Ϣ
    virtual void displayMessage(const std::string& message) const = 0;

    // ��ȡ�û�����
    virtual std::string getUserInput() const = 0;

    // ��ȡ��������������
    virtual std::vector<int> getOperation() const = 0;

    // ��ȡλ�ã���������
    virtual std::vector<int> getPosition() const = 0;

    // ��ȡ��������һ������
    virtual int getNumber() const = 0;

    // ��ʾ�˵��������û�ѡ��
    virtual int displayMenu(const std::vector<std::string>& options) const = 0;
};

#endif // IO_INTERFACE_H
