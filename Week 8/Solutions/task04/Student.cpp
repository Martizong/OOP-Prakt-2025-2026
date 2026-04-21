#include "Student.h"

void Student::freeDynamic() {
    delete[] name;
    delete[] facultyNumber;
    name = nullptr;
    facultyNumber = nullptr;
}

void Student::copyDynamic(const Student& other) {
    if (!other.name || !other.facultyNumber)
        throw std::invalid_argument("Null pointer in Student");

    char* newName = new char[strlen(other.name) + 1];
    strcpy(newName, other.name);

    char* newFN = new char[strlen(other.facultyNumber) + 1];
    strcpy(newFN, other.facultyNumber);

    freeDynamic();
    name = newName;
    facultyNumber = newFN;
}

Student::Student() {
    name = new char[1];
    name[0] = '\0';

    facultyNumber = new char[1];
    facultyNumber[0] = '\0';

    specialty = Specialty::Informatics;
}

Student::Student(const char* n, const char* fn, Specialty spec) {
    if (!n || !fn)
        throw std::invalid_argument("Null pointer");

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    facultyNumber = new char[strlen(fn) + 1];
    strcpy(facultyNumber, fn);

    specialty = spec;
}

Student::Student(const Student& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    facultyNumber = new char[strlen(other.facultyNumber) + 1];
    strcpy(facultyNumber, other.facultyNumber);

    specialty = other.specialty;
}

Student::~Student() {
    freeDynamic();
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Student temp(other);

        freeDynamic();
        name = temp.name;
        facultyNumber = temp.facultyNumber;

        temp.name = nullptr;
        temp.facultyNumber = nullptr;

        specialty = other.specialty;
    }
    return *this;
}

const char* Student::getName() const {
    return name;
}

const char* Student::getFacultyNumber() const {
    return facultyNumber;
}

Specialty Student::getSpecialty() const {
    return specialty;
}

void Student::setName(const char* newName) {
    if (!newName)
        throw std::invalid_argument("Null pointer");

    char* newData = new char[strlen(newName) + 1];
    strcpy(newData, newName);

    delete[] name;
    name = newData;
}

void Student::setFacultyNumber(const char* newFN) {
    if (!newFN)
        throw std::invalid_argument("Null pointer");

    char* newData = new char[strlen(newFN) + 1];
    strcpy(newData, newFN);

    delete[] facultyNumber;
    facultyNumber = newData;
}

void Student::setSpecialty(Specialty newSpec) {
    specialty = newSpec;
}
