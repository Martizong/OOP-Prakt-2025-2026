#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <stdexcept>
#include <iostream>

class MyString {
private:
    char* data;
    size_t size;
    size_t capacity;

    void freeDynamic();
    char* copyDynamic(const char* source, size_t capacity);
    void resize(size_t newCapacity);

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);

    char at(size_t index) const;
    char front() const;
    char back() const;
    const char* str() const;

    size_t length() const;
    size_t getCapacity() const;
    bool empty() const;

    void append(char c);
    void append(const char* str);
    void append(const MyString& other);

    void clear();
    bool equals(const MyString& other) const;
    int find(char c) const;

    
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    MyString& operator+=(const MyString& other);

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& ref);

    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    friend bool operator==(const MyString& lhs, const MyString& rhs);
    friend bool operator!=(const MyString& lhs, const MyString& rhs);
    friend bool operator<(const MyString& lhs, const MyString& rhs);
    friend bool operator<=(const MyString& lhs, const MyString& rhs);
    friend bool operator>(const MyString& lhs, const MyString& rhs);
    friend bool operator>=(const MyString& lhs, const MyString& rhs);
};

#endif
