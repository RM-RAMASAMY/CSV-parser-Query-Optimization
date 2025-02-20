#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "RecTimeStamp.h"
#include "RecPlace.h"
#include "RecPeople.h"
#include "RecVehicle.h"
#include "CrashRecord.h"

// Function to split a line by commas, but ignore commas inside parentheses
std::vector<std::string> splitLine(const std::string &line)
{
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    std::stringstream ss;

    for (char ch : line)
    {
        if (ch == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (ch == ',' && !inQuotes)
        {
            tokens.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
        else
        {
            ss << ch;
        }
    }
    tokens.push_back(ss.str());

    // Remove surrounding quotes from tokens if present
    for (std::string &token : tokens)
    {
        if (!token.empty() && token.front() == '"' && token.back() == '"')
        {
            token = token.substr(1, token.size() - 2);
        }
    }

    return tokens;
}

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
        std::vector<std::string> tokens = splitLine(line);
        if (tokens.size() < 29) // Adjust this number based on the number of columns in your CSV
        {
            std::cerr << "Invalid line: " << line << std::endl;
            continue;
        }

        // Parse each column
        std::string date = tokens[0];
        std::string timeStr = tokens[1];
        TimeStamp timestamp(timeStr, date);

        std::string Borough = tokens[2];
        std::string ZipCode = tokens[3];
        std::string Latitude = tokens[4];
        std::string Longitude = tokens[5];
        std::string Location = tokens[6];
        std::string OnStName = tokens[7];
        std::string CrStName = tokens[8];
        std::string OffStName = tokens[9];
        Place place(Borough, OffStName, OnStName, CrStName, ZipCode, Latitude, Longitude, Location);

        int PerInj = tokens[10].empty() ? 0 : std::stoi(tokens[10]);
        int PerKil = tokens[11].empty() ? 0 : std::stoi(tokens[11]);
        int PedInj = tokens[12].empty() ? 0 : std::stoi(tokens[12]);
        int PedKil = tokens[13].empty() ? 0 : std::stoi(tokens[13]);
        int CycInj = tokens[14].empty() ? 0 : std::stoi(tokens[14]);
        int CycKil = tokens[15].empty() ? 0 : std::stoi(tokens[15]);
        int MotInj = tokens[16].empty() ? 0 : std::stoi(tokens[16]);
        int MotKil = tokens[17].empty() ? 0 : std::stoi(tokens[17]);

        People people(PerInj, PerKil, PedInj, PedKil, CycInj, CycKil, MotInj, MotKil);

        std::vector<std::string> TypCde;
        TypCde.push_back(tokens[18]);
        TypCde.push_back(tokens[19]);
        TypCde.push_back(tokens[20]);
        TypCde.push_back(tokens[21]);
        TypCde.push_back(tokens[22]);

        unsigned int ColID = tokens[23].empty() ? 0 : std::stoi(tokens[23]);

        std::vector<std::string> CntFct;
        CntFct.push_back(tokens[24]);
        CntFct.push_back(tokens[25]);
        CntFct.push_back(tokens[26]);
        CntFct.push_back(tokens[27]);
        CntFct.push_back(tokens[28]);
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