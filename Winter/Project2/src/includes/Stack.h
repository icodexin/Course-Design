/**
 * @file Stack.h
 * @author https://github.com/DianDengJun
 * @brief 栈(模板)类头文件
 * @version 1
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <cassert>
#include <iostream>
#include <stdexcept>

#define Stack_Init_Size 10 // 栈存储空间初始容量

/**
 * @brief 栈(模板)类
 *
 * @tparam T 基础元素类型
 */
template<typename T>
class Stack {
public:
    /************** 嵌套类型 **************/
    typedef T           value_type;         // 基础元素类型
    typedef T*          pointer;            // 指针
    typedef const T*    const_pointer;      // 常指针
    typedef T&          reference;          // 引用
    typedef const T&    const_reference;    // 常引用
    typedef std::size_t size_type;          // 无符号长整型

private:
    /************** 私有数据成员 **************/
    pointer _top;  // 栈顶(后一位)
    pointer _base; // 栈底
    pointer _cap;  // 当前栈存储空间的尾部(后一位)

public:
    // 构造一个空栈
    Stack() {
        try {
            _base = new value_type[Stack_Init_Size];
            _top = _base;
            _cap = _base + Stack_Init_Size;
        } catch (std::bad_alloc &) { // 分配内存异常
            std::cerr << "Exception: Can not construct a new Stack object,"
                      << "because there is no available memory."
                      << std::endl;
        }
    }

    // 销毁栈
    ~Stack() {
        delete[] _base;
        _base = _top = _cap = nullptr;
    }

    // 返回pos位置的引用
    reference operator[](size_type pos) {
        assert(!empty());
        return *(_base + pos);
    }

    // 返回pos位置的常引用
    const_reference operator[](size_type pos) const {
        assert(!empty());
        return *(_base + pos);
    }

    // 返回栈顶的引用
    reference top() {
        assert(!empty());
        return *(_top - 1);
    }

    // 返回栈顶的常引用
    const_reference top() const {
        assert(!empty());
        return *(_top - 1);
    }

    // 返回栈是否为空
    bool empty() const noexcept {
        return _top == _base;
    }

    // 获取栈长
    size_type size() const noexcept {
        return (_top - _base);
    }

    // 获取栈的存储容量
    size_type capacity() const noexcept {
        return _cap - _base;
    }

    // 入栈
    void push(const_reference data) {
        if (size() >= capacity())
            try {
                reserve(capacity() * 3 / 2);
            } catch (std::bad_alloc &) {
                std::cerr << "Exception: Can not push new data,"
                          << "because there is no available memory."
                          << std::endl;
            }
        *(_top++) = data;
    }

    // 出栈
    void pop() {
        assert(!empty());
        _top--;
    }

    // 寻找元素的第一个位置
    size_type index(const_reference data) {
        for (size_type i = 0; i < size(); i++) {
            if (*(_base + i) == data)
                return i;
        }
        throw std::out_of_range{"not found"};
    }

    // 打印栈
    void print() {
        if (empty())
            std::cout << "null" << std::endl;
        else {
            for (size_type i = 0; i < size(); i++) {
                std::string ch = ((i + 1) % 5 ? " " : "\n");
                if (i + 1 == size())
                    ch = "\n";
                std::cout << "(" << i + 1 << ", " << *(_base + i) << ")" << ch;
            }
            std::cout << std::endl;
        }
    }

    // 重新分配存储空间容量
    void reserve(size_type newCapacity) {
        size_type _size = size();

        if (newCapacity <= capacity())
            return;

        pointer temp = _base;
        _base = new value_type[newCapacity];
        for (int i = 0; i < _size; i++)
            *(_base + i) = *(temp + i);
        delete[] temp;

        _top = _base + _size;
        _cap = _base + newCapacity;
    }
};