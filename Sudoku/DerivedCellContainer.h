#ifndef DERIVEDCELLCONTAINER
#define DERIVEDCELLCONTAINER

// 10月7日：整合Block, Column, Row到这一个文件中

#include "CellContainer.h"

class Block : public CellContainer {
public:
    Block() : CellContainer() {}  // 构造函数继承基类
};

class Column : public CellContainer {
public:
    Column() : CellContainer() {}  // 构造函数继承基类
};

class Row : public CellContainer {
public:
    Row() : CellContainer() {}  // 构造函数继承基类
};


#endif
