#pragma once
#include "Student.h"
#include <stdexcept>

class StudentArray {
private:
    Student* data;
    size_t size;
    size_t capacity;

    void freeDynamic();
    void copyDynamic(const StudentArray& other);
    void resize(size_t newCap);

public:
    StudentArray();
    StudentArray(const StudentArray& other);
    ~StudentArray();

    StudentArray& operator=(const StudentArray& other);

    void pushBack(const Student& s);
    void pushFront(const Student& s);

    Student& getBack();
    Student& getFront();

    size_t getSize() const;
    bool isEmpty() const;

    Student& at(size_t index);
};
