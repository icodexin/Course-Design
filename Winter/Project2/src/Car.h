/**
 * @file Car.h
 * @author https://github.com/DianDengJun
 * @brief 汽车类头文件
 * @version 1
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <iostream>

// 时间类
struct Time {
    /************** 公有数据成员 **************/
    int hour;   // 时
    int minute; // 分

    // 构造函数
    Time() : Time(0, 0) {}

    Time(int hour, int minute) {
        this->hour = hour;
        this->minute = minute;
    }

    friend Time operator+(const Time &left, const Time &right);

    friend Time operator-(const Time &left, const Time &right);

    friend bool operator==(const Time &left, const Time &right);

    friend bool operator<(const Time &left, const Time &right);

    friend bool operator<=(const Time &left, const Time &right);

    friend bool operator>(const Time &left, const Time &right);

    friend bool operator>=(const Time &left, const Time &right);

    friend std::ostream &operator<<(std::ostream &os, const Time &t);

    Time operator+=(const Time &right) {
        *this = *this + right;
        return *this;
    }

    Time operator-=(const Time &right) {
        *this = *this - right;
        return *this;
    }
};

Time operator+(const Time &left, const Time &right) {
    int m = (left.minute + right.minute) % 60;
    int h = left.hour + right.hour + (left.minute + right.minute) / 60;
    return Time{h, m};
}

Time operator-(const Time &left, const Time &right) {
    if (left.hour < right.hour ||
        left.hour == right.hour && left.minute < right.minute)
        return Time{0, 0};

    int h = left.hour - right.hour;
    int m = left.minute - right.minute;
    if (m < 0) {
        m += 60;
        h--;
    }
    return Time(h, m);
}

bool operator==(const Time &left, const Time &right) {
    return left.hour == right.hour && left.minute == right.minute;
}

bool operator<(const Time &left, const Time &right) {
    if (left.hour < right.hour)
        return true;
    else if (left.hour == right.hour) {
        return left.minute < right.minute;
    } else
        return false;
}

bool operator<=(const Time &left, const Time &right) {
    return left == right || left < right;
}

bool operator>(const Time &left, const Time &right) {
    return !(left <= right);
}

bool operator>=(const Time &left, const Time &right) {
    return !(left < right);
}

// 将时间输出到流中
std::ostream &operator<<(std::ostream &os, const Time &t) {
    os << t.hour << "h " << t.minute << "m";
    return os;
}

// 汽车类
class Car {
private:
    /************** 私有数据成员 **************/
    std::string number; // 牌照号码
    Time lastTime;      // 最后一次在栈内的时刻
    Time parking;       // 停车时间

public:
    // 构造函数
    Car() = default;

    explicit Car(std::string number) {
        this->number = number;
        this->parking = {0, 0};
    }

    // 判断是否为同一辆车
    bool operator==(const Car &car) {
        return this->number == car.number;
    }

    // 设置最后一次在栈内的时刻,并增加停车时间
    void updateLastTime(const Time &time) {
        addParkingTime(time - lastTime);
        this->lastTime = time;
    }

    // 设置最后一次在栈内的时刻
    void setLastTime(const Time &time) {
        this->lastTime = time;
    }

    // 获取最后一次在栈内的时刻
    Time getLastTime() {
        return lastTime;
    }

    // 增加停车时间
    void addParkingTime(const Time &time) {
        this->parking += time;
    }

    // 获取停车时间
    Time getParingTime() {
        return parking;
    }

    friend std::ostream &operator<<(std::ostream &os, const Car &c);
};

// 将汽车输出到流中
std::ostream &operator<<(std::ostream &os, const Car &c) {
    os << c.number;
    return os;
}