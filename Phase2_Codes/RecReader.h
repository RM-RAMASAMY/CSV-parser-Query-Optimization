#ifndef RecReader_H
#define RecReader_H

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
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

#pragma omp parallel for num_threads(12)
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = splitLine(line);
        if (tokens.size() < 29) // Adjust this number based on the number of columns in your CSV
        {
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
#pragma omp critical
        {
            records.emplace_back(timestamp, place, people, vehicle, ColID);
        }
    }

    file.close();
    return records; // Return by value, utilizing move semantics
}

#endif // RecReader_H