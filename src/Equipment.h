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

    // TO CALCULATE AND GET STATUS
    void determineStatus();

    // DISPLAY A ALL EQUIPMENT IN TERMINAL
    void display() const;

    // CHECK ALERT AND GIVE ME A WARNING
    void showAlert() const;

    // ALL OUTPUT SAVE IN FILE 
    void saveToFile() const;

    // ACCESS PRIVATE VALUE IN MAIN.CPP
    string getStatus() const;
    string getName() const;    // using get word for access the name in main function bcs name is in private.
    double getTemp() const;
    double getPressure() const;
    double getVibration() const;

    // UPDATE THE READING AND SAVE THE PREVIOUS READING IN HISTORY
    void updateReadings(double newTemperature, double newPressure, double newVibration);

    // DISPLAY THE ALL HISTORY IN TERMINAL
    void displayHistory() const;
    void displayStatusHistory() const;

    // USED TO RESTORE EQUIPMENTS
    void analyzeTrend() const;

    // Used when restoring old readings from saved data
    void addHistoryReading(Reading reading);

    // HISTORY  IS IN PRIVATE THAT'S WHY  I USED THIS IN PUBLIC TO ACCESS
    vector<Reading> getHistory() const;
    vector<string> getStatusHistory() const;

    // USED FOR RESTORE STATUS  HISTORY
    void addStatusHistory(string transition);


};

#endif