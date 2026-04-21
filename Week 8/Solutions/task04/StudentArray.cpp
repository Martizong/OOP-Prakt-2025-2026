#include "StudentArray.h"

void StudentArray::freeDynamic() {
    delete[] data;
    data = nullptr;
}

Student* StudentArray::copyDynamic(const StudentArray& other) {
    if (!other.data && other.size > 0)
        throw std::invalid_argument("Null source array");

    Student* newData = nullptr;

    try {
        newData = new Student[other.capacity];

        for (size_t i = 0; i < other.size; i++)
            newData[i] = other.data[i];
    }
    catch (...) {
        delete[] newData;
        throw;
    }

    return newData;
}

void StudentArray::resize(size_t newCap) {
    if (newCap <= capacity)
        return;

    Student* newData = nullptr;

    try {
        newData = new Student[newCap];

        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
    }
    catch (...) {
        delete[] newData;
        throw;
    }

    delete[] data;
    data = newData;
    capacity = newCap;
}

StudentArray::StudentArray() {
    data = new Student[1];
    size = 0;
    capacity = 1;
}

StudentArray::StudentArray(const StudentArray& other) {
    data = copyDynamic(other);
    size = other.size;
    capacity = other.capacity;
}

StudentArray::~StudentArray() {
    freeDynamic();
}

StudentArray& StudentArray::operator=(const StudentArray& other) {
    if (this != &other) {
        Student* newData = copyDynamic(other);

        freeDynamic();
        data = newData;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

void StudentArray::pushBack(const Student& s) {
    if (size >= capacity)
        resize(capacity * 2);

    data[size++] = s;
}

void StudentArray::pushFront(const Student& s) {
    if (size >= capacity)
        resize(capacity * 2);

    for (size_t i = size; i > 0; i--)
        data[i] = data[i - 1];

    data[0] = s;
    size++;
}

Student& StudentArray::getBack() {
    if (isEmpty())
        throw std::out_of_range("Empty array");
    return data[size - 1];
}

Student& StudentArray::getFront() {
    if (isEmpty())
        throw std::out_of_range("Empty array");
    return data[0];
}

size_t StudentArray::getSize() const {
    return size;
}

bool StudentArray::isEmpty() const {
    return size == 0;
}

Student& StudentArray::at(size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}
