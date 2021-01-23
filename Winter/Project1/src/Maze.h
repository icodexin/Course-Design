#pragma once
#include <iostream>

#define MAXLEN 10

// 坐标位置类
struct Pos {
    int i; // 行号
    int j; // 列号
    // 重载 "==" 运算符，用于判断两个位置是否相等
    bool operator==(const Pos &right) const;
    // 构造函数，初始化一个坐标
    Pos();
    // 有参构造函数，初始化一个坐标
    Pos(int i, int j);
    // 将坐标信息转换为字符串
    std::string to_String();
};

// 迷宫类
class Maze {
private:
    int r;                    // 行数
    int c;                    // 列数
    char map[MAXLEN][MAXLEN]; // 迷宫矩阵,外围全是1,0通路1强

public:
    // 构造函数
    Maze();
    // 构造函数，初始化迷宫
    Maze(int r, int c, char map[MAXLEN][MAXLEN]);
    // 获取行数
    int getRow();
    // 获取列数
    int getCol();
    // 设置行数
    void setRow(int row);
    // 设置列数
    void setCol(int col);
    // 设置迷宫矩阵某坐标元素值
    void setMapValue(Pos pos, char value);
    // 获取迷宫矩阵某坐标元素值
    char getMapValue(Pos pos);
    // 某坐标是否通路
    bool canPass(Pos pos);
};

// 通道块
struct Block {
    int ord{0};     // 通道块在路径上的“序号”
    Pos seat{0, 0}; // 通道块在迷宫中的“坐标位置”
    int di{0};      // 从此通道块走向下一通道块的“方向”,东0南1西2北3
    // 构造函数，初始化通道块
    Block();
    // 有参构造函数，初始化通道块
    Block(int ord, Pos seat, int di);
    // 设置通道块
    void setBlock(int ord, Pos seat, int di);
    // 将通道块信息转换为字符串
    std::string to_String();
    // 重载"<<"运算符,用于输出通道块类信息到输出流中
    friend std::ostream &operator<<(std::ostream &out, Block block);
};