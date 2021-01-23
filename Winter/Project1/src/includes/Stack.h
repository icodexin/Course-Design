#pragma once

#include <string>

// 栈节点类
template<typename T>
class Node {
private:
    T data;        // 数据域
    Node<T> *next; // 指向下一节点

public:
    // 构造函数，初始化栈节点
    Node();

    // 有参构造函数，初始化栈节点
    Node(T data, Node<T> *next = nullptr);

    // 获取数据域
    T getData();

    // 设置下一节点
    void setNext(Node<T> *next);

    // 获取下一节点
    Node<T> *getNext();
};

// 栈类
template<typename T>
class Stack {
private:
    Node<T> *top; // 栈顶，链栈头指针
    int size;     // 栈大小(节点个数)
public:
    // 构造函数，初始化栈
    Stack();

    // 析构函数，释放栈
    ~Stack();

    // 获取栈长
    int getSize();

    // 判断栈是否为空
    bool isEmpty();

    // 入栈
    void push(T data);

    // 出栈
    void pop();

    // 出栈并将栈顶节点的data值赋给参数e
    void pop(T &e);

    // 获取栈顶的引用
    Node<T> &getTop();

    // 打印栈
    void print();
};


// 构造函数
template<typename T>
Node<T>::Node() = default;

// 有参构造函数
template<typename T>
Node<T>::Node(T data, Node<T> *next) {
    this->data = data;
    this->next = next;
}

// 获取数据域
template<typename T>
T Node<T>::getData() {
    return data;
}

// 设置下一节点
template<typename T>
void Node<T>::setNext(Node<T> *next) {
    this->next = next;
}

// 获取下一节点
template<typename T>
Node<T> *Node<T>::getNext() {
    return next;
}

// 构造函数
template<typename T>
Stack<T>::Stack() {
    top = nullptr;
    // 初始时，没有节点
    size = 0;
}

// 析构函数
template<typename T>
Stack<T>::~Stack() {
    while (top) { // 如果栈顶存在
        Node<T> *p = top;
        top = top->getNext();
        // 释放栈顶
        delete p;
    }
}

// 获取栈长
template<typename T>
int Stack<T>::getSize() {
    return size;
}

// 判断栈是否为空
template<typename T>
bool Stack<T>::isEmpty() {
    return top == nullptr;
}

// 入栈
template<typename T>
void Stack<T>::push(T data) {
    // 生成新栈顶，并指向当前栈顶
    auto newTop = new Node<T>{data, top};
    // top指向新栈顶
    top = newTop;
    // 更新size
    size++;
}

// 出栈
template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        std::cerr << "栈空! 无法出栈." << std::endl;
        exit(1);
    }
    Node<T> *p = top;
    // top变为原栈顶的下一节点
    top = top->getNext();
    // 删除原栈顶
    delete p;
    // 更新size
    size--;
}

// 出栈并将栈顶节点的data值赋给参数e
template<typename T>
void Stack<T>::pop(T &e) {
    if (isEmpty()) {
        std::cerr << "栈空! 无法出栈." << std::endl;
        exit(1);
    }
    // 将栈顶赋值给e
    e = (*top).getData();
    Node<T> *p = top;
    // top变为原栈顶的下一节点
    top = top->getNext();
    // 删除原栈顶
    delete p;
    // 更新size
    size--;
}

// 获取栈顶的引用
template<typename T>
Node<T> &Stack<T>::getTop() {
    if (isEmpty()) {
        std::cerr << "栈空! 没有栈顶." << std::endl;
        exit(1);
    }
    return *top;
}

// 打印栈
template<typename T>
void Stack<T>::print() {
    if (isEmpty()) {
        std::cout << "null";
    }
    Node<T> *p = top;
    auto cnt{1};
    while (p) {
        std::string ch = (cnt % 5 ? " " : "\n"); // 一行五个
        if (cnt == size)                         // 如果是最后一个
            ch = "\n";
        cnt++;
        std::cout << p->getData() << ch;
        p = p->getNext();
    }
}