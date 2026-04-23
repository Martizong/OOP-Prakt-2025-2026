#include "Product.h"

int Product::totalProducts = 0;
int Product::totalQuantity = 0;

void Product::freeDynamic() {
    delete[] name;
    name = nullptr;
}

void Product::copyDynamic(const Product& other) {
    if (!other.name)
        throw std::invalid_argument("Null name in source object");

    char* newName = nullptr;

    try {
        newName = new char[strlen(other.name) + 1];
        strcpy(newName, other.name);
    }
    catch (...) {
        delete[] newName;
        throw;
    }

    freeDynamic();
    name = newName;
}

Product::Product(const char* n, ProductType t, double w, int q, double p)
    : type(t), weight(w), quantity(q), price(p)
{
    if (!n)
        throw std::invalid_argument("Null name in constructor");

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    totalProducts++;
    totalQuantity += q;
}

Product::Product(const Product& other)
    : type(other.type), weight(other.weight),
      quantity(other.quantity), price(other.price)
{
    name = nullptr;
    copyDynamic(other);

    totalProducts++;
    totalQuantity += quantity;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        Product temp(other);

        freeDynamic();
        name = temp.name;
        temp.name = nullptr;

        totalQuantity -= quantity;
        quantity = other.quantity;
        totalQuantity += quantity;

        type = other.type;
        weight = other.weight;
        price = other.price;
    }
    return *this;
}

Product::~Product() {
    totalProducts--;
    totalQuantity -= quantity;
    freeDynamic();
}

const char* Product::getName() const { return name; }
ProductType Product::getType() const { return type; }
double Product::getWeight() const { return weight; }
int Product::getQuantity() const { return quantity; }
double Product::getPrice() const { return price; }

void Product::setName(const char* n) {
    if (!n)
        throw std::invalid_argument("Null name in setName");

    char* newData = new char[strlen(n) + 1];
    strcpy(newData, n);

    delete[] name;
    name = newData;
}

void Product::setType(ProductType t) { type = t; }
void Product::setWeight(double w) { weight = w; }

void Product::setQuantity(int q) {
    totalQuantity -= quantity;
    quantity = q;
    totalQuantity += q;
}

void Product::setPrice(double p) { price = p; }

void Product::printInfo() const {
    std::cout << "Name: " << name
              << ", Type: " << (int)type
              << ", Weight: " << weight
              << ", Quantity: " << quantity
              << ", Price: " << price << "\n";
}

void Product::restock(int amount) {
    if (amount < 0)
        throw std::invalid_argument("Negative restock amount");

    quantity += amount;
    totalQuantity += amount;
}

bool Product::sell(int amount) {
    if (amount <= 0)
        throw std::invalid_argument("Invalid sell amount");

    if (amount > quantity)
        return false;

    quantity -= amount;
    totalQuantity -= amount;
    return true;
}

int Product::getTotalProducts() { return totalProducts; }
int Product::getTotalQuantity() { return totalQuantity; }
