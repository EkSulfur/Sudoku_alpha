#include "GameApplication.h"
#include "ConsoleGameComponentsFactory.h"
#include <iostream>

int main() {
    // 创建具体工厂
    GameComponentsFactory* factory = new ConsoleGameComponentsFactory();

    // 指定所需的格式（可以从配置文件或用户输入中获取）
    std::string format = "DAT"; // 这里以 DAT 为例

    try {
        // 创建游戏应用程序，传入格式信息
        GameApplication game(factory, format);

        // 启动游戏
        game.startGame();

        // game 析构函数会自动清理资源
    }
    catch (const std::exception& ex) {
        // 处理异常，例如不支持的格式
        std::cerr << "Error: " << ex.what() << std::endl;
        delete factory; // 确保释放工厂资源
        return 1;
    }

    return 0;
}
