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

        string tempStr;
        getline(ss, tempStr, ',');
        double temperature = stod(tempStr);

        string pressureStr;
        getline(ss, pressureStr, ',');
        double pressure = stod(pressureStr);

        string vibrationStr;
        getline(ss, vibrationStr, ',');
        double vibration = stod(vibrationStr);

        string status;
        getline(ss, status);

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

        string tempStr;
        getline(ss, tempStr, ',');
        double temperature = stod(tempStr);

        string pressureStr;
        getline(ss, pressureStr, ',');
        double pressure = stod(pressureStr);

        string vibrationStr;
        getline(ss, vibrationStr, ',');
        double vibration = stod(vibrationStr);

        string status;
        getline(ss, status);

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

// LOAD FROM CSV STATUS HISTORY
void loadStatusHistoryFromCSV(vector<Equipment>& equipmentList)
{
    ifstream file("equipment_status_history.csv");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string name;
        getline(ss, name, ',');

        string transition;
        getline(ss, transition);

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

    for(int i = 0; i < n; i++){
        if(name[i] >= 'A' && name[i] <= 'Z'){
            name[i] = name[i] - 'A' + 'a';
        }
    }

    return name;
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
                        bool hasNonSpace = false;

                        do
                        {
                            hasNonSpace = false;

                            cout << "Enter equipment name: ";
                            getline(cin, name);

                            for(int j = 0; j < name.size(); j++)
                            {
                                if(name[j] != ' ')
                                {
                                    hasNonSpace = true;
                                    break;
                                }
                            }

                            if(name.empty() || !hasNonSpace)
                            {
                                cout << "Invalid equipment name. "
                                    << "Name cannot be empty or contain only spaces."
                                    << endl;
                            }

                        } while(name.empty() || !hasNonSpace);

                        string newName = convToLower(name);

                        for(Equipment& equipment : equipmentList)
                        {
                            string existingName = convToLower(equipment.getName());

                            if(existingName == newName)
                            {
                                duplicateName = true;

                                cout << "Equipment already exists. "
                                    << "Please enter a different name."
                                    << endl << endl;

                                break;
                            }
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
            }

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

                // CONVERT SEARCH NAME TO LOWERCASE
                searchName = convToLower(searchName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(const Equipment& equipment : equipmentList)
                {
                    string existingName = convToLower(equipment.getName());

                    if(existingName == searchName)
                    {
                        cout << "\n===== SEARCH RESULT =====" << endl;

                        equipment.display();

                        found = true;
                        break;
                    }
                }

                // IF EQUIPMENT IS NOT FOUND
                if(!found)
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

                // CONVERT UPDATE NAME TO LOWERCASE
                updateName = convToLower(updateName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(Equipment& equipment : equipmentList)
                {
                    string existingName = convToLower(equipment.getName());

                    if(existingName == updateName)
                    {
                        // GET NEW READINGS
                        double newTemperature =
                            getValidInput("Enter New Temperature: ");

                        double newPressure =
                            getValidInput("Enter New Pressure: ");

                        double newVibration =
                            getValidInput("Enter New Vibration: ");

                        // UPDATE EQUIPMENT
                        equipment.updateReadings(
                            newTemperature,
                            newPressure,
                            newVibration
                        );

                        cout << "\n===== UPDATED EQUIPMENT =====" << endl;
                        equipment.display();

                        found = true;
                        break;   
                    }
                }

                // IF EQUIPMENT IS NOT FOUND
                if(!found)
                {
                    cout << "Equipment not found." << endl;
                }

                 // SAVE UPDATED DATA
                if(found)
                {
                    saveAllToCSV(equipmentList);
                    saveHistoryToCSV(equipmentList);
                    saveStatusHistoryToCSV(equipmentList);
                }

                break;
            }

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

                // CONVERT NAME TO LOWERCASE
                deleteName = convToLower(deleteName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(int idx = 0; idx < equipmentList.size(); idx++)
                {
                    string existingName =
                        convToLower(equipmentList[idx].getName());

                    if(existingName == deleteName)
                    {
                        // DELETE EQUIPMENT
                        equipmentList.erase(equipmentList.begin() + idx);

                        cout << "Equipment deleted successfully." << endl;

                        found = true;
                        break;
                    }
                }

                // EQUIPMENT NOT FOUND
                if(!found)
                {
                    cout << "Equipment not found." << endl;
                }

                // SAVE UPDATED DATA AFTER DELETION
                if(found)
                {
                    saveAllToCSV(equipmentList);
                    saveHistoryToCSV(equipmentList);
                    saveStatusHistoryToCSV(equipmentList);
                }

                break;
            }

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
            }

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

                // CONVERT SEARCH NAME TO LOWERCASE
                historyName = convToLower(historyName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(const Equipment& equipment : equipmentList)
                {
                    string existingName =
                        convToLower(equipment.getName());

                    if(existingName == historyName)
                    {
                        cout << "\n===== READING HISTORY =====" << endl;

                        equipment.displayHistory();

                        found = true;
                        break;
                    }
                }
                // EQUIPMENT NOT FOUND
                if(!found)
                {
                    cout << "Equipment not found." << endl;
                }

                break;
            }

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

                // CONVERT SEARCH NAME TO LOWERCASE
                statusHistoryName = convToLower(statusHistoryName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(const Equipment& equipment : equipmentList)
                {
                    string existingName =
                        convToLower(equipment.getName());

                    if(existingName == statusHistoryName)
                    {
                        cout << "\n===== STATUS CHANGE HISTORY =====" << endl;

                        equipment.displayStatusHistory();

                        found = true;
                        break;
                    }
                }

                // EQUIPMENT NOT FOUND
                if(!found)
                {
                    cout << "Equipment not found." << endl;
                }
                break;
            }

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

                // CONVERT SEARCH NAME TO LOWERCASE
                trendName = convToLower(trendName);

                bool found = false;

                // SEARCH EQUIPMENT
                for(const Equipment& equipment : equipmentList)
                {
                    string existingName =
                        convToLower(equipment.getName());

                    if(existingName == trendName)
                    {
                        cout << "\n===== TREND ANALYSIS =====" << endl;

                        equipment.analyzeTrend();

                        found = true;
                        break;
                    }
                }

                // EQUIPMENT NOT FOUND
                if(!found)
                {
                    cout << "Equipment not found." << endl;
                }
                break;
            }

            case 10:
                cout << "\nExiting Program..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while(choice != 10);

    return 0;
}