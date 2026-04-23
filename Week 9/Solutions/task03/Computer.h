#pragma once
#include <cstring>
#include <stdexcept>
#include <iostream>

class Computer {
private:
    char* brand;
    char* processor;
    int video;
    int hardDrive;
    double weight;
    double batteryLife;
    double price;
    int quantity;

    void freeDynamic();
    void copyDynamic(const Computer& other);

public:
    Computer();
    Computer(const char* b, const char* p, int v, int h, double w, double bl, double pr, int q);
    Computer(const Computer& other);
    Computer& operator=(const Computer& other);
    ~Computer();

    const char* getBrand() const;
    const char* getProcessor() const;
    int getVideo() const;
    int getHardDrive() const;
    double getWeight() const;
    double getBatteryLife() const;
    double getPrice() const;
    int getQuantity() const;

    void addQuantity(int q);
    bool removeQuantity(int q);

    void print() const;
};
