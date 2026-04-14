#include "Car.h"
#include "Wheel.h"
#include "Engine.h"
#include <iostream>

int main() {
    Wheel w(18, Material::Aluminium);
    Engine e(150, 2000, "12345678901234567");

    double fuel[3] = {5.5, 6.0, 5.8};

    Car c("CA1234AB", Manufacturer::Toyota, "Corolla", fuel, e, &w);

    c.print();

    return 0;
}
