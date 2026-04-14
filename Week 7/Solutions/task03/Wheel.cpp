#include "Wheel.h"
#include <iostream>

Wheel::Wheel() {
    radius = 0;
    material = Material::Steel;
}

Wheel::Wheel(int r, Material m) {
    radius = (r >= 0 ? r : 0);
    material = m;
}

void Wheel::setRadius(int r) {
    if (r >= 0) radius = r;
}

void Wheel::setMaterial(Material m) {
    material = m;
}

int Wheel::getRadius() const { return radius; }
Material Wheel::getMaterial() const { return material; }

void Wheel::print() const {
    std::cout << "Wheel: " << radius << " inches, material=" << (int)material << '\n';
}
