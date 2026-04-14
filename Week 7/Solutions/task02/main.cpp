#include "Stock.h"
#include <iostream>

int main() {
    double prices[12] = { 10,11,12,13,14,15,16,17,18,19,20,22 };

    Stock s("AAPL", "Apple Inc.", prices);

    std::cout << "Profitable: " << (s.isProfitable() ? "Yes" : "No") << std::endl;

    return 0;
}
