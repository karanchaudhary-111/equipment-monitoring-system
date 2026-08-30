#include <iostream>
#include "Equipment.h"
#include <vector>

using namespace std;

int main()
{
    vector<Equipment> equipmentList;

    int normalCount  = 0;
    int warningCount = 0;
    int criticalCount   = 0;

    // for number of equipments
    int n;
    cout << "Enter number of equipments: ";
    cin >> n;
    
    if(n <= 0){
        cout << "Number of Equipment is greater than 0," << endl;
        return 0;
    }
    cin.ignore();

    // user input
    for(int i = 0; i < n; i++){

        cout << "\nEnter details for Equipment " << i + 1 << endl;

        string name;
        cout << "Enter equipment name: ";
        getline(cin, name);

        double temperature;
        cout << "Enter temperature: ";
        cin >> temperature;

        double pressure;
        cout << "Enter pressure: ";
        cin >> pressure;

        double vibration;
        cout << "Enter vibration: ";
        cin >> vibration;

        cin.ignore();

        Equipment newEquipment(name, temperature, pressure, vibration);

        equipmentList.push_back(newEquipment);
    }
    cout << endl << endl;

    vector<string> criticalEquipment;

    // search a equipment name through directly searching
    string searchName;

    cout << "\nEnter equipment name to search: ";
    getline(cin, searchName);

    bool  found = false;

    for(Equipment & equipment : equipmentList){
        if(equipment.getName() == searchName){

            cout << "\n===== SEARCH RESULT =====" << endl;
            equipment.display();

            char choice;

            cout << "\nDo you want to update readings? (y/n): ";
            cin >> choice;

            if(choice == 'y' || choice == 'Y'){
                double newTemperature;
                double newPressure;
                double newVibration;

                cout << "Enter new temperature: ";
                cin >> newTemperature;

                cout << "Enter new pressure: ";
                cin >> newPressure;

                cout << "Enter new vibration: ";
                cin >> newVibration;

                equipment.updateReadings(newTemperature, newPressure, newVibration);

                cout << "\n===== UPDATED EQUIPMENT =====" << endl;
                equipment.display();
                
                cout << "\n===== READING HISTORY =====" << endl;
                equipment.displayHistory();
            }

            found = true;
            break;
        }
    }
    if(!found){
        cout << "Equipment is not found." << endl;
    }

    // find total measurement of temp, pressure and vibration
    double totalTemperature = 0;
    double totalPressure    = 0;
    double totalVibration   = 0;

    // find highest temperature and their names
    double highestTemperature = equipmentList[0].getTemp();
    string highestTempEquipment = equipmentList[0].getName();

    // find lowest temperature and their names
    double lowestTemperature = equipmentList[0].getTemp();
    string lowestTempEquipment = equipmentList[0].getName();

    // for all equipment output
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

        // In loop health statistic
        totalTemperature += equipment.getTemp();
        totalPressure    += equipment.getPressure();
        totalVibration   += equipment.getVibration();

        // for highest
        if(equipment.getTemp() > highestTemperature){
            highestTemperature = equipment.getTemp();
            highestTempEquipment = equipment.getName();
        }

        // for lowest
        if(equipment.getTemp() < lowestTemperature){
            lowestTemperature = equipment.getTemp();
            lowestTempEquipment = equipment.getName();
        }

        cout << "----------------------" << endl;
    }


    // equipment summary 
    cout << "\n===== EQUIPMENT SUMMARY =====" << endl;

    cout << "Total Equipment: " << equipmentList.size() << endl;
    cout << "NORMAL: " << normalCount << endl;
    cout << "WARNING: " << warningCount << endl;
    cout << "CRITICAL: " << criticalCount << endl;



    // critical equipment 
    cout << "\nCritical Equipment:" << endl;

    if(criticalEquipment.empty()){
        cout << "There is no critical equipment." << endl;
    }

    for(const string &name : criticalEquipment)
    {
        cout << "- " << name << endl;
    }

    // for health statistics
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