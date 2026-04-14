#include "Car.h"
#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

void Car::freeDynamic() {
    if (regNumber) delete[] regNumber;
    if (model) delete[] model;
    regNumber = nullptr;
    model = nullptr;
}

void Car::copyDynamic(const Car& other) {
    if (other.regNumber) {
        regNumber = new char[std::strlen(other.regNumber) + 1];
        std::strcpy(regNumber, other.regNumber);
    } else {
        regNumber = new char[1];
        regNumber[0] = '\0';
    }

    if (other.model) {
        model = new char[std::strlen(other.model) + 1];
        std::strcpy(model, other.model);
    } else {
        model = new char[1];
        model[0] = '\0';
    }
}

Car::Car() {
    regNumber = new char[1];
    regNumber[0] = '\0';

    model = new char[1];
    model[0] = '\0';

    manufacturer = Manufacturer::Unknown;

    for (int i = 0; i < 3; i++) fuelConsumption[i] = 0;

    wheel = nullptr;
}

Car::Car(const char* reg, Manufacturer m, const char* mod,
         const double* fuel, const Engine& e, Wheel* w)
    : engine(e)
{
    if (!reg || std::strlen(reg) == 0) {
        regNumber = new char[1];
        regNumber[0] = '\0';
    } else {
        regNumber = new char[std::strlen(reg) + 1];
        std::strcpy(regNumber, reg);
    }

    if (!mod || std::strlen(mod) == 0) {
        model = new char[1];
        model[0] = '\0';
    } else {
        model = new char[std::strlen(mod) + 1];
        std::strcpy(model, mod);
    }

    manufacturer = m;

    if (!fuel) {
        for (int i = 0; i < 3; i++) fuelConsumption[i] = 0;
    } else {
        for (int i = 0; i < 3; i++) fuelConsumption[i] = fuel[i];
    }

    wheel = w;
}

Car::Car(const Car& other)
    : engine(other.engine)
{
    copyDynamic(other);
    manufacturer = other.manufacturer;

    for (int i = 0; i < 3; i++)
        fuelConsumption[i] = other.fuelConsumption[i];

    wheel = other.wheel;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        char* newReg = nullptr;
        char* newModel = nullptr;

        if (other.regNumber) {
            newReg = new char[std::strlen(other.regNumber) + 1];
            std::strcpy(newReg, other.regNumber);
        } else {
            newReg = new char[1];
            newReg[0] = '\0';
        }

        if (other.model) {
            newModel = new char[std::strlen(other.model) + 1];
            std::strcpy(newModel, other.model);
        } else {
            newModel = new char[1];
            newModel[0] = '\0';
        }

        delete[] regNumber;
        delete[] model;

        regNumber = newReg;
        model = newModel;

        manufacturer = other.manufacturer;

        for (int i = 0; i < 3; i++)
            fuelConsumption[i] = other.fuelConsumption[i];

        engine = other.engine;
        wheel = other.wheel;
    }
    return *this;
}

Car::~Car() {
    freeDynamic();
}

void Car::setRegNumber(const char* r) {
    if (!r || std::strlen(r) == 0) return;

    char* newReg = new char[std::strlen(r) + 1];
    std::strcpy(newReg, r);

    delete[] regNumber;
    regNumber = newReg;
}

void Car::setManufacturer(Manufacturer m) {
    manufacturer = m;
}

void Car::setModel(const char* mod) {
    if (!mod || std::strlen(mod) == 0) return;

    char* newModel = new char[std::strlen(mod) + 1];
    std::strcpy(newModel, mod);

    delete[] model;
    model = newModel;
}

void Car::setFuelConsumption(const double* f) {
    if (!f) return;
    for (int i = 0; i < 3; i++) fuelConsumption[i] = f[i];
}

void Car::setEngine(const Engine& e) {
    engine = e;
}

void Car::setWheel(Wheel* w) {
    wheel = w;
}

const char* Car::getRegNumber() const { return regNumber; }
Manufacturer Car::getManufacturer() const { return manufacturer; }
const char* Car::getModel() const { return model; }
const double* Car::getFuelConsumption() const { return fuelConsumption; }
const Engine& Car::getEngine() const { return engine; }
Wheel* Car::getWheel() const { return wheel; }

bool Car::isFuelEfficient() const {
    double avg = (fuelConsumption[0] + fuelConsumption[1] + fuelConsumption[2]) / 3.0;
    return avg <= 6.0;
}

bool Car::isMoreFuelEfficient(const Car& other) const {
    double avg1 = (fuelConsumption[0] + fuelConsumption[1] + fuelConsumption[2]) / 3.0;
    double avg2 = (other.fuelConsumption[0] + other.fuelConsumption[1] + other.fuelConsumption[2]) / 3.0;
    return avg1 < avg2;
}

void Car::print() const {
    std::cout << "Car: " << regNumber << ", model=" << model
              << ", manufacturer=" << (int)manufacturer << '\n';

    std::cout << "Fuel: " << fuelConsumption[0] << ", "
              << fuelConsumption[1] << ", "
              << fuelConsumption[2] << '\n';

    engine.print();

    if (wheel) wheel->print();
}
