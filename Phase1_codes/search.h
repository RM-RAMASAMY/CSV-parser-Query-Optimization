#ifndef Search_H
#define Search_H

#include <iostream>
#include <string>
#include "CrashRecord.h"

// Helper function to trim leading and trailing spaces
std::string trim(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Search for records by Borough (case-insensitive, trimmed)
void searchByBorough(const std::string &borough, vector<CrashRecord> &records)
{
    vector<CrashRecord> resultRecords;
    int recCount = 0;
    std::string searchBorough = trim(borough); // Trim for case-insensitive comparison

    for (int i = 0; i < records.size(); ++i)
    {
        if (trim(records[i].getPlace().getBorough()) == searchBorough)
        { // Compare using trimmed strings
            resultRecords.push_back(records[i]);
            recCount++;
        }
    }

    std::cout << "Total records found for borough " << borough << ": " << recCount << std::endl;
    if (recCount == 0)
    {
        std::cout << "No records found for borough: " << borough << std::endl;
    }
}

#endif // Search_H