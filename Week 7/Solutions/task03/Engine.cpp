#include "Engine.h"
#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

Engine::Engine() {
    power = 0;
    displacement = 0;
    vin[0] = '\0';
}

Engine::Engine(int p, int d, const char* v) {
    power = (p >= 0 ? p : 0);
    displacement = (d >= 0 ? d : 0);

    if (!v || std::strlen(v) != 17) {
        vin[0] = '\0';
    } else {
        std::strcpy(vin, v);
    }
}

void Engine::setPower(int p) {
    if (p >= 0) power = p;
}

void Engine::setDisplacement(int d) {
    if (d >= 0) displacement = d;
}

void Engine::setVIN(const char* v) {
    if (!v || std::strlen(v) != 17) return;
    std::strcpy(vin, v);
}

int Engine::getPower() const { return power; }
int Engine::getDisplacement() const { return displacement; }
const char* Engine::getVIN() const { return vin; }

void Engine::print() const {
    std::cout << "Engine: " << power << " HP, "
              << displacement << " cc, VIN: " << vin << '\n';
}
