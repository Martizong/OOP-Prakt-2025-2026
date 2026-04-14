#pragma once

class Engine {
private:
    int power;
    int displacement;
    char vin[18];

public:
    Engine();
    Engine(int p, int d, const char* v);

    void setPower(int p);
    void setDisplacement(int d);
    void setVIN(const char* v);

    int getPower() const;
    int getDisplacement() const;
    const char* getVIN() const;

    void print() const;
};
