#include <iostream>
#include "Equipment.h"
#include <vector>

using namespace std;

int main()
{
    vector<Equipment> equipmentList;

    equipmentList.push_back(
        Equipment("Motor-01", 70.0, 5.2, 2.5, "NORMAL")
    );

    equipmentList.push_back(
        Equipment("Pump-01", 82.0, 6.1, 4.2, "WARNING")
    );

    for (Equipment equipment : equipmentList)
    {
        equipment.display();
        cout << "----------------------" << endl;
    }

    return 0;
}