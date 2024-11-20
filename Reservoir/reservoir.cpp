#include "Reservoir.h"

Reservoir::Reservoir(const char* name, const char* type, double width, double length, double maxDepth)
    : width(width), length(length), maxDepth(maxDepth) {
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);

    this->type = new char[strlen(type) + 1];
    strcpy_s(this->type, strlen(type) + 1, type);
}

Reservoir::Reservoir(const Reservoir& other)
    : width(other.width), length(other.length), maxDepth(other.maxDepth) {
    name = new char[strlen(other.name) + 1];
    strcpy_s(name, strlen(other.name) + 1, other.name);

    type = new char[strlen(other.type) + 1];
    strcpy_s(type, strlen(other.type) + 1, other.type);
}

Reservoir& Reservoir::operator=(const Reservoir& other) {
    if (this != &other) {
        delete[] name;
        delete[] type;

        name = new char[strlen(other.name) + 1];
        strcpy_s(name, strlen(other.name) + 1, other.name);

        type = new char[strlen(other.type) + 1];
        strcpy_s(type, strlen(other.type) + 1, other.type);

        width = other.width;
        length = other.length;
        maxDepth = other.maxDepth;
    }
    return *this;
}

Reservoir::~Reservoir() {
    delete[] name;
    delete[] type;
}

double Reservoir::calculateVolume() const {
    return width * length * maxDepth;
}

double Reservoir::calculateSurfaceArea() const {
    return width * length;
}

bool Reservoir::isSameType(const Reservoir& other) const {
    return strcmp(type, other.type) == 0;
}

bool Reservoir::hasLargerSurfaceArea(const Reservoir& other) const {
    return calculateSurfaceArea() > other.calculateSurfaceArea();
}

void Reservoir::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

void Reservoir::setType(const char* type) {
    delete[] this->type;
    this->type = new char[strlen(type) + 1];
    strcpy_s(this->type, strlen(type) + 1, type);
}

void Reservoir::setDimensions(double width, double length, double maxDepth) {
    this->width = width;
    this->length = length;
    this->maxDepth = maxDepth;
}

const char* Reservoir::getName() const {
    return name;
}

const char* Reservoir::getType() const {
    return type;
}

double Reservoir::getWidth() const {
    return width;
}

double Reservoir::getLength() const {
    return length;
}

double Reservoir::getMaxDepth() const {
    return maxDepth;
}

void Reservoir::display() const {
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    cout << "Width: " << width << endl;
    cout << "Length: " << length << endl;
    cout << "Max Depth: " << maxDepth << endl;
    cout << "Volume: " << calculateVolume() << endl;
    cout << "Surface Area: " << calculateSurfaceArea() << endl;
}

void Reservoir::saveToFile(ofstream& outFile) const {
    size_t nameLength = strlen(name) + 1;
    size_t typeLength = strlen(type) + 1;

    outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    outFile.write(name, nameLength);
    outFile.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    outFile.write(type, typeLength);
    outFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
    outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    outFile.write(reinterpret_cast<const char*>(&maxDepth), sizeof(maxDepth));
}

void Reservoir::loadFromFile(ifstream& inFile) {
    size_t nameLength, typeLength;

    inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    delete[] name;
    name = new char[nameLength];
    inFile.read(name, nameLength);

    inFile.read(reinterpret_cast<char*>(&typeLength), sizeof(typeLength));
    delete[] type;
    type = new char[typeLength];
    inFile.read(type, typeLength);

    inFile.read(reinterpret_cast<char*>(&width), sizeof(width));
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
    inFile.read(reinterpret_cast<char*>(&maxDepth), sizeof(maxDepth));
}