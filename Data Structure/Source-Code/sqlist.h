//
// Created by hsing on 2020/11/19.
//

#ifndef SQLIST_H
#define SQLIST_H

#include <string>
#include <fstream>

using namespace std;

/********************宏定义********************/
#define OK 1        // 正确
#define ERROR 0     // 错误
#define OVERFLOW -2 // 溢出

#define LISTINCREMENT 5    // 顺序表存储空间的分配增量
/********************宏定义********************/

/********************数据结构定义********************/
using Status = int; // 状态参数

// 基本元素: computer
typedef struct computer {
    char type[50];  // 型号
    double price;   // 价格
    int number;     // 数量
} Computer, ElemType;

// 顺序表: SqList
typedef struct {
    ElemType *elem;     // 基地址
    int length;         // 当前有效数据的个数
    int listsize;       // 当前存储容量(单位是sizeof(ElemType))
    bool isInit{false}; // 有序表是否已经初始化
    int sortWay{1};     // 有序表的排序方式
} SqList;
/********************数据结构定义********************/


/********************函数声明********************/
// 初始化一个空的动态顺序表
Status InitSqList(SqList &L, int n);

// 创建仓库
void CreateWarehouse(SqList &L, int n, int sort_way);

// 从文件流创建仓库
void CreateWarehouse(SqList &L, int n, int sort_way, ifstream &ImportFile);

// 显示仓库
void PrintWarehouse(SqList L);

// 入库
Status Enter(SqList &L, const Computer &c);

// 出库
Status Out(SqList &L, const char *type, int num);

// 盘点仓库
void Check(SqList L);

// computer排序方式：按价格升序
bool cmp1(const Computer &a, const Computer &b);

// computer排序方式：按价格降序
bool cmp2(const Computer &a, const Computer &b);

// computer排序方式：按数量升序
bool cmp3(const Computer &a, const Computer &b);

// computer排序方式：按数量降序
bool cmp4(const Computer &a, const Computer &b);

// 输出仓库数据到文件中
void output(SqList L, const string &filename);

// 从外部文件导入数据到仓库
Status Import(SqList &L, const string &filename);

// 检查外部文件头
Status getFileHead(ifstream &ImportFile, int &sort_way, int &total_type);

// 获取电脑信息
void getInfo(SqList L, const char *type);

// 显示电脑信息
void showInfo(Computer c);
/********************函数声明********************/
#endif //SQLIST_H
