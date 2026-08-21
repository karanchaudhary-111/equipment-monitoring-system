#include "Equipment.h"
#include <iostream>

using namespace std;

Equipment::Equipment(string name, double temperature, double pressure, double vibration)
{
    this->name = name;
    this->temperature = temperature;
    this->pressure = pressure;
    this->vibration = vibration;

    determineStatus();
}

void Equipment::determineStatus(){
    if(temperature <= 80 && pressure <= 6 && vibration <= 3){
        status = "NORMAL";
    }else if(temperature <= 100 && pressure <= 8 && vibration <= 5){
        status = "WARNING";
    }else{
        status = "CRITICAL";
    }
}

void Equipment::display() const
{
    cout << "Equipment: " << name << endl;
    cout << "Temperature: " << temperature << " C" << endl;
    cout << "Pressure: " << pressure << " bar" << endl;
    cout << "Vibration: " << vibration << " mm/s" << endl;
    cout << "Status: " << status << endl;

    showAlert();
}

void Equipment::showAlert() const
{
    if(status ==  "WARNING"){
        cout << "WARNING..." << name << " need monitoring." << endl;
    }

    if(status == "CRITICAL"){
        cout << "Alert..." << name << " requires immediate attention!" << endl;
    }
}