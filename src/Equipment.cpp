#include "Equipment.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor: initializes a new equipment object with its sensor readings.
Equipment::Equipment(string name, double temperature, double pressure, double vibration)
{
    this->name = name;
    this->temperature = temperature;
    this->pressure = pressure;
    this->vibration = vibration;

    determineStatus();
}

// Determines the equipment condition based on the current
// temperature, pressure, and vibration readings.
void Equipment::determineStatus(){
    if(temperature <= 80 && pressure <= 6 && vibration <= 3){
        status = "NORMAL";
    }else if(temperature <= 100 && pressure <= 8 && vibration <= 5){
        status = "WARNING";
    }else{
        status = "CRITICAL";
    }
}


// Displays the current sensor readings and status of the equipment.
// After displaying the data, showAlert() checks whether an alert is required.
void Equipment::display() const
{
    cout << "Equipment: " << name << endl;
    cout << "Temperature: " << temperature << " C" << endl;
    cout << "Pressure: " << pressure << " bar" << endl;
    cout << "Vibration: " << vibration << " mm/s" << endl;
    cout << "Status: " << status << endl;

    showAlert();
}

// Displays an alert only when the equipment is in WARNING or CRITICAL state.
// NORMAL equipment does not require an alert.
void Equipment::showAlert() const
{
    if(status ==  "WARNING"){
        cout << "WARNING..." << name << " need monitoring." << endl;
    }

    if(status == "CRITICAL"){
        cout << "Alert..." << name << " requires immediate attention!" << endl;
    }
}

// Saves the current equipment details to equipment_report.txt.
// ios::app is used so new reports are added without deleting previous data.
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

// Getter functions provide read-only access to private equipment data.
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

// Updates the sensor readings while preserving the previous reading.
void Equipment:: updateReadings(double newTemperature, double newPressure, double newVibration)
{
    // Save the current reading before replacing it with new values.
    Reading oldReading;

    oldReading.temperature = temperature;
    oldReading.pressure    = pressure;
    oldReading.vibration   = vibration;
    oldReading.status      = status;

    history.push_back(oldReading);

    // Remember the old status for status-change detection.
    string oldStatus = status;

    // Replace the sensor values with the new readings.
    this->temperature = newTemperature;
    this->pressure    = newPressure;
    this->vibration   = newVibration;

    // Acts as a bridge between the new sensor values and the new status.
    determineStatus();

    // If the status changed, store the transition in statusHistory.
    if(oldStatus != status)
    {
        string transition = oldStatus + " -> " + status;
        statusHistory.push_back(transition);

        cout << "Status changed: " << transition << endl;
    }
}

// Displays all PREVIOUS readings stored before equipment updates.
// The current/latest reading is stored in the Equipment object itself,
// so it is not part of this history vector.
void Equipment::displayHistory() const
{
    if(history.empty()){
        cout << "No previous readings available." << endl;
    }else{
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
}

// Displays only the recorded STATUS TRANSITIONS.
// Example: CRITICAL -> NORMAL, NORMAL -> WARNING.
// Updates that keep the same status are not stored here.
void Equipment::displayStatusHistory() const
{
    if(statusHistory.empty())
    {
        cout << "No status changes recorded." << endl;
        return;
    }

    int count = 1;

    for(const string &transition : statusHistory)
    {
        cout << count << ". " << transition << endl;
        count++;
    }
}

string getTrend(double previous, double current)
{
    if(current > previous)
    {
        return "INCREASING";
    }
    else if(current < previous)
    {
        return "DECREASING";
    }
    else
    {
        return "STABLE";
    }
}

void Equipment:: analyzeTrend() const
{
    if(history.empty())
    {
        cout << "No previous readings available for trend analysis." << endl;
        return;
    }

    int choice;

    cout << "\n1. Latest Trend" << endl;
    cout << "2. Overall Trend" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if(choice == 1)
    {
        double previousTemp = history.back().temperature;
        double previousPressure = history.back().pressure;
        double previousVibration = history.back().vibration;

        cout << "\n===== LATEST TREND =====" << endl;

        cout << "Temperature Trend: "
            << getTrend(previousTemp, temperature) << endl;

        cout << "Pressure Trend: "
            << getTrend(previousPressure, pressure) << endl;

        cout << "Vibration Trend: "
            << getTrend(previousVibration, vibration) << endl;
        }

    else if(choice == 2)
    {
        // OVERALL TREND CODE HERE
        int n = history.size();
        int i = 0;

        while(i < n - 1)
        {
            double currentTemp = history[i].temperature;
            double nextTemp = history[i + 1].temperature;

            cout << "\nReading " << i + 1 << " -> Reading " << i + 2 << endl;
            cout << "Temperature Trend: " << getTrend(currentTemp, nextTemp) << endl;

            double currentPressure = history[i].pressure;
            double nextPressure = history[i + 1].pressure;
            cout << "Pressure Trend: " << getTrend(currentPressure, nextPressure) << endl;


            double currentVibration = history[i].vibration;
            double nextVibration = history[i + 1].vibration;
            cout << "Vibration Trend: " << getTrend(currentVibration, nextVibration) << endl;

            i++;
        }

        cout << "\nReading " << n << " -> Current Reading" << endl;

        double lastTemp = history.back().temperature;
        cout << "Temperature Trend: " << getTrend(lastTemp, temperature) << endl;


        double lastPressure = history.back().pressure;
        cout << "Pressure Trend: " << getTrend(lastPressure, pressure) << endl;


        double lastVibration = history.back().vibration;
        cout << "Vibration Trend: " << getTrend(lastVibration, vibration) << endl;

    }else
    {
        cout << "Invalid choice." << endl;
    }
}
