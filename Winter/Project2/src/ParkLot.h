/**
 * @file ParkLot.h
 * @author https://github.com/DianDengJun
 * @brief 停车场头文件
 * @version 1
 * @date 2021-02-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Car.h"
#include <Queue.h>
#include <Stack.h>
#include <iostream>

int fees(Car c);

// 停车场类
class ParkLot {
private:
    /************** 私有数据成员 **************/
    Stack<Car> s;       // 停车场(栈)
    Queue<Car> q;       // 便道(队列)
    std::size_t size{}; // 停车场容量(栈最大大小)

public:
    // 构造函数
    ParkLot() = default;

    explicit ParkLot(std::size_t size) {
        this->size = size;
    }

    // 到达汽车
    void add(const std::string &carNumber, const Time &arriveTime) {
        if (s.size() >= size) {
            Car c = Car{carNumber};
            q.push(c);
            std::cout << "The car arrive at No." << q.size() << " position in corridor." << std::endl;
        } else {
            Car c = Car{carNumber};
            c.setLastTime(arriveTime);
            s.push(c);
            std::cout << "The car arrive at No." << s.size() << " position in parking lot." << std::endl;
        }
    }

    // 离开汽车
    void reduce(const std::string &carNumber, const Time &leaveTime) {
        if (s.size() < size || (s.size() == size && q.empty())) {
            try {
                int pos = s.index(Car{carNumber});
                s[pos].updateLastTime(leaveTime);
                std::cout << "Parking time: " << s[pos].getParingTime() << std::endl;
                std::cout << "Fees to be paid: " << fees(s[pos]) << std::endl;
                for (std::size_t i = pos + 1; i < s.size(); i++) {
                    s[i - 1] = s[i];
                }
                s.pop();
            } catch (const std::out_of_range &e) {
                std::cerr << "No matching Car In Parking Lot." << '\n';
            }
        } else {
            try {
                int pos = s.index(Car{carNumber});
                s[pos].updateLastTime(leaveTime);
                std::cout << "Parking time: " << s[pos].getParingTime() << std::endl;
                std::cout << "Fees to be paid: " << fees(s[pos]) << std::endl;
                for (std::size_t i = pos + 1; i < s.size(); i++) {
                    s[i - 1] = s[i];
                }
                s.pop();
                Car c = q.front();
                c.setLastTime(leaveTime);
                q.pop();
                s.push(c);
            } catch (const std::out_of_range &) {
                try {
                    q.erase(Car{carNumber});
                    std::cout << "Parking time: " << Time{0, 0} << std::endl;
                    std::cout << "Fees to be paid: " << 0 << std::endl;
                    std::cout << "The car left from corridor directly." << std::endl;
                } catch (const std::out_of_range &) {
                    std::cerr << "No matching Car." << '\n';
                }
            }
        }
    }

    // 打印停车场
    void print() {
        std::cout << "In Parking Lot:" << std::endl;
        s.print();
        std::cout << "In Corridor:" << std::endl;
        q.print();
    }
};

int fees(Car c) {
    int fee;
    Time t = c.getParingTime();
    if (t <= Time{1, 0}) {
        fee = 0;
    } else if (t <= Time{2, 0}) {
        fee = 5;
    } else {
        t -= Time{2, 0};
        fee = 5 + (t.hour + (t.minute ? 1 : 0)) * 3;
    }
    return fee;
}