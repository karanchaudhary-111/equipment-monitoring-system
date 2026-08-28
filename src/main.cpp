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

    int n;
    cout << "Enter nummber of equipment: ";
    cin >> n;
    cin.ignore();

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

    // search a equipment name through directly searching
    string searchName;

    cout << "\nEnter equipment name to search: ";
    getline(cin, searchName);

    bool  found = false;

    for(const Equipment & equipment : equipmentList){
        if(equipment.getName() == searchName){

            cout << "\n===== SEARCH RESULT =====" << endl;
            equipment.display();

            found = true;
            break;
        }
    }
    if(!found){
        cout << "Equipment is not found." << endl;
    }

    return 0;
}