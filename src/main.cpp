#include <iostream>
#include "Equipment.h"
#include <vector>
# include <limits>

using namespace std;

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

int main()
{
    vector<Equipment> equipmentList;

    int normalCount  = 0;
    int warningCount = 0;
    int criticalCount   = 0;

    // FOR HOW MUCH EQUIPMENT YOU WANT
    int n;
    cout << "Enter number of equipments: ";
    cin >> n;
    
    if(n <= 0){
        cout << "Number of Equipment should be greater than 0," << endl;
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

    for(Equipment & equipment : equipmentList){

        string equipmentName = equipment.getName();

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
            equipment.display();

            char choice;

            // UPDATE NEW READING OF EQUIPMENT NAME
            cout << "\nDo you want to update readings? (y/n): ";
            cin >> choice;

            while(choice == 'y' || choice == 'Y'){

                // FOR VALID INPUT FOR UPDATED VALUE 
                double newTemperature = getValidInput("Enter New Temperature: ");
                double newPressure = getValidInput("Enter New Pressure: ");
                double newVibration = getValidInput("Enter New Vibration: ");

                equipment.updateReadings(newTemperature, newPressure, newVibration);

                cout << "\n===== UPDATED EQUIPMENT =====" << endl;
                equipment.display();

                cout << "\nDo you want to update again? (y/n): ";
                cin >> choice;
            }

            // SHOW THE ALL HISTORY OF EQUIPMENT CHANGES
            char historyChoice;
            cout << "Do you want to view reading history? (y/n): ";
            cin >> historyChoice;

            if(historyChoice == 'y' || historyChoice == 'Y'){
                cout << "\n===== READING HISTORY =====" << endl;

                equipment.displayHistory();
            }

            char statusHistoryChoice;

            cout << "\nDo you want to view status change history? (y/n): ";
            cin >> statusHistoryChoice;

            if(statusHistoryChoice == 'y' || statusHistoryChoice == 'Y')
            {
                cout << "\n===== STATUS CHANGE HISTORY =====" << endl;
                equipment.displayStatusHistory();
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


    return 0;
}