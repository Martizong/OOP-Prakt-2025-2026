#pragma once
#include "Product.h"

class Shop {
private:
    Product* products;
    int size;
    int capacity;

    void freeDynamic();
    void copyDynamic(const Shop& other);
    void resize();

public:
    Shop();
    Shop(const Shop& other);
    Shop& operator=(const Shop& other);
    ~Shop();

    void loadProducts(const char* name, ProductType type, double weight, int quantity, double price);
    bool sellProduct(const char* name, int amount);

    void printInventory() const;
};
