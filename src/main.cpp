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

// INPUT NAME IS VALID OR NOT
bool isValidEquipmentName(string name)
{
    for(int i = 0; i < name.size(); i++)
    {
        if(name[i] != ' ')
        {
            return true;
        }
    }

    return false;
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

        if(!isValidEquipmentName(name))
        {
            cout << "Invalid equipment name in CSV. Skipping row." << endl;
            continue;
        }

        string tempStr;
        getline(ss, tempStr, ',');

        string pressureStr;
        getline(ss, pressureStr, ',');

        string vibrationStr;
        getline(ss, vibrationStr, ',');

        double temperature;
        double pressure;
        double vibration;

        try
        {
            temperature = stod(tempStr);
            pressure = stod(pressureStr);
            vibration = stod(vibrationStr);
        }
        catch(...)
        {
            cout << "Invalid numeric data in CSV. Skipping row." << endl;
            continue;
        }

        string status;
        if(!getline(ss, status))
        {
            cout << "Missing data in CSV. Skipping row." << endl;
            continue;
        }

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

        if(!isValidEquipmentName(name))
        {
            cout << "Invalid equipment name in history CSV. Skipping row." << endl;
            continue;
        }

        string tempStr;
        getline(ss, tempStr, ',');

        string pressureStr;
        getline(ss, pressureStr, ',');

        string vibrationStr;
        getline(ss, vibrationStr, ',');

        double temperature;
        double pressure;
        double vibration;

        try
        {
            temperature = stod(tempStr);
            pressure = stod(pressureStr);
            vibration = stod(vibrationStr);
        }
        catch(...)
        {
            cout << "Invalid numeric data in history CSV. Skipping row." << endl;
            continue;
        }

        string status;
        
        if(!getline(ss, status))
        {
            cout << "Missing data in history CSV. Skipping row." << endl;
            continue;
        }

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

// LOAD STATUS HISTORY FROM CSV 
void loadStatusHistoryFromCSV(vector<Equipment>& equipmentList)
{
    ifstream file("equipment_status_history.csv");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string name;
        getline(ss, name, ',');

        if(!isValidEquipmentName(name))
        {
            cout << "Invalid equipment name in status history CSV. Skipping row." << endl;
            continue;
        }

        string transition;

        if(!getline(ss, transition))
        {
            cout << "Missing transition in Status History CSV. Skipping row." << endl;
            continue;
        }

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


// CONVERT THE EQUIPMENT NAME IN LOWERCASE
string convToLower(string name){
    int n = name.size();

    for(int i = 0; i < n; i++)
    {
        if(name[i] >= 'A' && name[i] <= 'Z')
        {
            name[i] = name[i] - 'A' + 'a';
        }
    }

    return name;
}

// Returns the index of the equipment by name (case-insensitive), or -1 if not found.
int findEquipment(vector<Equipment>& equipmentList, string name)
{
    for(int i = 0; i < equipmentList.size(); i++)
    {
        string existingName = equipmentList[i].getName();

        if(convToLower(name) == convToLower(existingName))
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    vector<Equipment> equipmentList;

    loadFromCSV(equipmentList);
    loadHistoryFromCSV(equipmentList);
    loadStatusHistoryFromCSV(equipmentList);

    // SELECT THE CHOICE 
    int choice;

    // ===== MAIN MENU STARTS HERE =====
    do
    {
        cout << "\n===== INDUSTRIAL EQUIPMENT MONITORING SYSTEM =====" << endl;
        cout << "1. Add Equipment" << endl;
        cout << "2. Display All Equipment" << endl;
        cout << "3. Search Equipment" << endl;
        cout << "4. Update Equipment" << endl;
        cout << "5. Delete Equipment" << endl;
        cout << "6. Show Summary Dashboard" << endl;
        cout << "7. Show Reading History" << endl;
        cout << "8. Show Status Change History" << endl;
        cout << "9. Show Trend Analysis" << endl;
        cout << "10. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number from 1 to 10." << endl;
            continue;
        }

        if(choice < 1 || choice > 10)
        {
            cout << "Invalid choice. Please enter a number from 1 to 10." << endl;
            continue;
        }

        switch(choice)
        {
            case 1: // ==== ADD EQUIPMENT CODE HERE ====
            {

                int n;

                cout << "Enter number of equipments: ";
                cin >> n;

                // CHECK NUMBER OF EQUIPMENTS
                if(n < 0)
                {
                    cout << "Number of Equipment cannot be negative." << endl;
                    break;
                }

                if(n == 0)
                {
                    cout << "No equipment added. Please select another option." << endl;
                    break;
                }

                cin.ignore();

                for(int i = 0; i < n; i++)
                {
                    cout << "\nEnter details for Equipment " << i + 1 << endl;

                    string name;
                    bool duplicateName = false;

                    // CHECK DUPLICATE TILL UNIQUE NAME
                    do
                    {
                        duplicateName = false;

                        // REMOVE INVALID NAME LIKE SPACE AND EMPTY NAME
                        do
                        {
                            cout << "Enter equipment name: ";
                            getline(cin, name);

                            if(!isValidEquipmentName(name))
                            {
                                cout << "Invalid equipment name. "
                                    << "Name cannot be empty or contain only spaces."
                                    << endl;
                            }

                        } while(!isValidEquipmentName(name));

                        // CHECK IF EQUIPMENT NAME ALREADY EXISTS
                        int index = findEquipment(equipmentList, name);

                        if(index != -1)
                        {
                            duplicateName = true;

                            cout << "Equipment already exists. "
                                << "Please enter a different name."
                                << endl << endl;
                        }

                    } while(duplicateName);

                    // USING FUNCTION FOR VALID INPUT
                    double temperature =
                        getValidInput("Enter temperature: ");

                    double pressure =
                        getValidInput("Enter pressure: ");

                    double vibration =
                        getValidInput("Enter vibration: ");

                    cin.ignore();

                    // CREATE NEW EQUIPMENT
                    Equipment newEquipment(
                        name,
                        temperature,
                        pressure,
                        vibration
                    );

                    equipmentList.push_back(newEquipment);
                }

                // SAVE UPDATED EQUIPMENT LIST
                saveAllToCSV(equipmentList);

                cout << "Equipment added successfully." << endl;

                break;
            }// CASE 1 IS COMPLETED

            case 2: // ==== DISPLAY ALL EQUIPMENT ====
            {
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                for(const Equipment& equipment : equipmentList)
                {
                    equipment.display();
                    cout << "----------------------" << endl;
                }

                break;
            }// CASE 2 IS COMPLETED

            case 3: // ==== SEARCH EQUIPMENT ====
            {

                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                string searchName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to search: ";
                getline(cin, searchName);

                int index = findEquipment(equipmentList, searchName);

                if(index != -1)
                {
                    cout << "\n===== SEARCH RESULT =====" << endl;
                    equipmentList[index].display();
                }
                else
                {
                    cout << "Equipment not found." << endl;
                }

                break;
            }// CASE 3 IS COMPLETED

            case 4: // ==== UPDATE EQUIPMENT ====
            {
                
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                string updateName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to search: ";
                getline(cin, updateName);

                // FIND THE EQUIPMENT AND GET ITS INDEX
                int index = findEquipment(equipmentList, updateName);

                // IF EQUIPMENT IS NOT FOUND
                if(index == -1)
                {
                    cout << "Equipment not found." << endl;
                    break;
                }

                // TAKE NEW READINGS
                double newTemperature =
                    getValidInput("Enter New Temperature: ");

                double newPressure =
                    getValidInput("Enter New Pressure: ");

                double newVibration =
                    getValidInput("Enter New Vibration: ");

                // UPDATED READINGS OF THE SELECTED EQUIPMENT
                equipmentList[index].updateReadings(
                    newTemperature,
                    newPressure,
                    newVibration
                );

                // DISPLAY UPDATED EQUIPMENT
                cout << "\n===== UPDATED EQUIPMENT =====" << endl;
                equipmentList[index].display();

                // SAVE UPDATED DATA AND HISTORY
                saveAllToCSV(equipmentList);
                saveHistoryToCSV(equipmentList);
                saveStatusHistoryToCSV(equipmentList);

                break;
            }// CASE 4 IS COMPLETED

            case 5: // ==== DELETE EQUIPMENT ====
            {
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                string deleteName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to delete: ";
                getline(cin, deleteName);

                // FIND THE EQUIPMENT AND GET ITS INDEX
                int index = findEquipment(equipmentList, deleteName);

                // IF EQUIPMENT IS NOT FOUND
                if(index == -1)
                {
                    cout << "Equipment not found." << endl;
                    break;
                }

                char confirm;

                do
                {
                    cout << "Are you sure you want to delete this equipment? (y/n): ";
                    cin >> confirm;

                    // INVALID INPUT CHECK FOR CONFIRM
                    if(confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N')
                    {
                        cout << "Invalid choice. Please enter y or n." << endl;
                    }

                } while(confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N' );

                // DELETE EQUIPMENT IF USER CONFIRMS
                if(confirm == 'y' || confirm == 'Y')
                {
                    // DELETE EQUIPMENT FROM VECTOR
                    equipmentList.erase(equipmentList.begin() + index);
                    cout << "Equipment deleted successfully." << endl;

                    // Save remaining equipment and histories
                    saveAllToCSV(equipmentList);
                    saveHistoryToCSV(equipmentList);
                    saveStatusHistoryToCSV(equipmentList);

                }else // CANCEL DELETION IF USER SELECTS NO
                {
                    cout << "Deletion cancelled." << endl;
                }

                break;

            }// CASE 5 IS COMPLETED

            case 6: // ==== SHOW SUMMARY DASHBOARD ====
            {
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                // TO COUNT THE STATUS
                int normalCount     = 0;
                int warningCount    = 0;
                int criticalCount   = 0;

                vector<string> criticalEquipment;

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

                // CALCULATE SUMMARY DATA
                for (const Equipment& equipment : equipmentList)
                {
                    // COUNT STATUS
                    if(equipment.getStatus() == "NORMAL"){
                        normalCount++;
                    }
                    else if(equipment.getStatus() == "WARNING"){
                        warningCount++;
                    }else{
                        criticalCount++;
                        criticalEquipment.push_back(equipment.getName());
                    }

                    //  TOTAL READINGS
                    totalTemperature += equipment.getTemp();
                    totalPressure    += equipment.getPressure();
                    totalVibration   += equipment.getVibration();

                    // FIND HIGHEST TEMP AND THEIR NAME
                    if(equipment.getTemp() > highestTemperature){
                        highestTemperature = equipment.getTemp();
                        highestTempEquipment = equipment.getName();
                    }

                    // FIND LOWEST TEMP AND THEIR NAME
                    if(equipment.getTemp() < lowestTemperature){
                        lowestTemperature = equipment.getTemp();
                        lowestTempEquipment = equipment.getName();
                    }
                }

                // CALCULATE AVERAGES

                double avgTemperature = totalTemperature / equipmentList.size();
                double avgPressure = totalPressure / equipmentList.size();
                double avgVibration = totalVibration / equipmentList.size();

                // PRINT THE SUMMARY DASHBOARD
                cout << "\n===== SUMMARY DASHBOARD =====" << endl;

                cout << "Total Equipments: " << equipmentList.size() << endl;
                cout << "Normal: " << normalCount << endl;
                cout << "Warning: " << warningCount << endl;
                cout << "Critical: " << criticalCount << endl;

                cout << "\nAverage Temperature: " << avgTemperature << " C" << endl;
                cout << "Average Pressure: " << avgPressure << " bar" << endl;
                cout << "Average Vibration: " << avgVibration << " mm/s" << endl;

                cout << "\nHighest Temperature: "
                    << highestTemperature << " C"
                    << " (" << highestTempEquipment << ")" << endl;

                cout << "Lowest Temperature: "
                    << lowestTemperature << " C"
                    << " (" << lowestTempEquipment << ")" << endl;

                 // DISPLAY CRITICAL EQUIPMENT
                if(criticalEquipment.empty())
                {
                    cout << "\nNo critical equipment." << endl;
                }
                else
                {
                    cout << "\nCritical Equipments:" << endl;

                    for(const string& name : criticalEquipment)
                    {
                        cout << name << endl;
                    }
                }

                break;
            }// CASE 6 IS COMPLETED

            case 7: // ==== SHOW READING HISTORY ====
            {
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                string historyName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to view reading history: ";
                getline(cin, historyName);

                // FIND THE EQUIPMENT AND GET ITS INDEX
                int index = findEquipment(equipmentList, historyName);

                // IF EQUIPMENT IS NOT FOUND
                if(index == -1)
                {
                    cout << "Equipment not found." << endl;
                    break;
                }

                // DISPLAY READING HISTORY OF SELECTED EQUIPMENT
                cout << "\n===== READING HISTORY =====" << endl;
                equipmentList[index].displayHistory();

                break;
            }// CASE 7 IS COMPLETED

            case 8: // ==== SHOW  STATUS CHANGE HISTORY ====
            {
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo equipment available." << endl;
                    break;
                }

                string statusHistoryName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to view status change history: ";
                getline(cin, statusHistoryName);

                // FIND THE EQUIPMENT AND GET ITS INDEX
                int index = findEquipment(equipmentList, statusHistoryName);

                // IF EQUIPMENT IS NOT FOUND
                if(index == -1)
                {
                    cout << "Equipment not found." << endl;
                    break;
                }

                // DISPLAY STATUS CHANGE HISTORY OF SELECTED EQUIPMENT
                cout << "\n===== STATUS CHANGE HISTORY =====" << endl;
                equipmentList[index].displayStatusHistory();
                break;
            }// CASE 8 IS COMPLETED

            case 9: // ==== SHOW TREND ANALYSIS ====
            {
                // CHECK IF EQUIPMENT LIST IS EMPTY
                if(equipmentList.empty())
                {
                    cout << "\nNo Equipment available." << endl;
                    break;
                }

                string trendName;

                // REMOVE LEFTOVER NEWLINE
                cin.ignore();

                cout << "Enter equipment name to view trend analysis: ";
                getline(cin, trendName);

                 // FIND THE EQUIPMENT AND GET ITS INDEX
                int index = findEquipment(equipmentList, trendName);

                // CHECK IF EQUIPMENT IS NOT FOUND
                if(index == -1)
                {
                    cout << "Equipment not found." << endl;
                    break;
                }

                // DISPLAY TREND ANALYSIS OF SELECTED EQUIPMENT
                cout << "\n===== TREND ANALYSIS =====" << endl;
                equipmentList[index].analyzeTrend();
                break;
            }// CASE 9 IS COMPLETED

            case 10:
                cout << "\nExiting Program..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while(choice != 10);

    return 0;
}