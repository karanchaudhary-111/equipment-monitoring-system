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
        }

        cout << "----------------------" << endl;
    }

    cout << "\n===== EQUIPMENT SUMMARY =====" << endl;

    cout << "Total Equipment: " << equipmentList.size() << endl;
    cout << "NORMAL: " << normalCount << endl;
    cout << "WARNING: " << warningCount << endl;
    cout << "CRITICAL: " << criticalCount << endl;

    return 0;
}