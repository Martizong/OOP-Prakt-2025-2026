#include "Shop.h"
#include <cstring>

void Shop::freeDynamic() {
    delete[] products;
    products = nullptr;
}

void Shop::copyDynamic(const Shop& other) {
    Product* newArr = new Product[other.capacity];

    for (int i = 0; i < other.size; i++)
        newArr[i] = other.products[i];

    freeDynamic();
    products = newArr;
}

void Shop::resize() {
    int newCap = capacity * 2;
    Product* newArr = new Product[newCap];

    for (int i = 0; i < size; i++)
        newArr[i] = products[i];

    delete[] products;
    products = newArr;
    capacity = newCap;
}

Shop::Shop() : size(0), capacity(4) {
    products = new Product[capacity];
}

Shop::Shop(const Shop& other) : products(nullptr), size(other.size), capacity(other.capacity) {
    copyDynamic(other);
}

Shop& Shop::operator=(const Shop& other) {
    if (this != &other) {
        Shop temp(other);

        freeDynamic();
        products = temp.products;
        temp.products = nullptr;

        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

Shop::~Shop() {
    freeDynamic();
}

void Shop::loadProducts(const char* name, ProductType type, double weight, int quantity, double price) {
    for (int i = 0; i < size; i++) {
        if (strcmp(products[i].getName(), name) == 0) {
            products[i].restock(quantity);
            return;
        }
    }

    if (size >= capacity)
        resize();

    products[size] = Product(name, type, weight, quantity, price);
    size++;
}

bool Shop::sellProduct(const char* name, int amount) {
    for (int i = 0; i < size; i++) {
        if (strcmp(products[i].getName(), name) == 0) {
            return products[i].sell(amount);
        }
    }
    return false;
}

void Shop::printInventory() const {
    std::cout << "=== INVENTORY ===\n";
    for (int i = 0; i < size; i++)
        products[i].printInfo();

    std::cout << "Total products: " << Product::getTotalProducts() << "\n";
    std::cout << "Total quantity: " << Product::getTotalQuantity() << "\n";
}
