#include "ComputerShop.h"

int main() {
    ComputerShop* shop = ComputerShop::getInstance("TechWorld");

    shop->addComputer(Computer("Dell", "i7", 3070, 512, 2.2, 8, 2500, 5));
    shop->addComputer(Computer("HP", "i5", 3060, 512, 2.4, 7, 1800, 3));
    shop->addComputer(Computer("MacBook", "M1", 0, 256, 1.3, 12, 2000, 4));

    shop->printComputers();

    shop->buyComputer("Dell", 3000);

    std::cout << "\nGaming laptops:\n";
    shop->printAvailable(true, false);

    std::cout << "\nTravel laptops:\n";
    shop->printAvailable(false, true);

    return 0;
}
