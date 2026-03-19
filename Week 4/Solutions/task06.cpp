#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable : 4996)

const int MAX_LENGTH = 25;
const char FILE_PATH[] = "offers-database.dat";

// Изчистване на входния поток
void flushStream() {
    std::cin.clear();
    std::cin.ignore(1024, '\n');
}

struct jobOffer {
    char name[MAX_LENGTH];
    int peopleCount;
    int restDaysCount;
    long long salary;
};

// Създаване на оферта
jobOffer createOffer(const char* name, int colCount, int restDays, long long salary) {
    jobOffer o;
    strcpy(o.name, name);
    o.peopleCount = colCount;
    o.restDaysCount = restDays;
    o.salary = salary;
    return o;
}

// Четене на оферта от клавиатура
jobOffer readOffer() {
    char name[MAX_LENGTH];
    int colCount, restDays;
    long long salary;

    std::cout << "Company name (max 25 chars): ";
    std::cin.getline(name, MAX_LENGTH);

    std::cout << "Colleague count: ";
    std::cin >> colCount;

    std::cout << "Rest days: ";
    std::cin >> restDays;

    std::cout << "Salary: ";
    std::cin >> salary;

    flushStream();
    return createOffer(name, colCount, restDays, salary);
}

// Запис в двоичен файл
void saveOfferToFile(std::ofstream& out, const jobOffer& o) {
    out.write((const char*)&o, sizeof(o));
}

// Четене от двоичен файл
bool readOffer(std::ifstream& in, jobOffer& o) {
    return (bool)in.read((char*)&o, sizeof(o));
}

// Добавяне на n оферти
void addOffers(const char* filePath, int n) {
    std::ofstream out(filePath, std::ios::binary | std::ios::app);
    if (!out) {
        std::cerr << "File error.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        jobOffer o = readOffer();
        saveOfferToFile(out, o);
    }
}

// Печат на оферта
void printOffer(const jobOffer& o) {
    std::cout << "-----------------------------\n";
    std::cout << "Company: " << o.name << "\n";
    std::cout << "Team size: " << o.peopleCount << "\n";
    std::cout << "Rest days: " << o.restDaysCount << "\n";
    std::cout << "Salary: " << o.salary << "\n";
    std::cout << "-----------------------------\n\n";
}

// Филтриране по минимална заплата
void filterOffers(const char* filePath, long long minSalary) {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) {
        std::cerr << "File error.\n";
        return;
    }

    jobOffer o;
    while (readOffer(in, o)) {
        if (o.salary >= minSalary)
            printOffer(o);
    }
}

// Проверка дали фирма съществува
bool existOffer(const char* filePath, const char* name) {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) return false;

    jobOffer o;
    while (readOffer(in, o)) {
        if (strcmp(o.name, name) == 0)
            return true;
    }
    return false;
}

// Проверка за "перфектна" оферта
bool isPerfect(const jobOffer& o, int maxCoworkers, int minVacancyDays, int minSalary) {
    return o.peopleCount <= maxCoworkers &&
           o.restDaysCount >= minVacancyDays &&
           o.salary >= minSalary;
}

// Запис на перфектни оферти в текстов файл
void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary) {
    std::ifstream in(filePath, std::ios::binary);
    std::ofstream out("perfect.txt");

    if (!in) {
        std::cerr << "File error.\n";
        return;
    }

    jobOffer o;
    while (readOffer(in, o)) {
        if (isPerfect(o, maxCoworkers, minVacancyDays, minSalary)) {
            out << o.name << " "
                << o.peopleCount << " "
                << o.restDaysCount << " "
                << o.salary << "\n";
        }
    }
}

// Печат на всички оферти
void printAll(const char* filePath) {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) {
        std::cerr << "File error.\n";
        return;
    }

    jobOffer o;
    while (readOffer(in, o)) {
        printOffer(o);
    }
}

// Система от команди
void runSystem(const char* filePath = FILE_PATH) {
    bool running = true;

    while (running) {
        std::cout << "Command: ";
        char c;
        std::cin >> c;
        flushStream();

        switch (c) {
        case 'a':
            addOffers(filePath, 1);
            break;

        case 'i':
            printAll(filePath);
            break;

        case 's': {
            char name[MAX_LENGTH];
            std::cout << "Company name: ";
            std::cin.getline(name, MAX_LENGTH);
            std::cout << (existOffer(filePath, name) ? "Exists\n" : "Not found\n");
            break;
        }

        case 'f': {
            long long minSalary;
            std::cout << "Min salary: ";
            std::cin >> minSalary;
            flushStream();
            filterOffers(filePath, minSalary);
            break;
        }

        case 'q':
            running = false;
            break;

        default:
            std::cout << "Unknown command.\n";
        }
    }
}

int main() {
    runSystem();
    return 0;
}
