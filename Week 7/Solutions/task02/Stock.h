#pragma once
#include <iostream>

class Stock {
private:
    char* abbreviation = nullptr;
    char* name = nullptr;
    double prices[12];

    void freeDynamic();
    void copyDynamic(const Stock& other);

public:
    Stock();
    Stock(const char* abbr, const char* nm, const double* pr);
    Stock(const Stock& other);
    Stock& operator=(const Stock& other);
    ~Stock();

    void setAbbreviation(const char* abbr);
    void setName(const char* nm);
    void setPrices(const double* pr);

    const char* getAbbreviation() const;
    const char* getName() const;
    const double* getPrices() const;

    bool isProfitable() const;
};
