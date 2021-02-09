/**
 * @file Queue.h
 * @author https://github.com/DianDengJun
 * @brief 队列(模板)类头文件
 * @version 1
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <cassert>
#include <iostream>

/**
 * @brief 队列节点(模板)类
 *
 * @tparam T 基础元素类型
 */
template<typename T>
class QNode {
public:
    /************** 嵌套类型 **************/
    typedef T                   value_type;         // 基础元素类型
    typedef T*                  pointer;            // 指针
    typedef const T*            const_pointer;      // 常指针
    typedef T&                  reference;          // 引用
    typedef const T&            const_reference;    // 常引用
    typedef QNode<T>*           node_ptr;           // 节点指针
    typedef const QNode<T>*     const_node_ptr;     // 节点常指针
    typedef QNode<T>&           node_ref;           // 节点引用
    typedef const QNode<T>&     const_node_ref;     // 节点常引用
    typedef std::size_t         size_type;          // 无符号超长整型

private:
    /************** 私有数据成员 **************/
    value_type _data; // 数据域
    node_ptr _next;   // 指针域，指向下一节点

public:
    // 默认构造函数
    QNode() : QNode{value_type()} {}

    // 有参构造函数
    explicit QNode(const_reference data, const_node_ptr next = nullptr) {
        this->_data = data;
        this->_next = const_cast<node_ptr>(next);
    }

    // 返回数据域的引用
    reference data() {
        return _data;
    }

    // 返回数据域的常引用
    const_reference data() const {
        return _data;
    }

    // 修改数据域
    void setData(const_reference data) {
        this->_data = data;
    }

    // 返回指针域
    node_ptr next() {
        return this->_next;
    }

    // 返回指针域
    const_node_ptr next() const {
        return this->_next;
    }

    // 修改指针域
    void setNext(const_node_ptr next) {
        this->_next = const_cast<node_ptr>(next);
    }
};

template<typename T>
class Queue {
public:
    /************** 嵌套类型 **************/
    typedef typename QNode<T>::value_type           value_type;         // 基础元素类型
    typedef typename QNode<T>::reference            reference;          // 节点引用
    typedef typename QNode<T>::const_reference      const_reference;    // 节点常引用
    typedef typename QNode<T>::node_ptr             node_ptr;           // 节点指针
    typedef typename QNode<T>::const_node_ptr       const_node_ptr;     // 节点常指针
    typedef typename QNode<T>::node_ref             node_ref;           // 节点引用
    typedef typename QNode<T>::const_node_ref       const_node_ref;     // 节点引用
    typedef std::size_t                             size_type;          // 无符号超长整型


private:
    /************** 私有数据成员 **************/
    node_ptr _front; // 队头指针
    node_ptr _back;  // 队尾指针

public:
    // 构造一个空队列
    Queue() {
        try {
            _front = _back = new QNode<value_type>;
        } catch (std::bad_alloc &) {
            std::cerr << "Exception: Can not construct a new Stack object,"
                      << "because there is no available memory."
                      << std::endl;
        }
        _front->setNext(nullptr);
    }

    // 销毁队列
    ~Queue() {
        while (_front) {
            _back = _front->next();
            delete _front;
            _front = _back;
        }
    }

    // 返回队头的引用
    reference front() {
        return _front->next()->data();
    }

    // 返回队头的常引用
    const_reference front() const {
        return _front->next()->data();
    }

    // 返回队尾的引用
    reference back() {
        return _back->data();
    }

    // 返回队尾的常引用
    const_reference back() const {
        return _back->data();
    }

    // 返回队列是否为空
    bool empty() const noexcept {
        return _front == _back;
    }

    // 返回队列的大小
    size_type size() {
        node_ptr temp = _front->next();
        size_type size{0};
        while (temp) {
            size++;
            temp = temp->next();
        }
        return size;
    }

    // 入队列
    void push(const_reference data) {
        node_ptr p;
        try {
            p = new QNode<value_type>;
        } catch (std::bad_alloc &) {
            std::cerr << "Exception: Can not push new data,"
                      << "because there is no available memory."
                      << std::endl;
        }
        p->setData(data);
        p->setNext(nullptr);
        _back->setNext(p);
        _back = p;
    }

    // 出队列
    void pop() {
        assert(!empty());
        node_ptr p = _front->next();
        _front->setNext(p->next());
        if (_back == p)
            _back = _front;
        delete p;
    }

    // 直接擦除第一个值为data的节点
    void erase(const_reference data) {
        assert(!empty());
        node_ptr before = _front;
        node_ptr current = _front->next();
        while (current) {
            auto next = current->next();
            if (current->data() == data) {
                auto toDelete = current;
                if (_back == current)
                    _back = before;
                current = next;
                before->setNext(next);
                delete toDelete;
                return;
            } else {
                before = current;
                current = next;
            }
        }
        throw std::out_of_range("not found");
    }

    // 打印队列
    void print() {
        if (empty()) {
            std::cout << "null" << std::endl;
        } else {
            node_ptr p = _front->next();
            auto cnt{1};
            while (p) {
                std::string ch = (cnt % 5 ? " " : "\n");
                if (cnt == size())
                    ch = "\n";
                std::cout << "(" << cnt++ << ", " << p->data() << ")" << ch;
                p = p->next();
            }
        }
    }
};