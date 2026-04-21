#include <iostream>
#include "Vector.h"

int main() {
    try {
        Vector v;

        v.pushBack(10);
        v.pushBack(20);
        v.pushFront(5);

        std::cout << "Front: " << v.getFront() << std::endl;
        std::cout << "Back: " << v.getBack() << std::endl;

        std::cout << "Size: " << v.getSize() << std::endl;

        for (size_t i = 0; i < v.getSize(); i++) {
            std::cout << v.at(i) << " ";
        }
        std::cout << std::endl;

        v.popBack();
        std::cout << "After popBack, size: " << v.getSize() << std::endl;
        std::cout << v.at(100) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Memory error: " << e.what() << std::endl;
    }

    try {
        Vector v2;
        v2.popBack(); 
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
