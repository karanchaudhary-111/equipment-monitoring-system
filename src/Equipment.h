#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <vector>

using namespace std;

struct Reading
{
    double temperature;
    double pressure;
    double vibration;
    string status;
};

class Equipment
{
private:
    string name;
    double temperature;
    double pressure;
    double vibration;
    string status;
    vector<Reading> history;
    vector<string> statusHistory;

public:
    Equipment(string name, double temperature, double pressure, double vibration);

    void determineStatus();
    void display() const;
    void showAlert() const;
    void saveToFile() const;
    string getStatus() const;
    string getName() const;    // using get word for access the name in main function bcs name is in private.
    double getTemp() const;
    double getPressure() const;
    double getVibration() const;
    void updateReadings(double newTemperature, double newPressure, double newVibration);
    void displayHistory() const;
    void displayStatusHistory() const;

    // USED TO RESTORE EQUIPMENTS
    void analyzeTrend() const;

    // Used when restoring old readings from saved data
    void addHistoryReading(Reading reading);

    // HISTORY  IS IN PRIVATE THAT'S WHY  I USED THIS IN PUBLIC TO ACCESS
    vector<Reading> getHistory() const;

};

#endif