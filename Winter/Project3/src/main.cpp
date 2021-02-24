#include "Huffman.h"
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using Hf = Huffman;

int menu();

// 显示文件内容
void showFile(const string &filename);

// 导入文件到文件流
ifstream &importFile(ifstream &is);

// 将字符串写入文件
void writeToFile(const string &filename, const string &str);


int main() {
    cout << "Welcome to Huffman Encoding and Decoding System!" << endl;
    Hf h;        // 实例化一个哈夫曼编码树对象
    ifstream is; // 实例化一个输入文件流对象
    while (true) {
        switch (menu()) {
            case 1: {
                // 尝试导入文件
                try {
                    importFile(is);
                    h = Hf(is); // 匿名构造，然后复制之
                    is.close();
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << endl;
                    break;
                }
                cout << "\nInit succeeded!\n\n"
                     << "Here are the Overview of the Huffman Tree:\n\n";
                // 打印哈夫曼树关键信息
                h.printTree();
            } break;
            case 2: {
                // 尝试导入文件
                try {
                    importFile(is);
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << endl;
                    break;
                }
                string code; // 用以存储二进制哈夫曼编码
                // 尝试编码
                try {
                    code = h.enCode(is);
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << endl;
                    is.close();
                    break;
                }
                is.close();
                cout << "\nEnCode succeeded!\n\n"
                     << "The string has been transformed to:\n"
                     << code << endl
                     << endl;
                // 将编码写入Code.txt
                writeToFile("Code.txt", code);
            } break;
            case 3: {
                // 尝试导入文件
                try {
                    importFile(is);
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << endl;
                    break;
                }
                string str; // 用以存储译码后的字符串
                try {
                    str = h.deCode(is);
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << endl;
                    is.close();
                }
                is.close();
                cout << "\nDeCode succeeded!\n\n"
                     << "The string has been translated to:\n"
                     << str << endl
                     << endl;
                // 将译码后的字符串写入TextFile.txt
                writeToFile("TextFile.txt", str);
            } break;
            case 4: {
                cout << "\nCharacter Table:" << endl;
                h.printCode();             // 显示DataFile.data中的字符频率
                showFile("ToBeTran.data"); // 显示ToBeTran.data
                showFile("Code.txt");      // 显示Code.txt
                showFile("CodeFile.data"); // 显示CodeFile.data
                showFile("TextFile.txt");  // 显示TextFile.txt
            } break;
            case 0:
                cout << "Thanks for using!" << endl;
                exit(0);
        }
    }
    return 0;
}

int menu() {
    auto sn{0};
    cout << endl
         << "<--------------- Menu ---------------" << endl
         << "1. Init system" << endl
         << "2. Encoding" << endl
         << "3. Decoding" << endl
         << "4. Output" << endl
         << "0. Exit" << endl
         << "--------------- Menu --------------->" << endl
         << "Pleas input 0-4: ";
    while (true) {
        cin >> sn;
        if (sn < 0 || sn > 4) {
            cout << "Error Number! Please Input 0-4: ";
        } else
            break;
    }
    return sn;
}

void showFile(const string &filename) {
    cout << endl;
    cout << filename << ":" << endl;
    ifstream is;
    is.open(filename);
    if (!is.is_open()) {
        cout << "Fail to open file " << filename << "!" << endl;
        return;
    }
    string str;
    getline(is, str);
    cout << str << endl;
}

ifstream &importFile(ifstream &is) {
    string filename;
    cout << "Input filename (with '.data'): ";
    cin >> filename;
    is.open(filename);
    if (!is.is_open()) {
        is.close();
        throw std::invalid_argument("Fail to open file " + filename + "!");
    }
    return is;
}

void writeToFile(const string &filename, const string &str) {
    ofstream os;
    os.open(filename);
    if (!os.is_open()) {
        cout << "Fail to write the result to file " << filename
             << "!" << endl;
        return;
    }
    os << str << endl;
    os.close();
    cout << "The result has been written to " << filename << endl;
}