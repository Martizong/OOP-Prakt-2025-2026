#include "Vector.h"

void Vector::freeDynamic() {
    delete[] data;
    data = nullptr;
}

int* Vector::copyDynamic(const int* source, size_t count, size_t capacity) {
    if (!source && count > 0)
        throw std::invalid_argument("Null source");

    int* newData = new int[capacity];

    for (size_t i = 0; i < count; i++)
        newData[i] = source[i];

    return newData;
}

void Vector::resize(size_t newCapacity) {
    if (newCapacity <= capacity)
        return;

    int* newData = new int[newCapacity];

    for (size_t i = 0; i < size; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

Vector::Vector() : data(new int[1]), size(0), capacity(1) {}

Vector::Vector(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    data = copyDynamic(other.data, size, capacity);
}

Vector::~Vector() {
    freeDynamic();
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        int* newData = copyDynamic(other.data, other.size, other.capacity);

        delete[] data; 
        data = newData;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

void Vector::pushBack(int value) {
    if (size >= capacity)
        resize(capacity * 2);

    data[size++] = value;
}

void Vector::pushFront(int value) {
    if (size >= capacity)
        resize(capacity * 2);

    for (size_t i = size; i > 0; i--)
        data[i] = data[i - 1];

    data[0] = value;
    size++;
}

int Vector::getBack() const {
    if (isEmpty())
        throw std::out_of_range("Empty vector");
    return data[size - 1];
}

int Vector::getFront() const {
    if (isEmpty())
        throw std::out_of_range("Empty vector");
    return data[0];
}

size_t Vector::getSize() const {
    return size;
}

bool Vector::isEmpty() const {
    return size == 0;
}

int Vector::at(size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

void Vector::popBack() {
    if (isEmpty())
        throw std::out_of_range("Pop from empty vector");

    size--;
}

void Vector::clear() {
    size = 0;
}
