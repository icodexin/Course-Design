#include "ParkLot.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int menu();

int main() {
    cout << "Welcome to use Parking Management System!" << endl;
    cout << "Please input the capacity of the Parking Lot: ";
    Stack<Car>::size_type size{0};
    cin >> size;
    ParkLot p{size};
    while (true) {
        switch (menu()) {
            case 1: {
                cout << "Please input the License Number of the car, arrive time" << endl
                     << "(the format is \"number hour minute\", like: A-00001 12 59):" << endl;
                std::string number;
                int hour{0}, minute{0};
                cin >> number >> hour >> minute;
                p.add(number, Time{hour, minute});
            } break;
            case 2: {
                cout << "Please input the License Number of the car, leave time" << endl
                     << "(the format is \"number hour minute\", like: A-00001 12 59):" << endl;
                std::string number;
                int hour{0}, minute{0};
                cin >> number >> hour >> minute;
                p.reduce(number, Time{hour, minute});
            } break;
            case 3:
                p.print();
                break;
            case 0:
                cout << "Thanks for using!" << endl;
                exit(0);
        }
    }
}

int menu() {
    auto sn{0};
    cout << endl
         << "<--------------- Menu ---------------" << endl
         << "1. Add Car" << endl
         << "2. Reduce Car" << endl
         << "3. Show Parking Situation" << endl
         << "0. Exit System" << endl
         << "--------------- Menu --------------->" << endl
         << "Pleas input 0-3: ";
    while (true) {
        cin >> sn;
        if (sn < 0 || sn > 3) {
            cout << "Error Number! Please Input 0-3: ";
        } else
            break;
    }
    return sn;
}