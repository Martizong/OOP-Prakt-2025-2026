#include "Product.h"

int main() {
    Product p1("Bread", ProductType::Food, 0.5, 20, 1.20);
    Product p2("Cola", ProductType::Drink, 1.0, 50, 2.50);

    p1.printInfo();
    p2.printInfo();

    p1.restock(10);
    p2.sell(5);

    std::cout << "Total products: " << Product::getTotalProducts() << "\n";
    std::cout << "Total quantity: " << Product::getTotalQuantity() << "\n";

    return 0;
}
