#pragma once
#include "ShopType.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

enum class ShopType {
    Food,
    Drink,
    NonFood
};

class Shop {
private:
    char* name;
    ShopType type;
    int weight;
    int quantity;
    double price;

    static int totalProducts;
    static int totalQuantity;

    void freeDynamic();
    void copyDynamic(const Shop& other);

public:
    Shop(const char* n, ShopType t, int w, int q, double p);
    Shop(const Shop& other);
    Shop& operator=(const Shop& other);
    ~Shop();

    const char* getName() const;
    ShopType getType() const;
    int getWeight() const;
    int getQuantity() const;
    double getPrice() const;

    void setName(const char* n);
    void setType(ShopType t);
    void setWeight(int w);
    void setQuantity(int q);
    void setPrice(double p);

    void printInfo() const;
    void printInventory() const; 

    void loadProducts(int newQuantity);
    bool sellProduct(int amount);

    static int getTotalProducts();
    static int getTotalQuantity();
};
