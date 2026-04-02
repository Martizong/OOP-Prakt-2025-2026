#pragma once
#include <iostream>

class Person {
private:
    char* name;
    int age;

    void freeDynamic();
    void copyDynamic(const Person& other);

public:
    Person();
    Person(const char* n, int a);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    void setName(const char* n);
    void setAge(int a);

    const char* getName() const;
    int getAge() const;
};
