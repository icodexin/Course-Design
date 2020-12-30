#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include "sqlist.h"

using namespace std;

/********************函数声明********************/
// 菜单
int menu();

// 输入from至end范围内的数字
int input_number(int from, int end);

// 输入大于from的数字
int input_number(int from);

/********************函数声明********************/

// 主函数
int main() {
    cout << "欢迎使用电脑仓库管理系统！" << endl;

    // 定义顺序表L
    SqList L;

    // 根据菜单选择实现对应功能
    while (true) {
        switch (menu()) {
            // 初始化仓库
            case 1: {
                // 检查仓库是否已经创建
                if (L.isInit) {
                    cout << "仓库已创建过!" << endl;
                    break;
                }

                cout << "选择创建仓库的方式" << endl
                     << "1.手动输入  2.从外部文件导入" << endl
                     << "选择1-2:";
                auto sn = input_number(1, 2);

                if (sn == 1) {  // 手动创建仓库
                    cout << "请输入电脑的类型数:";
                    auto n = input_number(1);

                    if (!InitSqList(L, n)) {
                        cout << "创建仓库失败!" << endl
                             << "原因: 内存不足。" << endl;
                    } else {
                        cout << "请输入仓库排序的主要方式" << endl
                             << "1. 按价格升序 2. 按价格降序" << endl
                             << "3. 按数量升序 4. 按数量降序" << endl
                             << "选择1-4:";
                        auto select = input_number(1, 4);
                        CreateWarehouse(L, n, select);
                        cout << "创建仓库成功!" << endl
                             << "您可以选择菜单2以显示仓库" << endl;
                    }
                } else { // 从文件创建仓库
                    cout << "请输入文件名(无需文件名后缀):";
                    string filename;
                    cin >> filename;
                    switch (Import(L, filename)) {
                        case OK: {
                            string sort_way;
                            cout << "导入成功!" << endl;
                            switch (L.sortWay) {
                                case 1:
                                    sort_way = "按照价格升序排序。";
                                    break;
                                case 2:
                                    sort_way = "按照价格降序排序。";
                                    break;
                                case 3:
                                    sort_way = "按照数量升序排序。";
                                    break;
                                case 4:
                                    sort_way = "按照数量降序排序。";
                                    break;
                            }
                            cout << "按照文件要求: 仓库数据" + sort_way << endl;
                            cout << "您可以选择菜单2以显示仓库。" << endl;
                        }
                            break;
                        case ERROR:
                            cout << "导入失败!" << endl
                                 << "原因: 没有" << filename << ".txt这个文件 / " << filename << ".txt文件无法打开。" << endl;
                            break;
                        case 2:
                            cout << "导入失败!" << endl
                                 << "原因: " << filename << ".txt文件内容不符合要求。" << endl;
                            break;
                        case 3:
                            cout << "导入失败!" << endl
                                 << "原因: " + filename + ".txt文件没有数据。" << endl;
                            break;
                        case OVERFLOW:
                            cout << "导入失败!" << endl
                                 << "原因: 内存不足。" << endl;
                            break;
                    }
                }
            }
                break;

            // 显示仓库
            case 2:
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                PrintWarehouse(L);
                break;

            // 入库
            case 3: {
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                cout << "请输入要入库的电脑型号、单价、总数:" << endl;
                Computer c;
                cin >> c.type >> c.price >> c.number;
                switch (Enter(L, c)) {
                    case OK:
                        cout << "入库成功!" << endl;
                        break;
                    case ERROR:
                        cout << "无法入库！" << endl
                             << "原因: 输入的" << c.type << "型号电脑的单价" << c.price << "与库存中单价不一致。" << endl;
                        break;
                    case OVERFLOW:
                        cout << "入库失败!" << endl
                             << "原因: 内存不足。" << endl;
                        break;
                }
            }
                break;

            // 出库
            case 4: {
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                cout << "请输入要出库的电脑型号、数量:" << endl;
                char type[50];
                int num{0};
                cin >> type >> num;
                if (num <= 0) {
                    cout << "无法出库!" << endl
                         << "原因: 数量输入小于等于0" << endl;
                    break;
                }
                switch (Out(L, type, num)) {
                    case OK:
                        cout << "出库成功!" << endl;
                        break;
                    case -1:
                        cout << "出库失败!" << endl
                             << "原因: " << type << "型号的电脑不在仓库中!" << endl;
                        break;
                    case ERROR:
                        cout << "无法出库!" << endl
                             << "原因: 要出库的数量" << num << "大于库存中的数量。" << endl;
                        break;
                }
            }
                break;

            // 查询
            case 5: {
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                cout << "请输入要查询的电脑型号:";
                char type[50];
                cin >> type;
                getInfo(L, type);
            }
                break;

            // 盘点仓库
            case 6:
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                Check(L);
                break;

            // 对仓库重新排序
            case 7: {
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                cout << "请输入要重新对仓库排序的主要方式" << endl
                     << "1. 按价格升序 2. 按价格降序" << endl
                     << "3. 按数量升序 4. 按数量降序" << endl
                     << "选择1-4:";
                auto select = input_number(1, 4);
                switch (select) {
                    case 1:
                        sort(L.elem, L.elem + L.length, cmp1);
                        break;
                    case 2:
                        sort(L.elem, L.elem + L.length, cmp2);
                        break;
                    case 3:
                        sort(L.elem, L.elem + L.length, cmp3);
                        break;
                    case 4:
                        sort(L.elem, L.elem + L.length, cmp4);
                        break;
                    default:
                        break;
                }
                L.sortWay = select;
                cout << "重新排序成功!" << endl;
            }
                break;

            // 导出仓库数据到文件
            case 8: {
                // 检查仓库是否已经创建
                if (!L.isInit) {
                    cout << "仓库还未初始化!" << endl;
                    break;
                }
                cout << "请输入要保存的文件名(无需文件名后缀):";
                string filename;
                cin >> filename;
                output(L, filename);
                cout << "已成功将仓库数据保存在程序所在文件夹的" << filename << ".txt。" << endl;
            }
                break;

            // 结束程序
            case 0:
                cout << "程序结束，谢谢使用！" << endl;
                system("Pause");
                exit(0);
        }
    }
}

// 菜单
int menu() {
    cout << endl
         << "<---------------显示菜单---------------" << endl
         << "1. 初始化仓库" << endl
         << "2. 显示仓库" << endl
         << "3. 入库" << endl
         << "4. 出库" << endl
         << "5. 查询" << endl
         << "6. 盘点仓库" << endl
         << "7. 重新对仓库排序" << endl
         << "8. 导出仓库数据到文件" << endl
         << "0. 结束程序" << endl
         << "---------------显示菜单--------------->" << endl
         << "输入0-8:";
    return input_number(0, 8);
}

// 输入from至end范围内的数字
int input_number(int from, int end) {
    auto select{0};
    string input;
    regex r("[0-9]*");  // 正则表达式:数字0-9，可以出现多次
    while (true) {
        cin >> input;
        bool isNumber = regex_match(input,r);
        if (!isNumber)  // 如果input和正则表达式匹配
            cout << "输入错误，请输入数字" << from << "-" << end << ":";
        else {
            select = atoi(input.c_str());
            if (select < from || select > end)
                cout << "输入错误，重新输入" << from << "-" << end << ":";
            else
                break;
        }
    }
    return select;
}

// 输入大于from的数字
int input_number(int from) {
    auto number{0};
    string input;
    regex r("[0-9]*");  // 正则表达式:数字0-9，可以出现多次
    while (true) {
        cin >> input;
        bool isNumber = regex_match(input,r);
        if (!isNumber)  // 如果input和正则表达式匹配
            cout << "输入错误，请输入数字:";
        else {
            number = atoi(input.c_str());
            if (number < from)
                cout << "输入错误，重新输入:";
            else
                break;
        }
    }
    return number;
}