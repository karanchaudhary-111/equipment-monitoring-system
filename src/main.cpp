#include <iostream>
#include "Equipment.h"
#include <vector>

using namespace std;

int main()
{
    vector<Equipment> equipmentList;

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

    Equipment newEquipment(name, temperature, pressure, vibration);

    equipmentList.push_back(newEquipment);

    for (const Equipment& equipment : equipmentList)
    {
        equipment.display();
        cout << "----------------------" << endl;
    }

    return 0;
}