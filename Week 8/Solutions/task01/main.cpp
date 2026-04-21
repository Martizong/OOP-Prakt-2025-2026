#include <iostream>
#include "MyString.h"

int main() {
    try {
        MyString s1("Hello");
        MyString s2("World");

        s1.append(' ');
        s1.append(s2);

        std::cout << "String: " << s1.str() << std::endl;

        std::cout << "Front: " << s1.front() << std::endl;
        std::cout << "Back: " << s1.back() << std::endl;

        std::cout << "At(1): " << s1.at(1) << std::endl;

        std::cout << "Find 'o': " << s1.find('o') << std::endl;

        std::cout << "Equals s2: " << s1.equals(s2) << std::endl;

        std::cout << s1.at(100) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
    }

    std::cout << "\n--- second test ---\n";

    try {
        
        MyString s3(nullptr);
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
