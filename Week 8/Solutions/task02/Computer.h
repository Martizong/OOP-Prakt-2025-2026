#pragma once
#include <cstring>
#include <stdexcept>
#include <fstream>

class Computer {
private:
    static unsigned serialCounter;

    unsigned serialNumber;
    char* brand;
    char* processor;
    int video;
    int hardDrive;
    int weight;
    int batteryLife;
    double price;
    int quantity;

    void freeDynamic();
    void copyDynamic(const Computer& other);

public:
    Computer();
    Computer(const char* brand, const char* processor,
             int video, int hardDrive, int weight,
             int batteryLife, double price, int quantity);

    Computer(const Computer& other);
    Computer(Computer&& other) noexcept;

    ~Computer();

    Computer& operator=(const Computer& other);
    Computer& operator=(Computer&& other) noexcept;

    unsigned getSerialNumber() const;
    const char* getBrand() const;
    const char* getProcessor() const;
    int getVideo() const;
    int getHardDrive() const;
    int getWeight() const;
    int getBatteryLife() const;
    double getPrice() const;
    int getQuantity() const;

    void setBrand(const char* b);
    void setProcessor(const char* p);
    void setVideo(int v);
    void setHardDrive(int h);
    void setWeight(int w);
    void setBatteryLife(int b);
    void setPrice(double p);
    void setQuantity(int q);

    void writeText(std::ofstream& ofs) const;
    void readText(std::ifstream& ifs);

    void writeBinary(std::ofstream& ofs) const;
    void readBinary(std::ifstream& ifs);

    static void saveSerialCounter(std::ofstream& ofs);
    static void loadSerialCounter(std::ifstream& ifs);
};
