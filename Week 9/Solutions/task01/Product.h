#pragma once
#include <cstring>
#include <stdexcept>
#include <iostream>

enum class ProductType {
    Food,
    Drink,
    Household,
    Other
};

class Product {
private:
    char* name;
    ProductType type;
    double weight;
    int quantity;
    double price;

    static int totalProducts;
    static int totalQuantity;

    void freeDynamic();
    void copyDynamic(const Product& other);

public:
    Product(const char* n, ProductType t, double w, int q, double p);
    Product(const Product& other);
    Product& operator=(const Product& other);
    ~Product();

    const char* getName() const;
    ProductType getType() const;
    double getWeight() const;
    int getQuantity() const;
    double getPrice() const;

    void setName(const char* n);
    void setType(ProductType t);
    void setWeight(double w);
    void setQuantity(int q);
    void setPrice(double p);

    void printInfo() const;
    void restock(int amount);
    bool sell(int amount);

    static int getTotalProducts();
    static int getTotalQuantity();
};
