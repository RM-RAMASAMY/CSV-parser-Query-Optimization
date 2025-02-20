#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "RecTimeStamp.h"
#include "RecPlace.h"
#include "RecPeople.h"
#include "RecVehicle.h"
#include "CrashRecord.h"

// Function to read the CSV file and return a vector of Record objects
std::vector<CrashRecord> readCSV(const std::string &filename)
{
    std::vector<CrashRecord> records;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return records;
    }

    std::string line;
    // Skip the header line if there is one
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;

        // Parse each column
        std::getline(ss, token, ',');
        string date = token;
        std::getline(ss, token, ',');
        string timeStr = token;
        TimeStamp timestamp(timeStr, date);

        std::getline(ss, token, ',');
        string Borough = token;
        std::getline(ss, token, ',');
        string ZipCode = token;
        std::getline(ss, token, ',');
        string Latitude = token;
        std::getline(ss, token, ',');
        string Longitude = token;
        std::getline(ss, token, ','); // Read the entire location string
        string Location1 = token;
        std::getline(ss, token, ','); // Read the entire location string
        string Location2 = token;
        string Location = Location1 + Location2;
        std::getline(ss, token, ',');
        string OnStName = token;
        std::getline(ss, token, ',');
        string CrStName = token;
        std::getline(ss, token, ',');
        string OffStName = token;
        Place place(Borough, OffStName, OnStName, CrStName, ZipCode, Latitude, Longitude, Location);

        // std::getline(ss, token, ',');
        // int PerInj = stoi(token);
        // std::getline(ss, token, ',');
        // int PerKil = stoi(token);
        // std::getline(ss, token, ',');
        // int PedInj = stoi(token);
        // std::getline(ss, token, ',');
        // int PedKil = stoi(token);
        // std::getline(ss, token, ',');
        // int CycInj = stoi(token);
        // std::getline(ss, token, ',');
        // int CycKil = stoi(token);
        // std::getline(ss, token, ',');
        // int MotInj = stoi(token);
        // std::getline(ss, token, ',');
        // int MotKil = stoi(token);

        int PerInj = 0, PerKil = 0, PedInj = 0, PedKil = 0, CycInj = 0, CycKil = 0, MotInj = 0, MotKil = 0;

        People people(PerInj, PerKil, PedInj, PedKil, CycInj, CycKil, MotInj, MotKil);

        vector<string> TypCde;
        std::getline(ss, token, ',');
        TypCde.push_back(token);
        std::getline(ss, token, ',');
        TypCde.push_back(token);
        std::getline(ss, token, ',');
        TypCde.push_back(token);
        std::getline(ss, token, ',');
        TypCde.push_back(token);
        std::getline(ss, token, ',');
        TypCde.push_back(token);

        std::getline(ss, token, ',');
        unsigned int ColID = stoi(token);

        vector<string> CntFct;
        std::getline(ss, token, ',');
        CntFct.push_back(token);
        std::getline(ss, token, ',');
        CntFct.push_back(token);
        std::getline(ss, token, ',');
        CntFct.push_back(token);
        std::getline(ss, token, ',');
        CntFct.push_back(token);
        std::getline(ss, token, ',');
        CntFct.push_back(token);
        Vehicle vehicle(TypCde, CntFct);

        // Create a Record object and add it to the vector
        records.emplace_back(timestamp, place, people, vehicle, ColID);
    }

    file.close();
    return records; // Return by value, utilizing move semantics
}

int main()
{
    // Path to the CSV file
    std::string filename = "../sample_slice.csv";

    // Read the CSV file into a vector of Record objects
    std::vector<CrashRecord> records = readCSV(filename);

    // Print the number of records read
    std::cout << "Number of records read: " << records.size() << std::endl;

    // Optionally, print some records to verify
    for (size_t i = 0; i < std::min(records.size(), size_t(5)); ++i)
    {
        std::cout << "Record " << i + 1 << ": {" << std::endl;
        std::cout << "Date: " << records[i].getTime().getDate() << std::endl;
        std::cout << "Time: " << records[i].getTime().gettime() << std::endl;
        std::cout << "Borough: " << records[i].getPlace().getBorough() << std::endl;
        std::cout << "Zip: " << records[i].getPlace().getZip() << std::endl;
        std::cout << "Lat: " << records[i].getPlace().getLatitude() << std::endl;
        std::cout << "Long: " << records[i].getPlace().getLongitude() << std::endl;
        std::cout << "Loc: " << records[i].getPlace().getLoc() << std::endl;
        std::cout << "Onst: " << records[i].getPlace().getOnStName() << std::endl;
        std::cout << "CrossSt: " << records[i].getPlace().getCrossStName() << std::endl;
        std::cout << "OffSt: " << records[i].getPlace().getOffStName() << std::endl;
        std::cout << "Per_2: " << records[i].getPeople().get_per_dead() << std::endl;
        std::cout << "Per_1: " << records[i].getPeople().get_per_inj() << std::endl;
        std::cout << "Ped_2: " << records[i].getPeople().get_ped_dead() << std::endl;
        std::cout << "ped_1: " << records[i].getPeople().get_ped_inj() << std::endl;
        std::cout << "Cyc_2: " << records[i].getPeople().get_cyc_dead() << std::endl;
        std::cout << "Cyc_1: " << records[i].getPeople().get_cyc_inj() << std::endl;
        std::cout << "Mot_2: " << records[i].getPeople().get_mot_dead() << std::endl;
        std::cout << "Mot_1: " << records[i].getPeople().get_mot_inj() << std::endl;
        std::cout << "V1T: " << records[i].getVehicle().getTypeCode()[0] << std::endl;
        std::cout << "V2T: " << records[i].getVehicle().getTypeCode()[1] << std::endl;
        std::cout << "V3T: " << records[i].getVehicle().getTypeCode()[2] << std::endl;
        std::cout << "V4T: " << records[i].getVehicle().getTypeCode()[3] << std::endl;
        std::cout << "V5T: " << records[i].getVehicle().getTypeCode()[4] << std::endl;
        std::cout << "CollisionId: " << records[i].getCollisionID() << std::endl;
        std::cout << "ContrFact1: " << records[i].getVehicle().getContFact()[0] << std::endl;
        std::cout << "ContrFact2: " << records[i].getVehicle().getContFact()[1] << std::endl;
        std::cout << "ContrFact3: " << records[i].getVehicle().getContFact()[2] << std::endl;
        std::cout << "ContrFact4: " << records[i].getVehicle().getContFact()[3] << std::endl;
        std::cout << "ContrFact5: " << records[i].getVehicle().getContFact()[4] << std::endl;
        std::cout << "}" << std::endl
                  << std::endl
                  << std::endl;
    }

    return 0;
}