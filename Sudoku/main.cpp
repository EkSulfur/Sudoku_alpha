/*
先前的 main 函数中包含了组件的创建和初始化逻辑，确实有些繁琐，这可能违反了面向对象编程中的封装原则。
按照封装的理念，我们希望隐藏对象的创建和初始化细节，只提供必要的接口供使用者调用。
为了解决这个问题，我们可以设计一个单一的、高层次的接口类 GameApplication，它负责初始化所有的组件，并提供一个简单的接口来启动游戏。
这样，main 函数只需要实例化一个对象并调用 startGame 方法，具体的实现细节都被封装在 GameApplication 内部。
*/

#include "GameApplication.h"

int main() {

    // 创建游戏应用程序
    GameApplication app;

    // 启动游戏
    app.startGame();

    // 智能指针会自动清理资源

    return 0;
}