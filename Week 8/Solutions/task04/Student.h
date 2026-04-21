#pragma once
#include <cstring>
#include <stdexcept>

enum class Specialty {
    Informatics,
    InformationSystems,
    SoftwareEngineering,
    ComputerScience
};

class Student {
private:
    char* name;
    char* facultyNumber;
    Specialty specialty;

    void freeDynamic();
    void copyDynamic(const Student& other);

public:
    Student();
    Student(const char* name, const char* fn, Specialty spec);
    Student(const Student& other);
    ~Student();

    Student& operator=(const Student& other);

    const char* getName() const;
    const char* getFacultyNumber() const;
    Specialty getSpecialty() const;

    void setName(const char* newName);
    void setFacultyNumber(const char* newFN);
    void setSpecialty(Specialty newSpec);
};
