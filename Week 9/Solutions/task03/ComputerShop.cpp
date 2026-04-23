#include "ComputerShop.h"
#include <cstring>

ComputerShop* ComputerShop::instance = nullptr;

void ComputerShop::freeDynamic() {
    delete[] name;
    delete[] computers;
    name = nullptr;
    computers = nullptr;
    size = 0;
    capacity = 0;
}

void ComputerShop::copyDynamic(const ComputerShop& other) {
    char* newName = new char[strlen(other.name) + 1];
    strcpy(newName, other.name);

    Computer* newArr = new Computer[other.capacity];
    for (int i = 0; i < other.size; i++)
        newArr[i] = other.computers[i];

    freeDynamic();
    name = newName;
    computers = newArr;
    size = other.size;
    capacity = other.capacity;
}

void ComputerShop::resize() {
    int newCap = capacity * 2;
    Computer* newArr = new Computer[newCap];

    for (int i = 0; i < size; i++)
        newArr[i] = computers[i];

    delete[] computers;
    computers = newArr;
    capacity = newCap;
}

ComputerShop::ComputerShop(const char* n)
    : size(0), capacity(4)
{
    if (!n)
        throw std::invalid_argument("Null shop name");

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    computers = new Computer[capacity];
}

ComputerShop* ComputerShop::getInstance(const char* name) {
    if (!instance)
        instance = new ComputerShop(name);
    return instance;
}

ComputerShop::~ComputerShop() {
    freeDynamic();
}

void ComputerShop::addComputer(const Computer& c) {
    for (int i = 0; i < size; i++) {
        if (strcmp(computers[i].getBrand(), c.getBrand()) == 0) {
            computers[i].addQuantity(c.getQuantity());
            return;
        }
    }

    if (size >= capacity)
        resize();

    computers[size] = c;
    size++;
}

void ComputerShop::printComputers() const {
    std::cout << "=== " << name << " Inventory ===\n";
    for (int i = 0; i < size; i++)
        computers[i].print();
}

void ComputerShop::buyComputer(const char* brand, double money) {
    for (int i = 0; i < size; i++) {
        if (strcmp(computers[i].getBrand(), brand) == 0) {
            if (money < computers[i].getPrice())
                throw std::runtime_error("Not enough money");

            if (!computers[i].removeQuantity(1))
                throw std::runtime_error("Out of stock");

            return;
        }
    }
    throw std::runtime_error("Computer not found");
}

void ComputerShop::printAvailable(bool gamingOnly, bool travelOnly) const {
    for (int i = 0; i < size; i++) {
        if (computers[i].getQuantity() <= 0)
            continue;

        if (gamingOnly && !ConsultantUtils::isGoodForGaming(computers[i]))
            continue;

        if (travelOnly && !ConsultantUtils::isGoodForTravel(computers[i]))
            continue;

        computers[i].print();
    }
}
