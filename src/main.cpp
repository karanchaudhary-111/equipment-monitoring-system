#include <iostream>
#include "Equipment.h"
#include <vector>

using namespace std;

int main()
{
    vector<Equipment> equipmentList;

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

    for (const Equipment& equipment : equipmentList)
    {
        equipment.display();
        equipment.saveToFile();
        cout << "----------------------" << endl;
    }

    return 0;
}