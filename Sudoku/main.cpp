// master.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "Sudoku.h"
#include "ConsoleIO.h"
#include "SFMLIO.h"
#include "PuzzleLoaderDAT.h"

int main() {
    // ��������̨��������ӿ�
    //ConsoleIO consoleIO;

    // ����SFML�ӿ�
    SFMLIO sfmlIO;

    // ����DAT��ʽ��PuzzleLoader
    PuzzleLoaderDAT puzzleLoader;

    // ����Sudoku��Ϸʵ��
    Sudoku game(&sfmlIO, &puzzleLoader);

    game.play();

    return 0;
}


//#include <iostream>
//#include <vector>
//#include <string>
//#include "testLoader.h"
//
//
//int main() {
//    testPuzzleLoader();
//    return 0;
//}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

//����SFML

//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}