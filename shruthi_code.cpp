#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#define MAX_RECORDS 2200 // Set the size for the 2.15 million records

class CrashRecord
{
public:
    std::string crashDate;
    std::string crashTime;
    std::string borough;
    int zipCode;
    double latitude;
    double longitude;

    CrashRecord()
    {
        crashDate = "";
        crashTime = "";
        borough = "";
        zipCode = 0;
        latitude = 0.0;
        longitude = 0.0;
    }

    // Constructor to initialize the class with data
    CrashRecord(const std::string &crashDate, const std::string &crashTime, const std::string &borough,
                int zipCode, double latitude, double longitude)
        : crashDate(crashDate), crashTime(crashTime), borough(borough), zipCode(zipCode),
          latitude(latitude), longitude(longitude) {}

    // Display the record (for debugging purposes)
    void displayRecord() const
    {
        std::cout << "Crash Date: " << crashDate << "\n"
                  << "Crash Time: " << crashTime << "\n"
                  << "Borough: " << borough << "\n"
                  << "Zip Code: " << zipCode << "\n"
                  << "Latitude: " << latitude << "\n"
                  << "Longitude: " << longitude << "\n";
    }
};

// Function to parse the CSV and convert it into an array of CrashRecord objects
int parseCSV(const std::string &filePath, CrashRecord records[MAX_RECORDS])
{
    int recordCount = 0;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return recordCount;
    }

    std::string line;
    while (std::getline(file, line) && recordCount < MAX_RECORDS)
    {
        std::stringstream ss(line);
        std::string key, value;
        std::string crashDate, crashTime, borough;
        int zipCode = 0;
        double latitude = 0.0, longitude = 0.0;

        // Read the first line (key-value pairs)
        while (std::getline(ss, key, '\t') && std::getline(ss, value, '\t'))
        {
            // Convert values to appropriate data types
            if (key == "CRASH DATE")
            {
                crashDate = value;
            }
            else if (key == "CRASH TIME")
            {
                crashTime = value;
            }
            else if (key == "BOROUGH")
            {
                borough = value;
            }
            else if (key == "ZIP CODE")
            {
                zipCode = std::stoi(value); // Convert string to int
            }
            else if (key == "LATITUDE")
            {
                latitude = std::stod(value); // Convert string to double
            }
            else if (key == "LONGITUDE")
            {
                longitude = std::stod(value); // Convert string to double
            }
        }

        // Create a new CrashRecord and add it to the array
        records[recordCount++] = CrashRecord(crashDate, crashTime, borough, zipCode, latitude, longitude);
    }

    file.close();
    return recordCount; // Return the number of records read
}

int main()
{
    CrashRecord records[MAX_RECORDS];           // Array of CrashRecord objects
    std::string filePath = "Motor_Vehicle.csv"; // Set your actual file path here
    int recordCount = parseCSV(filePath, records);

    // Display the first 5 records (for testing purposes)
    for (int i = 0; i < 5 && i < recordCount; ++i)
    {
        records[i].displayRecord();
    }

    return 0;
}