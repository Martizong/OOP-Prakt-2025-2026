#include "Computer.h"

unsigned Computer::serialCounter = 1;

void Computer::freeDynamic() {
    delete[] brand;
    delete[] processor;
    brand = nullptr;
    processor = nullptr;
}

void Computer::copyDynamic(const Computer& other) {
    if (!other.brand || !other.processor)
        throw std::invalid_argument("Invalid dynamic fields in source object");

    char* newBrand = nullptr;
    char* newProcessor = nullptr;

    try {
        newBrand = new char[strlen(other.brand) + 1];
        strcpy(newBrand, other.brand);

        newProcessor = new char[strlen(other.processor) + 1];
        strcpy(newProcessor, other.processor);
    }
    catch (...) {
        delete[] newBrand;
        delete[] newProcessor;
        throw;
    }

    freeDynamic();
    brand = newBrand;
    processor = newProcessor;
}

Computer::Computer() {
    serialNumber = serialCounter++;

    brand = new char[1];
    brand[0] = '\0';

    processor = new char[1];
    processor[0] = '\0';

    video = 0;
    hardDrive = 0;
    weight = 0;
    batteryLife = 0;
    price = 0;
    quantity = 0;
}

Computer::Computer(const char* b, const char* p,
                   int v, int h, int w,
                   int bl, double pr, int q) {
    if (!b || !p)
        throw std::invalid_argument("Null pointer passed to constructor");

    serialNumber = serialCounter++;

    brand = new char[strlen(b) + 1];
    strcpy(brand, b);

    processor = new char[strlen(p) + 1];
    strcpy(processor, p);

    video = v;
    hardDrive = h;
    weight = w;
    batteryLife = bl;
    price = pr;
    quantity = q;
}

Computer::Computer(const Computer& other) {
    serialNumber = other.serialNumber;

    brand = nullptr;
    processor = nullptr;

    copyDynamic(other);

    video = other.video;
    hardDrive = other.hardDrive;
    weight = other.weight;
    batteryLife = other.batteryLife;
    price = other.price;
    quantity = other.quantity;
}

Computer::Computer(Computer&& other) noexcept {
    serialNumber = other.serialNumber;

    brand = other.brand;
    processor = other.processor;

    other.brand = nullptr;
    other.processor = nullptr;

    video = other.video;
    hardDrive = other.hardDrive;
    weight = other.weight;
    batteryLife = other.batteryLife;
    price = other.price;
    quantity = other.quantity;
}

Computer::~Computer() {
    freeDynamic();
}

Computer& Computer::operator=(const Computer& other) {
    if (this != &other) {
        Computer temp(other);

        freeDynamic();
        brand = temp.brand;
        processor = temp.processor;

        temp.brand = nullptr;
        temp.processor = nullptr;

        serialNumber = other.serialNumber;
        video = other.video;
        hardDrive = other.hardDrive;
        weight = other.weight;
        batteryLife = other.batteryLife;
        price = other.price;
        quantity = other.quantity;
    }
    return *this;
}

Computer& Computer::operator=(Computer&& other) noexcept {
    if (this != &other) {
        freeDynamic();

        serialNumber = other.serialNumber;
        brand = other.brand;
        processor = other.processor;

        other.brand = nullptr;
        other.processor = nullptr;

        video = other.video;
        hardDrive = other.hardDrive;
        weight = other.weight;
        batteryLife = other.batteryLife;
        price = other.price;
        quantity = other.quantity;
    }
    return *this;
}

unsigned Computer::getSerialNumber() const { return serialNumber; }
const char* Computer::getBrand() const { return brand; }
const char* Computer::getProcessor() const { return processor; }
int Computer::getVideo() const { return video; }
int Computer::getHardDrive() const { return hardDrive; }
int Computer::getWeight() const { return weight; }
int Computer::getBatteryLife() const { return batteryLife; }
double Computer::getPrice() const { return price; }
int Computer::getQuantity() const { return quantity; }

void Computer::setBrand(const char* b) {
    if (!b)
        throw std::invalid_argument("Null pointer in setBrand");

    char* newData = new char[strlen(b) + 1];
    strcpy(newData, b);

    delete[] brand;
    brand = newData;
}

void Computer::setProcessor(const char* p) {
    if (!p)
        throw std::invalid_argument("Null pointer in setProcessor");

    char* newData = new char[strlen(p) + 1];
    strcpy(newData, p);

    delete[] processor;
    processor = newData;
}

void Computer::setVideo(int v) { video = v; }
void Computer::setHardDrive(int h) { hardDrive = h; }
void Computer::setWeight(int w) { weight = w; }
void Computer::setBatteryLife(int b) { batteryLife = b; }
void Computer::setPrice(double p) { price = p; }
void Computer::setQuantity(int q) { quantity = q; }

void Computer::writeText(std::ofstream& ofs) const {
    if (!ofs)
        throw std::runtime_error("Cannot write to text file");

    ofs << serialNumber << '\n'
        << brand << '\n'
        << processor << '\n'
        << video << '\n'
        << hardDrive << '\n'
        << weight << '\n'
        << batteryLife << '\n'
        << price << '\n'
        << quantity << '\n';
}

void Computer::readText(std::ifstream& ifs) {
    if (!ifs)
        throw std::runtime_error("Cannot read from text file");

    char buffer[256];

    if (!(ifs >> serialNumber))
        throw std::runtime_error("Invalid serial number");

    ifs.ignore();

    if (!ifs.getline(buffer, 256))
        throw std::runtime_error("Invalid brand");
    setBrand(buffer);

    if (!ifs.getline(buffer, 256))
        throw std::runtime_error("Invalid processor");
    setProcessor(buffer);

    if (!(ifs >> video >> hardDrive >> weight >> batteryLife >> price >> quantity))
        throw std::runtime_error("Invalid numeric fields");

    ifs.ignore();
}

void Computer::writeBinary(std::ofstream& ofs) const {
    if (!ofs)
        throw std::runtime_error("Cannot write to binary file");

    ofs.write((const char*)&serialNumber, sizeof(serialNumber));

    size_t len = strlen(brand);
    ofs.write((const char*)&len, sizeof(len));
    ofs.write(brand, len);

    len = strlen(processor);
    ofs.write((const char*)&len, sizeof(len));
    ofs.write(processor, len);

    ofs.write((const char*)&video, sizeof(video));
    ofs.write((const char*)&hardDrive, sizeof(hardDrive));
    ofs.write((const char*)&weight, sizeof(weight));
    ofs.write((const char*)&batteryLife, sizeof(batteryLife));
    ofs.write((const char*)&price, sizeof(price));
    ofs.write((const char*)&quantity, sizeof(quantity));
}

void Computer::readBinary(std::ifstream& ifs) {
    if (!ifs)
        throw std::runtime_error("Cannot read from binary file");

    ifs.read((char*)&serialNumber, sizeof(serialNumber));
    if (!ifs)
        throw std::runtime_error("Corrupted binary file");

    size_t len;

    ifs.read((char*)&len, sizeof(len));
    if (!ifs)
        throw std::runtime_error("Corrupted brand length");

    char* b = new char[len + 1];
    ifs.read(b, len);
    if (!ifs) {
        delete[] b;
        throw std::runtime_error("Corrupted brand data");
    }
    b[len] = '\0';
    setBrand(b);
    delete[] b;

    ifs.read((char*)&len, sizeof(len));
    if (!ifs)
        throw std::runtime_error("Corrupted processor length");

    char* p = new char[len + 1];
    ifs.read(p, len);
    if (!ifs) {
        delete[] p;
        throw std::runtime_error("Corrupted processor data");
    }
    p[len] = '\0';
    setProcessor(p);
    delete[] p;

    ifs.read((char*)&video, sizeof(video));
    ifs.read((char*)&hardDrive, sizeof(hardDrive));
    ifs.read((char*)&weight, sizeof(weight));
    ifs.read((char*)&batteryLife, sizeof(batteryLife));
    ifs.read((char*)&price, sizeof(price));
    ifs.read((char*)&quantity, sizeof(quantity));

    if (!ifs)
        throw std::runtime_error("Corrupted numeric fields");
}

void Computer::saveSerialCounter(std::ofstream& ofs) {
    if (!ofs)
        throw std::runtime_error("Cannot write serial counter");
    ofs << serialCounter << '\n';
}

void Computer::loadSerialCounter(std::ifstream& ifs) {
    if (!ifs)
        throw std::runtime_error("Cannot read serial counter");
    if (!(ifs >> serialCounter))
        throw std::runtime_error("Invalid serial counter");
    ifs.ignore();
}
