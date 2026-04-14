#include "Stock.h"
#include <cstring>

#pragma warning(disable:4996)

void Stock::freeDynamic() {
    if (abbreviation) delete[] abbreviation;
    if (name) delete[] name;
    abbreviation = nullptr;
    name = nullptr;
}

void Stock::copyDynamic(const Stock& other) {
    if (other.abbreviation) {
        abbreviation = new char[strlen(other.abbreviation) + 1];
        strcpy(abbreviation, other.abbreviation);
    } else {
        abbreviation = new char[1];
        abbreviation[0] = '\0';
    }

    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    } else {
        name = new char[1];
        name[0] = '\0';
    }
}

Stock::Stock() {
    abbreviation = new char[1];
    abbreviation[0] = '\0';

    name = new char[1];
    name[0] = '\0';

    for (int i = 0; i < 12; i++)
        prices[i] = 0;
}

Stock::Stock(const char* abbr, const char* nm, const double* pr) {
    if (!abbr || strlen(abbr) == 0) {
        abbreviation = new char[1];
        abbreviation[0] = '\0';
    } else {
        abbreviation = new char[strlen(abbr) + 1];
        strcpy(abbreviation, abbr);
    }

    if (!nm || strlen(nm) == 0) {
        name = new char[1];
        name[0] = '\0';
    } else {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
    }

    if (!pr) {
        for (int i = 0; i < 12; i++) prices[i] = 0;
    } else {
        for (int i = 0; i < 12; i++) prices[i] = pr[i];
    }
}

Stock::Stock(const Stock& other) {
    copyDynamic(other);
    for (int i = 0; i < 12; i++)
        prices[i] = other.prices[i];
}

Stock& Stock::operator=(const Stock& other) {
    if (this != &other) {

       
        char* newAbbr = nullptr;
        char* newName = nullptr;

        
        if (other.abbreviation) {
            newAbbr = new char[strlen(other.abbreviation) + 1];
            strcpy(newAbbr, other.abbreviation);
        } else {
            newAbbr = new char[1];
            newAbbr[0] = '\0';
        }

        if (other.name) {
            newName = new char[strlen(other.name) + 1];
            strcpy(newName, other.name);
        } else {
            newName = new char[1];
            newName[0] = '\0';
        }

        
        delete[] abbreviation;
        delete[] name;

        abbreviation = newAbbr;
        name = newName;

        for (int i = 0; i < 12; i++)
            prices[i] = other.prices[i];
    }
    return *this;
}

Stock::~Stock() {
    freeDynamic();
}

void Stock::setAbbreviation(const char* abbr) {
    if (!abbr || strlen(abbr) == 0) return;

    char* newAbbr = new char[strlen(abbr) + 1];
    strcpy(newAbbr, abbr);

    delete[] abbreviation;
    abbreviation = newAbbr;
}

void Stock::setName(const char* nm) {
    if (!nm || strlen(nm) == 0) return;

    char* newName = new char[strlen(nm) + 1];
    strcpy(newName, nm);

    delete[] name;
    name = newName;
}

void Stock::setPrices(const double* pr) {
    if (!pr) return;
    for (int i = 0; i < 12; i++)
        prices[i] = pr[i];
}

const char* Stock::getAbbreviation() const { return abbreviation; }
const char* Stock::getName() const { return name; }
const double* Stock::getPrices() const { return prices; }

bool Stock::isProfitable() const {
    int up = 0, down = 0;

    for (int i = 1; i < 12; i++) {
        if (prices[i] > prices[i - 1]) up++;
        else if (prices[i] < prices[i - 1]) down++;
    }

    bool trend = up > down;

    bool tenPercent =
        prices[11] >= prices[0] * 1.10;

    return trend && tenPercent;
}
