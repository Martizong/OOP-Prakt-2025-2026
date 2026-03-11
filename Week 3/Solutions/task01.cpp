#include <iostream>
#include <fstream>

constexpr unsigned MAX_NAME_LENGHT = 64;

struct Person {
    char name[MAX_NAME_LENGHT];
    bool gender;
    unsigned age;
};

void writePersonsToFile(const Person* persons, size_t size, const char* fileName) {
    std::ofstream ofs(fileName);

    if (!ofs.is_open()) 
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    ofs << size << std::endl; 

    for (size_t i = 0; i < size; ++i) 
    {
        ofs << persons[i].name << ' ' << persons[i].gender << ' ' << persons[i].age << std::endl;
    }

    ofs.close();
}

Person* readPersonsFromFile(const char* fileName, size_t& size) 
{
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) 
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return nullptr;
    }

    ifs >> size; 
    Person* persons = new Person[size];

    for (size_t i = 0; i < size; ++i) 
    {
        ifs >> persons[i].name >> persons[i].gender >> persons[i].age;
        ifs.ignore();
    }

    ifs.close();

    return persons;
}
int main()
{
    Person persons[3] =
    {
        {"Ivan", true, 21},
        {"Maria", false, 19},
        {"Georgi", true, 30}
    };

    writePersonsToFile(persons, 3, "persons.txt");

    size_t size = 0;

    Person* loadedPersons = readPersonsFromFile("persons.txt", size);

    if (!loadedPersons)
        return 1;

    for (size_t i = 0; i < size; i++)
    {
        std::cout << loadedPersons[i].name << " " << loadedPersons[i].gender << " " << loadedPersons[i].age << std::endl;
    }

    delete[] loadedPersons;

    return 0;
}
