#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

enum Department {
    Algebra,
    Geometry,
    ComputerScience
};

struct Teacher {
private:
    char firstName[30];
    char lastName[30];
    Department department;

public:
    Teacher() {
        firstName[0] = '\0';
        lastName[0] = '\0';
        department = Algebra;
    }

    Teacher(const char* f, const char* l, Department d) {
        setFirstName(f);
        setLastName(l);
        department = d;
    }

    void setFirstName(const char* f) {
        if (!f || strlen(f) >= 30) return;
        strcpy(firstName, f);
    }

    void setLastName(const char* l) {
        if (!l || strlen(l) >= 30) return;
        strcpy(lastName, l);
    }

    const char* getFirstName() const { return firstName; }
    const char* getLastName() const { return lastName; }
    Department getDepartment() const { return department; }
};

struct Student {
private:
    char firstName[30];
    char lastName[30];
    int facultyNumber;
    double grades[32];
    int gradesCount;

public:
    Student() {
        firstName[0] = '\0';
        lastName[0] = '\0';
        facultyNumber = 0;
        gradesCount = 0;
    }

    Student(const char* f, const char* l, int fn) {
        setFirstName(f);
        setLastName(l);
        facultyNumber = fn;
        gradesCount = 0;
    }

    void setFirstName(const char* f) {
        if (!f || strlen(f) >= 30) return;
        strcpy(firstName, f);
    }

    void setLastName(const char* l) {
        if (!l || strlen(l) >= 30) return;
        strcpy(lastName, l);
    }

    int getFacultyNumber() const { return facultyNumber; }
    const char* getFirstName() const { return firstName; }
    const char* getLastName() const { return lastName; }

    void addGrade(double g) {
        if (gradesCount >= 32) return;
        if (g < 2 || g > 6) return;
        grades[gradesCount++] = g;
    }

    void removeLastGrade() {
        if (gradesCount > 0) gradesCount--;
    }

    double getAverage() const {
        if (gradesCount == 0) return 0;

        double sum = 0;
        for (int i = 0; i < gradesCount; i++) {
            sum += grades[i];
        }
        return sum / gradesCount;
    }

    int getGradesCount() const { return gradesCount; }
    const double* getGrades() const { return grades; }
};

struct Subject {
private:
    Student students[100];
    int studentsCount;

    Teacher teacher;
    bool hasTeacher;

public:
    Subject() {
        studentsCount = 0;
        hasTeacher = false;
    }

    void addStudent(const Student& s) {
        if (studentsCount >= 100) return;

        for (int i = 0; i < studentsCount; i++) {
            if (students[i].getFacultyNumber() == s.getFacultyNumber())
                return;
        }

        students[studentsCount++] = s;
    }

    void setTeacher(const Teacher& t) {
        teacher = t;
        hasTeacher = true;
    }

    void serialize(const char* file) const {
        if (!file) return;

        std::ofstream ofs(file, std::ios::binary);
        if (!ofs.is_open()) return;

        ofs.write((const char*)&studentsCount, sizeof(studentsCount));

        for (int i = 0; i < studentsCount; i++) {
            ofs.write((const char*)&students[i], sizeof(Student));
        }

        ofs.write((const char*)&hasTeacher, sizeof(hasTeacher));

        if (hasTeacher) {
            ofs.write((const char*)&teacher, sizeof(Teacher));
        }

        ofs.close();
    }

    void deserialize(const char* file) {
        if (!file) return;

        std::ifstream ifs(file, std::ios::binary);
        if (!ifs.is_open()) return;

        ifs.read((char*)&studentsCount, sizeof(studentsCount));

        if (studentsCount < 0 || studentsCount > 100) {
            studentsCount = 0;
            return;
        }

        for (int i = 0; i < studentsCount; i++) {
            ifs.read((char*)&students[i], sizeof(Student));
        }

        ifs.read((char*)&hasTeacher, sizeof(hasTeacher));

        if (hasTeacher) {
            ifs.read((char*)&teacher, sizeof(Teacher));
        }

        ifs.close();
    }

    void print() const {
        std::cout << "Students:\n";
        for (int i = 0; i < studentsCount; i++) {
            std::cout << students[i].getFirstName() << " "
                      << students[i].getLastName()
                      << " | FN: " << students[i].getFacultyNumber()
                      << " | Avg: " << students[i].getAverage()
                      << std::endl;
        }

        if (hasTeacher) {
            std::cout << "Teacher: "
                      << teacher.getFirstName() << " "
                      << teacher.getLastName()
                      << " | Department: " << teacher.getDepartment()
                      << std::endl;
        }
    }
};

int main() {
    Subject subject;

    Student s1("Ivan", "Ivanov", 123);
    s1.addGrade(5);
    s1.addGrade(6);

    Student s2("Petar", "Petrov", 456);
    s2.addGrade(4);

    subject.addStudent(s1);
    subject.addStudent(s2);

    Teacher t("Georgi", "Georgiev", ComputerScience);
    subject.setTeacher(t);

    subject.serialize("subject.dat");

    Subject loaded;
    loaded.deserialize("subject.dat");

    loaded.print();

    return 0;
}
