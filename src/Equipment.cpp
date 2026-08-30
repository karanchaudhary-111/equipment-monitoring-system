#include "Equipment.h"
#include <iostream>
#include <fstream>

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

void Equipment::saveToFile() const
{
    ofstream file("equipment_report.txt", ios::app);

    file << "Equipment: " << name << endl;
    file << "Temperature: " << temperature << " C" << endl;
    file << "Pressure: " << pressure << " bar" << endl;
    file << "Vibration: " << vibration << " mm/s" << endl;
    file << "Status: " << status << endl;

    file << endl;
    file << "----------------------------" << endl;
    file << endl;

    file.close();
}

string Equipment::getStatus() const
{
    return status;
}

string Equipment::getName() const
{
    return name;
}

double Equipment:: getTemp() const
{
    return temperature;
}

double Equipment:: getPressure() const
{
    return pressure;
}

double Equipment:: getVibration() const
{
    return vibration;
}

void Equipment:: updateReadings(double newTemperature, double newPressure, double newVibration)
{
    Reading oldReading;

    oldReading.temperature = temperature;
    oldReading.pressure    = pressure;
    oldReading.vibration   = vibration;
    oldReading.status      = status;

     history.push_back(oldReading);


    this->temperature = newTemperature;
    this->pressure    = newPressure;
    this->vibration   = newVibration;

    determineStatus();
}

void Equipment::displayHistory() const
{
    cout << "Equipment: " << name << endl;
    int count = 1;
    for(const Reading &reading : history)
    {
        cout << "\nReading " << count << endl;
        cout << "Temperature: " << reading.temperature << " C" << endl;
        cout << "Pressure: " << reading.pressure << " bar" << endl;
        cout << "Vibration: " << reading.vibration << " mm/s" << endl;
        cout << "Status: " << reading.status << endl;
        cout << "----------------------" << endl;
        count++;

    }
}