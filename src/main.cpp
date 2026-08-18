#include <iostream>
#include "Equipment.h"

using namespace std;

int main()
{
    Equipment motor("Motor-01", 70.0, 5.2, 2.5);

    motor.display();

    return 0;
}