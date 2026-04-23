#pragma once
#include "Computer.h"
#include "ConsultantUtils.h"

class ComputerShop {
private:
    char* name;
    Computer* computers;
    int size;
    int capacity;

    static ComputerShop* instance;

    void freeDynamic();
    void copyDynamic(const ComputerShop& other);
    void resize();

    ComputerShop(const char* n);

public:
    static ComputerShop* getInstance(const char* name);

    ComputerShop(const ComputerShop& other) = delete;
    ComputerShop& operator=(const ComputerShop& other) = delete;

    ~ComputerShop();

    void addComputer(const Computer& c);
    void printComputers() const;
    void buyComputer(const char* brand, double money);

    void printAvailable(bool gamingOnly, bool travelOnly) const;
};
