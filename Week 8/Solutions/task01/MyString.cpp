#include "MyString.h"

void MyString::freeDynamic() {
    delete[] data;
    data = nullptr;
}

char* MyString::copyDynamic(const char* source, size_t capacity) {
    if (!source)
        throw std::invalid_argument("Null pointer");

    char* newData = new char[capacity];
    std::strcpy(newData, source);
    return newData;
}

void MyString::resize(size_t newCapacity) {
    if (newCapacity <= capacity)
        return;

    char* newData = new char[newCapacity];

    if (data)
        std::strcpy(newData, data);
    else
        newData[0] = '\0';

    delete[] data;
    data = newData;
    capacity = newCapacity;
}


MyString::MyString() : data(new char[1]), size(0), capacity(1) {
    data[0] = '\0';
}

MyString::MyString(const char* str) {
    if (!str)
        throw std::invalid_argument("Null pointer");

    size = std::strlen(str);
    capacity = size + 1;

    data = copyDynamic(str, capacity);
}

MyString::MyString(const MyString& other) {
    size = other.size;
    capacity = other.capacity;

    data = copyDynamic(other.data, capacity);
}

MyString::~MyString() {
    freeDynamic();
}



MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        char* newData = copyDynamic(other.data, other.capacity);

        delete[] data;   // commit
        data = newData;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

char MyString::at(size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

char MyString::front() const {
    if (empty())
        throw std::out_of_range("Empty string");
    return data[0];
}

char MyString::back() const {
    if (empty())
        throw std::out_of_range("Empty string");
    return data[size - 1];
}

const char* MyString::str() const {
    return data;
}

size_t MyString::length() const {
    return size;
}

size_t MyString::getCapacity() const {
    return capacity;
}

bool MyString::empty() const {
    return size == 0;
}



void MyString::append(char c) {
    if (size + 1 >= capacity)
        resize(capacity * 2);

    data[size++] = c;
    data[size] = '\0';
}

void MyString::append(const char* str) {
    if (!str)
        throw std::invalid_argument("Null pointer");

    size_t len = std::strlen(str);

    if (size + len + 1 > capacity)
        resize((size + len + 1) * 2);

    std::strcpy(data + size, str);
    size += len;
}

void MyString::append(const MyString& other) {
    append(other.data);
}


void MyString::clear() {
    size = 0;
    data[0] = '\0';
}

bool MyString::equals(const MyString& other) const {
    return std::strcmp(data, other.data) == 0;
}

int MyString::find(char c) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == c)
            return (int)i;
    }
    return -1;
}
