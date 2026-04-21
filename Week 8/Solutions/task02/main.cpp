#include <iostream>
#include "Computer.h"

int main() {
    try {
        Computer c1("Dell", "Intel i7", 8, 512, 2000, 8, 1499.99, 10);
        Computer c2("HP", "Ryzen 5", 6, 256, 1800, 6, 999.99, 5);

        {
            std::ofstream ofs("computers.txt");
            Computer::saveSerialCounter(ofs);
            c1.writeText(ofs);
            c2.writeText(ofs);
        }

        {
            std::ifstream ifs("computers.txt");
            Computer::loadSerialCounter(ifs);

            Computer t1;
            Computer t2;

            t1.readText(ifs);
            t2.readText(ifs);

            std::cout << t1.getSerialNumber() << " " << t1.getBrand() << "\n";
            std::cout << t2.getSerialNumber() << " " << t2.getBrand() << "\n";
        }

        {
            std::ofstream ofs("computers.bin", std::ios::binary);
            Computer::saveSerialCounter(ofs);
            c1.writeBinary(ofs);
            c2.writeBinary(ofs);
        }

        {
            std::ifstream ifs("computers.bin", std::ios::binary);
            Computer::loadSerialCounter(ifs);

            Computer b1;
            Computer b2;

            b1.readBinary(ifs);
            b2.readBinary(ifs);

            std::cout << b1.getSerialNumber() << " " << b1.getBrand() << "\n";
            std::cout << b2.getSerialNumber() << " " << b2.getBrand() << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
