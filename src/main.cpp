#include <iostream>
#include "Equipment.h"
#include <vector>

using namespace std;

int main()
{
    vector<Equipment> equipmentList;

    equipmentList.push_back(
        Equipment("Motor-01", 70.0, 5.2, 2.5)
    );

    equipmentList.push_back(
        Equipment("Pump-01", 82.0, 6.1, 4.2)
    );

    equipmentList.push_back(
        Equipment("Compressor-01", 110.0, 7.0, 4.0)
    );

    for (Equipment equipment : equipmentList)
    {
        equipment.display();
        cout << "----------------------" << endl;
    }

    return 0;
}