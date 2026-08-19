#include "Equipment.h"
#include <iostream>

using namespace std;

Equipment::Equipment(string name, double temperature, double pressure, double vibration, string status)
{
    this->name = name;
    this->temperature = temperature;
    this->pressure = pressure;
    this->vibration = vibration;
    this->status = status;
}

void Equipment::display()
{
    cout << "Equipment: " << name << endl;
    cout << "Temperature: " << temperature << " C" << endl;
    cout << "Pressure: " << pressure << " bar" << endl;
    cout << "Vibration: " << vibration << " mm/s" << endl;
    cout << "Status: " << status << endl;
}