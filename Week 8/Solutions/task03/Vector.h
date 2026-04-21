#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;

    void freeDynamic();
    int* copyDynamic(const int* source, size_t count, size_t capacity);
    void resize(size_t newCapacity);

public:
    Vector();
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    void pushBack(int value);
    void pushFront(int value);

    int getBack() const;
    int getFront() const;

    size_t getSize() const;
    bool isEmpty() const;

    int at(size_t index) const;

    void popBack();
    void clear();
};

#endif
