#include "Person.h"
#include <cstring>

#pragma warning(disable:4996)

void Person::freeDynamic() {
    delete[] name;
    name = nullptr;
}

void Person::copyDynamic(const Person& other) {
    if (!other.name) {
        name = new char[1];
        name[0] = '\0';
        return;
    }

    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);
}

Person::Person() {
    name = new char[1];
    name[0] = '\0';
    age = 0;
}

Person::Person(const char* n, int a) {
    if (!n || std::strlen(n) == 0) {
        name = new char[1];
        name[0] = '\0';
    } else {
        name = new char[std::strlen(n) + 1];
        std::strcpy(name, n);
    }

    age = (a >= 0 ? a : 0);
}

Person::Person(const Person& other) {
    copyDynamic(other);
    age = other.age;
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        freeDynamic();
        copyDynamic(other);
        age = other.age;
    }
    return *this;
}

Person::~Person() {
    freeDynamic();
}

void Person::setName(const char* n) {
    if (!n || std::strlen(n) == 0) {
        return;
    }

    freeDynamic();

    name = new char[std::strlen(n) + 1];
    std::strcpy(name, n);
}

void Person::setAge(int a) {
    if (a >= 0) {
        age = a;
    }
}

const char* Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}
