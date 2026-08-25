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
    void saveToFile() const;
    string getStatus() const;
    string getName() const;    // using get word for access the name in main function bcs name is in private.
};

#endif