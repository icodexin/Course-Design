#pragma once
#include <array>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// 哈夫曼树结点
struct HTNode {
    string ch{""};                          // 字符
    size_t weight{0};                       // 权值
    size_t lchild{0}, rchild{0}, parent{0}; // 父、子结点序号
};

// 哈夫曼编码树类
class Huffman {
private:
    HTNode *tree; // 以动态数组存储哈夫曼树
    size_t size;  // 字符数
    string *code; // 哈夫曼编码表

    // 构造函数
public:
    // 默认构造一棵空树
    Huffman() {
        tree = nullptr;
        size = 0;
        code = nullptr;
    }

    // 从字符数组和权值数组中构造一棵哈夫曼树
    Huffman(int n, string *_ch, size_t *_weight) {
        init(n, _ch, _weight);
        enCode();
    }

    // 从输入流中构造哈夫曼树
    Huffman(std::istream &is) {
        size_t n;
        is >> n;
        auto _ch = new string[n];
        auto _weight = new size_t[n];
        for (size_t i = 0; i < n; i++)
            is >> _ch[i] >> _weight[i];
        init(n, _ch, _weight);
        delete[] _ch;
        delete[] _weight;
        enCode();
    }

    // 移动复制
    Huffman &operator=(Huffman &&h) noexcept {
        delete[] tree;
        delete[] code;
        tree = h.tree;
        size = h.size;
        code = h.code;
        h.tree = nullptr;
        h.code = nullptr;
        h.size = 0;
        return *this;
    }

    // 析构函数
    ~Huffman() {
        delete[] tree;
        delete[] code;
        tree = nullptr;
        code = nullptr;
    }

    // 输出哈夫曼树的参数
    void printTree() {
        cout << "Node-ID "
             << "Character "
             << "Weight "
             << "Parent-ID "
             << "lChild-ID "
             << "rChild-ID"
             << endl;
        for (size_t i = 1; i <= size * 2 - 1; i++) {
            auto _parent = tree[i].parent ? std::to_string(tree[i].parent) : "(null)";
            auto _lchild = tree[i].lchild ? std::to_string(tree[i].lchild) : "(null)";
            auto _rchild = tree[i].lchild ? std::to_string(tree[i].rchild) : "(null)";
            cout << std::left;
            cout << std::setw(8) << i
                 << std::setw(10) << tree[i].ch
                 << std::setw(7) << tree[i].weight
                 << std::setw(10) << _parent
                 << std::setw(10) << _lchild
                 << std::setw(9) << _rchild << endl;
        }
    }

    // 从输入流中编码字符
    string enCode(std::istream &is) {
        string str;
        std::getline(is, str);
        return enCode(str);
    }

    // 对一串字符编码
    string enCode(const string &str) {
        string ans;
        for (auto i : str) {
            bool isFound{false};
            for (size_t j = 1; j <= size; j++) {
                if ((i == ' ' && tree[j].ch == "(space)") || i == tree[j].ch[0]) {
                    ans += code[j];
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                throw std::invalid_argument("Can not encode this string!");
        }
        return ans;
    }

    // 输出编码表
    void printCode() {
        cout << "Node-ID "
             << "Character "
             << "Weight "
             << "Code"
             << endl;
        for (size_t i = 1; i <= size; i++) {
            cout << std::left;
            cout << std::setw(8) << i
                 << std::setw(10) << tree[i].ch
                 << std::setw(7) << tree[i].weight
                 << code[i] << endl;
        }
    }

    // 对一串二进制字符进行译码
    string deCode(const string &str) {
        size_t q = totalSize();
        string ans;
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] == '0')
                q = tree[q].lchild;
            else if (str[i] == '1')
                q = tree[q].rchild;
            else {
                throw std::invalid_argument("Can not decode this string!");
            }

            if (tree[q].lchild == 0 && tree[q].rchild == 0) {
                ans += (tree[q].ch == "(space)" ? " " : tree[q].ch);
                q = totalSize();
            } else if (i == str.size() - 1) {
                throw std::invalid_argument("Can not decode this string!");
            }
        }

        return ans;
    }

    // 从输入流中译码
    string deCode(std::istream &is) {
        string str;
        std::getline(is, str);
        return deCode(str);
    }

    // 内部函数
private:
    // 结点总数
    inline size_t totalSize() {
        return 2 * size - 1;
    }

    // 将两个双亲域为0且权值最小的结点的下标赋给参数 s1, s2
    void select(size_t n, size_t &s1, size_t &s2) {
        /********** 前两个循环找s1 **********/
        // 找出一个双亲为0的结点
        for (size_t i = 1; i <= n; i++) {
            if (tree[i].parent == 0) {
                s1 = i; // s1 初始化为i
                break;
            }
        }
        // 找到权值最小的结点，且双亲为0
        for (size_t i = 1; i <= n; i++) {
            if (tree[i].weight < tree[s1].weight && tree[i].parent == 0)
                s1 = i;
        }

        /********** 后两个循环找s2 **********/
        // 找出一个双亲为0的结点，并且不是s1
        for (size_t i = 1; i <= n; i++) {
            if (tree[i].parent == 0 && i != s1) {
                s2 = i; // s2 初始化为i
                break;
            }
        }
        // 找到权值第二小的结点，且双亲为0
        for (size_t i = 1; i <= n; i++) {
            if (tree[i].weight < tree[s2].weight && tree[i].parent == 0 && i != s1)
                s2 = i;
        }
    }

    // 初始化
    void init(size_t n, string *_ch, size_t *_weight) {
        if (n <= 1) {
            size = 0;
            return;
        } else {
            size = n;
        }
        tree = new HTNode[totalSize() + 1]; // 0 号单元未使用
        // 初始化树
        for (size_t i = 1; i <= totalSize(); i++) {
            if (i <= size) {
                tree[i].ch = _ch[i - 1];
                tree[i].weight = _weight[i - 1];
            }
            tree[i].lchild = 0;
            tree[i].rchild = 0;
            tree[i].parent = 0;
        }
        // 建成哈夫曼树
        for (size_t i = size + 1; i <= totalSize(); i++) {
            // 在tree[1~i-1]中选择parent为0，且weight最小的两个结点
            size_t s1, s2;
            select(i - 1, s1, s2);
            // 将s1,s2的双亲改为i
            tree[s1].parent = tree[s2].parent = i;
            // 将i的左孩子改为s1
            tree[i].lchild = s1;
            // 将i的右孩子改为s2
            tree[i].rchild = s2;
            // i的权值为左右孩子权值之和
            tree[i].weight = tree[s1].weight + tree[s2].weight;
        }
    }

    // 对所有字符进行编码
    void enCode() {
        code = new string[size + 1];
        for (size_t i = 1; i <= size; i++) {
            auto c = i;              // 当前结点
            auto f = tree[c].parent; // 指向当前的父结点
            while (f != 0) {         // 从叶子结点开始回溯，直到根结点
                if (tree[f].lchild == c)
                    code[i].insert(code[i].begin(), '0');
                else
                    code[i].insert(code[i].begin(), '1');
                c = f;
                f = tree[f].parent; // 向上回溯
            }
        }
    }
};