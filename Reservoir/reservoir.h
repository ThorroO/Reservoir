#pragma once
#ifndef RESERVOIR_H
#define RESERVOIR_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Reservoir {
private:
    char* name;
    char* type;
    double width;
    double length;
    double maxDepth;

public:
    explicit Reservoir(const char* name = "Unknown", const char* type = "Unknown",
        double width = 0.0, double length = 0.0, double maxDepth = 0.0);
    Reservoir(const Reservoir& other);
    Reservoir& operator=(const Reservoir& other);
    ~Reservoir();

    double calculateVolume() const;
    double calculateSurfaceArea() const;
    bool isSameType(const Reservoir& other) const;
    bool hasLargerSurfaceArea(const Reservoir& other) const;

    void setName(const char* name);
    void setType(const char* type);
    void setDimensions(double width, double length, double maxDepth);

    const char* getName() const;
    const char* getType() const;
    double getWidth() const;
    double getLength() const;
    double getMaxDepth() const;

    void display() const;
    void saveToFile(ofstream& outFile) const;
    void loadFromFile(ifstream& inFile);
};

#endif