#include "Maze.h"
#include "Stack.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using Status = bool;

// 菜单函数
int menu();

// 手动输入或从文件导入迷宫
void InputMaze();

// 输入迷宫
void InputMaze(Maze &maze, std::istream &In);

// 非递归搜索
Status MazePath(Maze &maze, Pos start, Pos end);

// 递归搜索
void ReMazepath(Pos start, Pos end);

/**
 * @brief 输入迷宫
 * @param maze 迷宫对象，将输入到此对象中
 * @param In 流对象，从此流对象输入到maze中
*/
void InputMaze(Maze &maze, std::istream &In);

// 下一相邻方块
Pos NextPos(Pos curpos, int i);

// 打印迷宫路程图
void PrintMaze(Maze &maze);

int dir[][2] = {{0, 1},   // 东
                {1, 0},   // 南
                {0, -1},  // 西
                {-1, 0}}; // 北
Maze maze;                // 迷宫对象
Stack<Block> S;           // 栈对象
int count = 0;            // 递归搜索路径计数

int main() {
    while (true) {
        switch (menu()) {
            case 1: {
                InputMaze();
                Pos start, end;
                cout << "输入入口位置:";
                cin >> start.i >> start.j;
                cout << "输入出口位置:";
                cin >> end.i >> end.j;
                auto flag = MazePath(maze, start, end);
                if (flag) {
                    PrintMaze(maze);
                } else {
                    cout << "*****    此迷宫无法从起点走到终点。   ******\n";
                }
            } break;
            case 2: {
                InputMaze();
                Pos start, end;
                cout << "输入入口位置:";
                cin >> start.i >> start.j;
                cout << "输入出口位置:";
                cin >> end.i >> end.j;
                ReMazepath(start, end);
            } break;
            case 0:
                cout << "程序结束，谢谢使用！" << endl;
                exit(0);
        }
    }
    return 0;
}

int menu() {
    auto sn{0};
    cout << endl
         << "<---------------显示菜单---------------" << endl
         << "1. 非递归搜索迷宫通路路径" << endl
         << "2. 递归搜搜迷宫通路路径" << endl
         << "0. 结束程序" << endl
         << "---------------显示菜单--------------->" << endl
         << "输入0-2:";
    while (true) {
        cin >> sn;
        if (sn < 0 || sn > 2)
            cout << "输入错误，重选0－2:" << endl;
        else
            break;
    }
    return sn;
}

void InputMaze() {
    auto way{0};
    cout << "0手动输入,1从文件导入:";
    while (true) {
        cin >> way;
        if (way < 0 || way > 1)
            cout << "输入错误，重新输入0或1:" << endl;
        else
            break;
    }
    if (way) {
        std::string filename;
        cout << "输入文件名:";
        cin >> filename;
        std::ifstream InputFile;
        InputFile.open(filename);
        if (!InputFile.is_open()) {
            std::cerr << "没有找到文件" << filename << endl;
            exit(1);
        }
        InputMaze(maze, InputFile);
        InputFile.close();
    } else {
        cout << "输入行数、列数、迷宫矩阵:" << endl;
        InputMaze(maze, std::cin);
    }
}

void InputMaze(Maze &maze, std::istream &In) {
    auto row{0}, col{0};
    In >> row >> col;
    maze.setRow(row);
    maze.setCol(col);
    char value;
    for (int i = 0; i < maze.getRow(); i++) {
        for (int j = 0; j < maze.getRow(); j++) {
            In >> value;
            maze.setMapValue(Pos{i, j}, value);
        }
    }
}

Status MazePath(Maze &maze, Pos start, Pos end) {
    Stack<Block> S;     // 实例化一个栈对象
    Pos curpos = start; // 当前坐标
    Block e;            // 实例化一个通道块对象
    int curstep = 1;    // 探索步骤

    do {
        if (maze.canPass(curpos)) {         // 当前位置可通过
            maze.setMapValue(curpos, '*');  // 留下足迹
            e.setBlock(curstep, curpos, 0); // 设置待入栈的通道块

            S.push(e); // 入栈
            // 到达终点(出口)
            if (curpos == end) {
                S.print();
                return true;
            }
            // 下一位置是当前位置的东邻
            curpos = NextPos(curpos, 0);
            // 探索下一步
            curstep++;
        } else { // 当前不能通过
            if (!S.isEmpty()) {
                S.pop(e); // 出栈
                while (e.di == 3 && !S.isEmpty()) {
                    if (maze.getMapValue(e.seat) != '@')
                        maze.setMapValue(e.seat, '.');
                    S.pop(e); // 出栈，回退一步
                }
                if (e.di < 3) {
                    e.di++; // 换下一个方向探索
                    S.push(e);
                    // 设定当前位置是该新方向上的相邻块
                    curpos = NextPos(e.seat, e.di);
                }
            }
        }
    } while (!S.isEmpty());
    return false;
}

void ReMazepath(Pos start, Pos end) {
    if (start == end) {
        // 放入终点
        maze.setMapValue(start, '*');
        S.push(Block{S.getSize() + 1, start, 1});
        cout << "找到第" << ++count << "条通路:" << endl;
        S.print();
        PrintMaze(maze);
        // 退出栈，找下一条路径
        S.pop();
        // 恢复原值
        maze.setMapValue(start, '.');
    } else {
        if (maze.canPass(start)) {
            int di = 0;
            while (di < 4) {
                // 加入当前方块
                S.push(Block{S.getSize() + 1, start, di});
                // 下一位置
                Pos next = NextPos(start, di);
                // 避免来回走动
                maze.setMapValue(start, '*');
                // 递归
                ReMazepath(next, end);
                // 退出栈，找其他元素
                S.pop();
                // 恢复原值
                maze.setMapValue(start, '.');
                di++;
            }
        }
    }
}

Pos NextPos(Pos curpos, int i) {
    Pos ret = curpos;
    // 新坐标
    ret.i += dir[i][0];
    ret.j += dir[i][1];
    return ret;
}

void PrintMaze(Maze &maze) {
    std::cout << "迷宫路程图: \n";
    for (int i = 0; i < maze.getRow(); i++) {
        std::cout << "      ";
        for (int j = 0; j < maze.getCol(); j++) {
            std::cout << std::setw(2) << maze.getMapValue(Pos{i, j});
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}