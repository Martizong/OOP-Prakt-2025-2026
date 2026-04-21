#include <iostream>
#include "StudentArray.h"

const char* specialtyToString(Specialty s) {
    switch (s) {
        case Specialty::Informatics: return "Informatics";
        case Specialty::InformationSystems: return "Information Systems";
        case Specialty::SoftwareEngineering: return "Software Engineering";
        case Specialty::ComputerScience: return "Computer Science";
    }
    return "Unknown";
}

void printStudent(const Student& s) {
    std::cout << "Name: " << s.getName()
              << ", FN: " << s.getFacultyNumber()
              << ", Specialty: " << specialtyToString(s.getSpecialty())
              << std::endl;
}

int main() {
    try {
        StudentArray arr;

        Student s1("Ivan Petrov", "12345", Specialty::SoftwareEngineering);
        Student s2("Maria Georgieva", "67890", Specialty::Informatics);
        Student s3("Georgi Ivanov", "11223", Specialty::ComputerScience);

        arr.pushBack(s1);
        arr.pushBack(s2);
        arr.pushFront(s3);

        std::cout << "Array size: " << arr.getSize() << std::endl;

        std::cout << "\nFront student:\n";
        printStudent(arr.getFront());

        std::cout << "\nBack student:\n";
        printStudent(arr.getBack());

        std::cout << "\nAll students:\n";
        for (size_t i = 0; i < arr.getSize(); i++)
            printStudent(arr.at(i));

        std::cout << "\nTesting out_of_range:\n";
        try {
            arr.at(100); 
        }
        catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

    }
    catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
