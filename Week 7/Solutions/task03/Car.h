#pragma once
#include "Engine.h"
#include "Wheel.h"

enum class Manufacturer { Toyota, BMW, Mercedes, Tesla, Unknown };

class Car {
private:
    char* regNumber = nullptr;
    Manufacturer manufacturer;
    char* model = nullptr;
    double fuelConsumption[3];
    Engine engine;
    Wheel* wheel;

    void freeDynamic();
    void copyDynamic(const Car& other);

public:
    Car();
    Car(const char* reg, Manufacturer m, const char* mod,
        const double* fuel, const Engine& e, Wheel* w);

    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car();

    void setRegNumber(const char* r);
    void setManufacturer(Manufacturer m);
    void setModel(const char* mod);
    void setFuelConsumption(const double* f);
    void setEngine(const Engine& e);
    void setWheel(Wheel* w);

    const char* getRegNumber() const;
    Manufacturer getManufacturer() const;
    const char* getModel() const;
    const double* getFuelConsumption() const;
    const Engine& getEngine() const;
    Wheel* getWheel() const;

    bool isFuelEfficient() const;
    bool isMoreFuelEfficient(const Car& other) const;

    void print() const;
};
