#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

using namespace std;

class Equipment
{
private:
    string name;
    double temperature;
    double pressure;
    double vibration;
    string status;

public:
    Equipment(string name, double temperature, double pressure, double vibration);

    void determineStatus();
    void display() const;
    void showAlert() const;
};

#endif