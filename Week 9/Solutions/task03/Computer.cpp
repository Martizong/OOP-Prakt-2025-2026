#include "Computer.h"

void Computer::freeDynamic() {
    delete[] brand;
    delete[] processor;
    brand = nullptr;
    processor = nullptr;
}

void Computer::copyDynamic(const Computer& other) {
    char* newBrand = new char[strlen(other.brand) + 1];
    strcpy(newBrand, other.brand);

    char* newProcessor = new char[strlen(other.processor) + 1];
    strcpy(newProcessor, other.processor);

    freeDynamic();
    brand = newBrand;
    processor = newProcessor;
}

Computer::Computer()
    : brand(nullptr), processor(nullptr), video(0), hardDrive(0),
      weight(0), batteryLife(0), price(0), quantity(0) {}

Computer::Computer(const char* b, const char* p, int v, int h, double w, double bl, double pr, int q)
    : video(v), hardDrive(h), weight(w), batteryLife(bl), price(pr), quantity(q)
{
    if (!b || !p)
        throw std::invalid_argument("Null brand or processor");

    brand = new char[strlen(b) + 1];
    strcpy(brand, b);

    processor = new char[strlen(p) + 1];
    strcpy(processor, p);
}

Computer::Computer(const Computer& other)
    : video(other.video), hardDrive(other.hardDrive),
      weight(other.weight), batteryLife(other.batteryLife),
      price(other.price), quantity(other.quantity)
{
    brand = nullptr;
    processor = nullptr;
    copyDynamic(other);
}

Computer& Computer::operator=(const Computer& other) {
    if (this != &other) {
        Computer temp(other);

        freeDynamic();
        brand = temp.brand;
        processor = temp.processor;
        temp.brand = nullptr;
        temp.processor = nullptr;

        video = other.video;
        hardDrive = other.hardDrive;
        weight = other.weight;
        batteryLife = other.batteryLife;
        price = other.price;
        quantity = other.quantity;
    }
    return *this;
}

Computer::~Computer() {
    freeDynamic();
}

const char* Computer::getBrand() const { return brand; }
const char* Computer::getProcessor() const { return processor; }
int Computer::getVideo() const { return video; }
int Computer::getHardDrive() const { return hardDrive; }
double Computer::getWeight() const { return weight; }
double Computer::getBatteryLife() const { return batteryLife; }
double Computer::getPrice() const { return price; }
int Computer::getQuantity() const { return quantity; }

void Computer::addQuantity(int q) { quantity += q; }

bool Computer::removeQuantity(int q) {
    if (q > quantity) return false;
    quantity -= q;
    return true;
}

void Computer::print() const {
    std::cout << brand << " | CPU: " << processor
              << " | GPU: " << video
              << " | HDD: " << hardDrive
              << " | Weight: " << weight
              << " | Battery: " << batteryLife
              << " | Price: " << price
              << " | Qty: " << quantity << "\n";
}
