#include <iostream>
#include "Equipment.h"
#include <vector>
# include <limits>
# include <fstream>
#include <sstream>

using namespace std;

// FOR GETTING VALID INPUT FROM USERS
double getValidInput(string prompt)
{
    double value;

    // // FOR INVALID INPUT FOR VALUE
    while(true){

        cout << prompt;
        cin >> value;

        if(cin.fail() || cin.peek() != '\n' || value < 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a valid number." << endl;
        }else // GETTING VALID INPUT THEN RETURN
        {
            return value;
        }
    }
}

//  USED TO RESTORE THE  EQUIPMENT PERMANENT 
void loadFromCSV(vector<Equipment>& equipmentList)
{
    ifstream file("equipment_data.csv");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string name;
        getline(ss, name, ',');

        string tempStr;
        getline(ss, tempStr, ',');
        double temperature = stod(tempStr);

        string pressureStr;
        getline(ss, pressureStr, ',');
        double pressure = stod(pressureStr);

        string vibrationStr;
        getline(ss, vibrationStr, ',');
        double vibration = stod(vibrationStr);

        string status;
        getline(ss, status);

        Equipment loadedEquipment(name, temperature, pressure, vibration);
        equipmentList.push_back(loadedEquipment);
    }
}

// SAVE ALL LOADED CSV EQUIPMENTS
void saveAllToCSV(const vector<Equipment>& equipmentList)
{
    ofstream file("equipment_data.csv");

    for(const Equipment &equipment : equipmentList)
    {
        file << equipment.getName() << ","
             << equipment.getTemp() << ","
             << equipment.getPressure() << ","
             << equipment.getVibration() << ","
             << equipment.getStatus() << endl;
    }

    file.close();
}

// LOAD HISTORY FROM CSV 
void loadHistoryFromCSV(vector<Equipment>& equipmentList)
{
    ifstream file("equipment_history.csv");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        string tempStr;
        getline(ss, tempStr, ',');
        double temperature = stod(tempStr);

        string pressureStr;
        getline(ss, pressureStr, ',');
        double pressure = stod(pressureStr);

        string vibrationStr;
        getline(ss, vibrationStr, ',');
        double vibration = stod(vibrationStr);

        string status;
        getline(ss, status);

        // CREATE READING OBJECT FROM LOADED CSV
        Reading reading;

        reading.temperature = temperature;
        reading.pressure = pressure;
        reading.vibration = vibration;
        reading.status = status;

        // Find which equipment this history belongs to
        for(Equipment &equipment : equipmentList)
        {
            if(equipment.getName() == name)
            {
                equipment.addHistoryReading(reading);
                break;
            }
        }

    }
}

// USED TO RESTORE THE HISTORY JUST LIKE EQUIPMENT CSV
void saveHistoryToCSV(const vector<Equipment>& equipmentList)
{
    ofstream file("equipment_history.csv");

    for(const Equipment &equipment : equipmentList)
    {
        vector<Reading> history = equipment.getHistory();

        for(const Reading &reading : history)
        {
            file << equipment.getName() << ","
                 << reading.temperature << ","
                 << reading.pressure << ","
                 << reading.vibration << ","
                 << reading.status << endl;
        }
    }

    file.close();
}

// CONVERT THIS FILE INTO CSV
void saveStatusHistoryToCSV(const vector<Equipment>& equipmentList)
{
    ofstream file("equipment_status_history.csv");

    for(const Equipment &equipment : equipmentList)
    {
        vector<string> statusHistory = equipment.getStatusHistory();

        for(const string &transition : statusHistory)
        {
            file << equipment.getName()
                 << ","
                 << transition
                 << endl;
        }
    }
}

// LOAD FROM CSV STATUS HISTORY
void loadStatusHistoryFromCSV(vector<Equipment>& equipmentList)
{
    ifstream file("equipment_status_history.csv");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string name;
        getline(ss, name, ',');

        string transition;
        getline(ss, transition);

        for(Equipment &equipment : equipmentList)
        {
            if(equipment.getName() == name)
            {
                equipment.addStatusHistory(transition);
                break;
            }
        }
    }
}

int main()
{
    vector<Equipment> equipmentList;

    loadFromCSV(equipmentList);
    loadHistoryFromCSV(equipmentList);
    loadStatusHistoryFromCSV(equipmentList);

    int normalCount  = 0;
    int warningCount = 0;
    int criticalCount   = 0;

    // FOR HOW MUCH EQUIPMENT YOU WANT
    int n;
    cout << "Enter number of equipments: ";
    cin >> n;
    
    if(n < 0){
        cout << "Number of Equipment cannot be negative." << endl;
        return 0;
    }
    cin.ignore();

    // FOR USER INPUT OF EQUIPMENT DETAILS
    for(int i = 0; i < n; i++){

        cout << "\nEnter details for Equipment " << i + 1 << endl;

        string name;
        cout << "Enter equipment name: ";
        getline(cin, name);

        // USING FUNC FOR GET VALID INPUT
        double temperature = getValidInput("Enter temperature: ");
        double pressure = getValidInput("Enter pressure: ");
        double vibration = getValidInput("Enter vibration: ");

        cin.ignore();

        Equipment newEquipment(name, temperature, pressure, vibration);

        equipmentList.push_back(newEquipment);

    }

    // CHECK THE VECTOR IS  EMPTY OR NOT AFTER UPDATE THEIR INPUTS
    if(equipmentList.empty())
    {
        cout << "\nNo equipment available." << endl;
        return 0;
    }

    cout << endl << endl;

    vector<string> criticalEquipment;

    // SEARCH A EQUIPMENT NAME AND THEIR DETAILS BY DIRECTLY
    string searchName;

    cout << "\nEnter equipment name to search: ";
    getline(cin, searchName);

    // TO CHANGE LOWERCASE OF SEARCHNAME
    for(int i = 0; i < searchName.size(); i++)
    {
        if(searchName[i] >= 'A' && searchName[i] <= 'Z')
        {
            char ch = searchName[i] - 'A' + 'a';
            searchName[i] = ch;
        }
    }

    bool  found = false;

    for(int idx = 0; idx < equipmentList.size(); idx++){

        string equipmentName = equipmentList[idx].getName();

        for(int i = 0; i < equipmentName.size(); i++)
        {
            // TO CHANGE STORED EQUIPMENT NAME
            if(equipmentName[i] >= 'A' && equipmentName[i] <= 'Z')
            {
                char ch = equipmentName[i] - 'A' + 'a';
                equipmentName[i] = ch;
            }
        }

        if(equipmentName == searchName){

            cout << "\n===== SEARCH RESULT =====" << endl;
            equipmentList[idx].display();

            char choice;

            // UPDATE NEW READING OF EQUIPMENT NAME
            cout << "\nDo you want to update readings? (y/n): ";
            cin >> choice;

            while(choice == 'y' || choice == 'Y'){

                // FOR VALID INPUT FOR UPDATED VALUE 
                double newTemperature = getValidInput("Enter New Temperature: ");
                double newPressure = getValidInput("Enter New Pressure: ");
                double newVibration = getValidInput("Enter New Vibration: ");

                equipmentList[idx].updateReadings(newTemperature, newPressure, newVibration);

                cout << "\n===== UPDATED EQUIPMENT =====" << endl;
                equipmentList[idx].display();

                cout << "\nDo you want to update again? (y/n): ";
                cin >> choice;
            }

            // SHOW THE ALL HISTORY OF EQUIPMENT CHANGES
            char historyChoice;
            cout << "Do you want to view reading history? (y/n): ";
            cin >> historyChoice;

            if(historyChoice == 'y' || historyChoice == 'Y'){
                cout << "\n===== READING HISTORY =====" << endl;

                equipmentList[idx].displayHistory();
            }

            // SHOW THE STATUS HISTORY OF EQUIPMENT CHANGES
            char statusHistoryChoice;

            cout << "\nDo you want to view status change history? (y/n): ";
            cin >> statusHistoryChoice;

            if(statusHistoryChoice == 'y' || statusHistoryChoice == 'Y')
            {
                cout << "\n===== STATUS CHANGE HISTORY =====" << endl;
                equipmentList[idx].displayStatusHistory();
            }

            // FOR TREND ANALYSIS TO VIEW OR NOT
            char trendAnalysis;

            cout << "\nDo you want to view trend analysis? (y/n): ";
            cin >> trendAnalysis;

            if(trendAnalysis == 'y' || trendAnalysis == 'Y')
            {
                cout << "\n===== TREND ANALYSIS =====" << endl;
                equipmentList[idx].analyzeTrend();
            }

            // FOR DELETION OF EQUIPMENT IF I WANT
            char deleteChoice;

            cout << "\nDo you want to delete this equipment? (y/n): ";
            cin >> deleteChoice;

            if(deleteChoice == 'y' || deleteChoice == 'Y')
            {
                equipmentList.erase(equipmentList.begin() + idx);
                cout << "Equipment deleted successfully." << endl;
            }

            found = true;
            break;
        }
    }
    if(!found){
        cout << "Equipment is not found." << endl;
    }



    // FIND TOTAL MEASUREMENT OF ALL READINGS
    double totalTemperature = 0;
    double totalPressure    = 0;
    double totalVibration   = 0;

    // VARIABLE OF HIGHEST TEMPERATURE IN LIST AND ALSO THEIR NAME
    double highestTemperature = equipmentList[0].getTemp();
    string highestTempEquipment = equipmentList[0].getName();

    // VARIABLE OF LOWEST TEMPERATURE IN LIST AND ALSO THEIR NAME
    double lowestTemperature = equipmentList[0].getTemp();
    string lowestTempEquipment = equipmentList[0].getName();

    // OUTPUT OF ALL EQUIPMENT PRESENT IN VECTOR
    cout << "\n\n===== ALL EQUIPMENTS =====" << endl;


    for (const Equipment& equipment : equipmentList)
    {
        equipment.display();
        equipment.saveToFile();

        if(equipment.getStatus() == "NORMAL"){
            normalCount++;
        }
        else if(equipment.getStatus() == "WARNING"){
            warningCount++;
        }else{
            criticalCount++;
            criticalEquipment.push_back(equipment.getName());
        }

        // IN LOOP  HEALTH STATS
        totalTemperature += equipment.getTemp();
        totalPressure    += equipment.getPressure();
        totalVibration   += equipment.getVibration();

        // FIND HIGHEST TEMP AND NAME
        if(equipment.getTemp() > highestTemperature){
            highestTemperature = equipment.getTemp();
            highestTempEquipment = equipment.getName();
        }

        // FIND LOWEST TEMP AND NAME
        if(equipment.getTemp() < lowestTemperature){
            lowestTemperature = equipment.getTemp();
            lowestTempEquipment = equipment.getName();
        }

        cout << "----------------------" << endl;
    }


    // EQUIPMENT SUMMARY
    cout << "\n===== EQUIPMENT SUMMARY =====" << endl;

    cout << "Total Equipment: " << equipmentList.size() << endl;
    cout << "NORMAL: " << normalCount << endl;
    cout << "WARNING: " << warningCount << endl;
    cout << "CRITICAL: " << criticalCount << endl;



    // CRITICAL EQUIPMENT
    cout << "\nCritical Equipment:" << endl;

    if(criticalEquipment.empty()){
        cout << "There is no critical equipment." << endl;
    }

    for(const string &name : criticalEquipment)
    {
        cout << "- " << name << endl;
    }

    // FOR HEALTH STATISTIC
    double avgTemperature = totalTemperature / equipmentList.size();
    double avgPressure = totalPressure / equipmentList.size();
    double avgVibration = totalVibration / equipmentList.size();

    cout << "\n===== HEALTH STATISTICS =====" << endl;

    cout << "Average Temperature: " << avgTemperature << " C" << endl;
    cout << "Average Pressure: " << avgPressure << " bar" << endl;
    cout << "Average Vibration: " << avgVibration << " mm/s" << endl << endl;;

    cout  << endl << "Highest Temperature Equipment: " << highestTempEquipment << endl;
    cout << "Highest Temperature: " << highestTemperature << " C" << endl << endl;

    cout  << endl << "Lowest Temperature Equipment: " << lowestTempEquipment << endl;
    cout << "Lowest Temperature: " << lowestTemperature << " C" << endl;


    // SAVE CURRENT EQUIPMENT STATE
    saveAllToCSV(equipmentList);

    // SAVE PREVIOUS READING HISTORY
    saveHistoryToCSV(equipmentList);

    // SAVE PREVIOUS STATUS HISTORY
    saveStatusHistoryToCSV(equipmentList);

    return 0;
}