//
// Created by hsing on 2020/11/19.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include "sqlist.h"

using namespace std;

#define setLeft setiosflags(ios::left)

// 初始化一个空的动态顺序表
Status InitSqList(SqList &L, int n) {
    auto listsize{((n / 10) + 1) * 10}; // 确定顺序表初始内存占用空间
    L.elem = new ElemType[listsize];    // 分配基地址、顺序表内存
    if (!L.elem)    // 内存不足
        return OVERFLOW;
    L.length = 0;   // 此时顺序表还没有元素，L.length为0
    L.listsize = listsize;
    return OK;
}

// 创建仓库
void CreateWarehouse(SqList &L, int n, int sort_way) {
    cout << "请输入这" << n << "种电脑各自的型号、单价、总数:(以空格分隔)" << endl;
    // 输入n个数据元素
    for (int i = 0; i < n; i++)
        cin >> L.elem[i].type >> L.elem[i].price >> L.elem[i].number;
    // 按照sort_way对刚创建的顺序表排序
    switch (sort_way) {
        case 1:
            // 按价格升序
            sort(L.elem, L.elem + n, cmp1);
            break;
        case 2:
            // 按价格降序
            sort(L.elem, L.elem + n, cmp2);
            break;
        case 3:
            // 按数量升序
            sort(L.elem, L.elem + n, cmp3);
            break;
        case 4:
            // 按数量降序
            sort(L.elem, L.elem + n, cmp4);
            break;
        default:
            break;
    }
    // 更新L的参数
    L.sortWay = sort_way;
    L.length = n;
    L.isInit = true;
}

// 从文件流创建仓库
void CreateWarehouse(SqList &L, int n, int sort_way, ifstream &ImportFile) {
    string s;
    // 从文件流输入n个数据元素
    for (int i = 0; i < n; i++) {
        ImportFile >> L.elem[i].type >> L.elem[i].price >> L.elem[i].number;
        getline(ImportFile, s);
    }
    // 按照sort_way对刚创建的顺序表排序
    switch (sort_way) {
        case 1:
            sort(L.elem, L.elem + n, cmp1);
            break;
        case 2:
            sort(L.elem, L.elem + n, cmp2);
            break;
        case 3:
            sort(L.elem, L.elem + n, cmp3);
            break;
        case 4:
            sort(L.elem, L.elem + n, cmp4);
            break;
        default:
            break;
    }
    // 更新L的参数
    L.sortWay = sort_way;
    L.length = n;
    L.isInit = true;
}

// 显示仓库
void PrintWarehouse(SqList L) {
    if (!L.length)
        cout << "当前仓库没有数据!" << endl;
    else {
        cout << "当前仓库数据如下:" << endl;
        string sort_way;
        switch (L.sortWay) {
            case 1:
                sort_way = "(按照价格升序)";
                break;
            case 2:
                sort_way = "(按照价格降序)";
                break;
            case 3:
                sort_way = "(按照数量升序)";
                break;
            case 4:
                sort_way = "(按照数量降序)";
                break;
            default:
                break;
        }
        cout << sort_way << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << setLeft
             << setw(5) << "序号"
             << setw(20) << "型号"
             << setw(15) << "单价"
             << setw(15) << "数量"
             << endl;
        cout << "-------------------------------------------------------" << endl;
        for (int i = 0; i < L.length; i++)
            cout << setLeft
                 << setw(5) << i + 1
                 << setw(20) << L.elem[i].type
                 << setw(15) << L.elem[i].price
                 << setw(15) << L.elem[i].number
                 << endl;
        cout << "-------------------------------------------------------" << endl;
    }
}

// 入库
Status Enter(SqList &L, const Computer &c) {
    // 寻找仓库中是否已经有和c.type同类型的电脑
    for (int i = 0; i < L.length; i++) {
        if (strcmp(c.type, L.elem[i].type) == 0) {
            if (c.price == L.elem[i].price) {   // 检查价格价格是否与c.price相等
                L.elem[i].number += c.number;
                return OK;
            } else {
                cout << "提示:" << endl;
                showInfo(L.elem[i]);
                return ERROR;
            }

        }
    }

    // 入库一个新类型的电脑
    if (L.length >= L.listsize) {   // 顺序表占用空间不足
        // 申请新的基地址、内存空间
        auto *newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return OVERFLOW;
        L.elem = newbase;   // L的基地址更改为newbase
        L.listsize += LISTINCREMENT;
    }
    // 按照L.sort_way对插入到顺序表中
    int item{L.length}; // 确定要插入的位序
    for (int i = 0; i < L.length; i++) {
        switch (L.sortWay) {
            case 1: {
                if (c.price < L.elem[i].price) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 2: {
                if (c.price > L.elem[i].price) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 3: {
                if (c.number < L.elem[i].number) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 4: {
                if (c.number > L.elem[i].number) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
        }
    }
    change_sq:
    ElemType *q = &L.elem[item];
    // 将q及q以后的元素全部后移一位
    for (ElemType *p = L.elem + L.length - 1; p >= q; p--)
        *(p + 1) = *p;
    // 将新元素赋给q
    *q = c;
    L.length++;
    return OK;
}

// 出库
Status Out(SqList &L, const char *type, int num) {
    // 确定要出库元素的位序
    int item{L.length + 1};
    for (int i = 0; i < L.length; i++) {
        if (strcmp(type, L.elem[i].type) == 0) {
            item = i;
            break;
        }
    }
    // 没有找到要出库元素的位序，说明在仓库中没有元素，返回错误
    if (item > L.length)
        return -1;

    // 确定要出库元素现有库存的数量是否可以出库
    if (num < L.elem[item].number) {
        // 正常出库
        L.elem[item].number -= num;
        return OK;
    } else if (num == L.elem[item].number) {
        // 全部出库
        cout << "提示:" << endl
             << L.elem[item].type << "型号的电脑已全部出库!" << endl;

        // 将p及p以后的元素全部后移一位
        for (ElemType *p = &L.elem[item + 1]; p <= &L.elem[L.length - 1]; p++) {
            *(p - 1) = *p;
        }
        L.length--;
        return OK;
    } else {
        // 库存不足
        cout << "提示:" << endl;
        showInfo(L.elem[item]);
        return ERROR;
    }
}

// 盘点仓库
void Check(SqList L) {
    int numSum{0};
    double priceSum{0.0}, priceMax{L.elem[0].price}, priceMin{L.elem[0].price}, priceAverage{0.0};
    vector<char *> priceMaxComputer;    // 存储价格最高的电脑的类型名
    vector<char *> priceMinComputer;    // 存储价格最低的电脑的类型名

    if (!L.length) {
        cout << "当前仓库没有数据!" << endl;
    } else {
        // 求总数、总金额、最高价、最低价
        for (int i = 0; i < L.length; i++) {
            numSum += L.elem[i].number;
            priceSum += L.elem[i].price * L.elem[i].number;
            priceMax = max(priceMax, L.elem[i].price);
            priceMin = min(priceMin, L.elem[i].price);
        }
        // 记录价格最高、最低的电脑类型名
        for (int i = 0; i < L.length; i++) {
            if (L.elem[i].price == priceMax)
                priceMaxComputer.push_back(L.elem[i].type);
            if (L.elem[i].price == priceMin)
                priceMinComputer.push_back(L.elem[i].type);
        }
        // 求平均价
        priceAverage = priceSum / numSum;
        // 输出信息
        cout << "盘点数据如下" << endl
             << "电脑的总台数: " << numSum << endl
             << "电脑的总金额: " << priceSum << endl
             << "电脑的最高价: " << priceMax << endl
             << "           + 对应的型号是: ";
        for (const auto &c:priceMaxComputer)
            cout << c << "\t";
        cout << endl;
        cout << "电脑的最低价: " << priceMin << endl
             << "           + 对应的型号是: ";
        for (const auto &c:priceMinComputer)
            cout << c << "\t";
        cout << endl;
        cout << "电脑的平均价格: " << priceAverage << endl;
    }
}

// computer排序方式：按价格升序
bool cmp1(const Computer &a, const Computer &b) {
    return a.price < b.price;
}

// computer排序方式：按价格降序
bool cmp2(const Computer &a, const Computer &b) {
    return a.price > b.price;
}

// computer排序方式：按数量升序
bool cmp3(const Computer &a, const Computer &b) {
    return a.number < b.number;
}

// computer排序方式：按数量降序
bool cmp4(const Computer &a, const Computer &b) {
    return a.number > b.number;
}

// 输出仓库数据到文件中
void output(SqList L, const string &filename) {
    // 定义输出文件流filename.txt
    ofstream OutFile(filename + ".txt");
    // 输出文件头，用于下次输入时识别文件
    OutFile << "Computer Warehouse Data" << endl;
    if (!L.length)
        OutFile << "no data" << endl;
    else {
        OutFile << "The information is as follows:" << endl;
        switch (L.sortWay) {
            case 1:
                OutFile << "Sort Way: 1 (Ascending by price)" << endl;
                break;
            case 2:
                OutFile << "Sort Way: 2 (Descending by price)" << endl;
                break;
            case 3:
                OutFile << "Sort Way: 3 (Ascending by number)" << endl;
                break;
            case 4:
                OutFile << "Sort Way: 4 (Descending by number)" << endl;
                break;
            default:
                break;
        }
        OutFile << "Total Type: " << L.length << endl;

        // 输出数据信息
        for (int i = 0; i < L.length; i++)
            OutFile << L.elem[i].type << " "
                    << L.elem[i].price << " "
                    << L.elem[i].number
                    << endl;
        // 关闭文件
        OutFile.close();
    }
}

// 从外部文件导入数据到仓库
Status Import(SqList &L, const string &filename) {
    // 定义输入输入文件流filename.txt
    ifstream InFile;
    InFile.open(filename + ".txt");
    // 检查文件是否存在
    if (!InFile.is_open()) {
        InFile.close();
        return ERROR;
    }
    auto sort_way{0}, n{0};
    // 检查文件头是否正确，同时返回仓库排序方式、电脑类型总数
    switch (getFileHead(InFile, sort_way, n)) {
        case OK:
            break;
        case 2:
            return 2;
        case 3:
            return 3;
    }
    if (!InitSqList(L, n))
        return OVERFLOW;
    else
        // 调用函数CreateWarehouse创建仓库
        CreateWarehouse(L, n, sort_way, InFile);
    InFile.close();
    return OK;
}

// 检查外部文件头
Status getFileHead(ifstream &ImportFile, int &sort_way, int &total_type) {
    string s;
    getline(ImportFile, s);
    if (s != "Computer Warehouse Data") {
        ImportFile.close();
        return 2;
    }
    getline(ImportFile, s);
    if (s == "no data") {
        ImportFile.close();
        return 3;
    }
    if (s != "The information is as follows:") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Sort") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Way:") {
        ImportFile.close();
        return 2;
    }

    ImportFile >> sort_way;
    if (sort_way < 1 || sort_way > 4)
        return 2;
    getline(ImportFile, s);

    ImportFile >> s;
    if (s != "Total") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Type:") {
        ImportFile.close();
        return 2;
    }

    ImportFile >> total_type;
    if (total_type < 1)
        return 2;

    getline(ImportFile, s);
    return OK;
}

// 获取电脑信息
void getInfo(SqList L, const char *type) {
    // 确定要查找的电脑的元素位序
    int item{L.length + 1};
    for (int i = 0; i < L.length; i++) {
        if (strcmp(type, L.elem[i].type) == 0) {
            item = i;
            break;
        }
    }
    if (item > L.length)
        cout << "没有找到" << type << "型号的电脑" << endl;
    else {
        cout << "信息如下:" << endl;
        showInfo(L.elem[item]);
    }
}

// 显示电脑信息
void showInfo(Computer c) {
    cout << "--------------------------------------------------" << endl
         << setLeft << setw(20) << "型号" << setw(15) << "单价" << setw(15) << "现有库存数量" << endl
         << "--------------------------------------------------" << endl
         << setLeft << setw(20) << c.type << setw(15) << c.price << setw(15) << c.number << endl
         << "--------------------------------------------------" << endl;
}