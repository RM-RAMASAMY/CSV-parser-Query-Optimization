#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cctype>

#define MAX_RECORDS 100000 // Set the size for 100,000 records

class CrashRecord
{
public:
    std::string crashDate;
    std::string crashTime;
    std::string borough;
    int zipCode;
    double latitude;
    double longitude;

    // Default constructor (initializes with default values)
    CrashRecord()
        : crashDate(""), crashTime(""), borough(""), zipCode(0), latitude(0.0), longitude(0.0) {}

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

// Helper function to trim leading and trailing spaces
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Helper function to clean up coordinates, removing any unwanted characters
std::string cleanCoordinate(std::string &coordinate)
{
    coordinate.erase(remove(coordinate.begin(), coordinate.end(), '('), coordinate.end());
    coordinate.erase(remove(coordinate.begin(), coordinate.end(), ')'), coordinate.end());
    return coordinate;
}

// Function to parse a chunk of the CSV and convert it into an array of CrashRecord objects
int parseCSVChunk(const std::string &filePath, CrashRecord records[MAX_RECORDS], int startLine, int maxRecordsToRead)
{
    int recordCount = 0;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return recordCount;
    }

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line) && recordCount < maxRecordsToRead)
    {
        lineCount++;
        if (lineCount <= startLine)
            continue; // Skip lines before the start line

        std::stringstream ss(line);
        std::string crashDate, crashTime, borough, key, value;
        int zipCode = 0;
        double latitude = 0.0, longitude = 0.0;

        // Check if the line has sufficient fields (5 columns minimum: crashDate, crashTime, borough, latitude, longitude)
        if (std::count(line.begin(), line.end(), ',') < 4)
        {
            continue; // Skip invalid lines
        }

        // Parse the comma-separated line
        std::getline(ss, crashDate, ',');
        std::getline(ss, crashTime, ',');
        std::getline(ss, borough, ',');

        // Skip record if borough is null or empty
        if (borough.empty())
            continue;

        // Parse the zip code field
        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        if (!value.empty())
        {
            try
            {
                zipCode = std::stoi(value); // Convert string to int (ZIP CODE)
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid zip code: " << value << std::endl;
            }
        }

        // Parse the latitude field
        std::getline(ss, value, ',');
        if (!value.empty())
        {
            try
            {
                latitude = std::stod(value); // Convert string to double (LATITUDE)
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid latitude: " << value << std::endl;
            }
        }

        // Parse the longitude field
        std::getline(ss, value, ',');
        if (!value.empty())
        {
            try
            {
                longitude = std::stod(value); // Convert string to double (LONGITUDE)
            }
            catch (const std::invalid_argument &e)
            {
                // Clean and parse the longitude if it has parentheses
                value = cleanCoordinate(value);
                try
                {
                    longitude = std::stod(value); // Reattempt conversion after cleaning
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Invalid longitude: " << value << std::endl;
                }
            }
        }

        // Debugging print to verify the data being parsed
        std::cout << "Borough: " << borough << ", Latitude: " << latitude << ", Longitude: " << longitude << std::endl;

        // Ensure that we are within bounds before adding a new record
        if (recordCount < maxRecordsToRead)
        {
            records[recordCount++] = CrashRecord(crashDate, crashTime, borough, zipCode, latitude, longitude);
        }
    }

    file.close();
    return recordCount; // Return the number of records read
}

// Search for records by Borough (case-insensitive, trimmed)
void searchByBorough(const std::string &borough, CrashRecord records[], int recordCount)
{
    bool found = false;
    int manhattanCount = 0;
    std::string searchBorough = trim(borough); // Trim for case-insensitive comparison

    for (int i = 0; i < recordCount; ++i)
    {
        if (trim(records[i].borough) == searchBorough)
        { // Compare using trimmed strings
            records[i].displayRecord();
            manhattanCount++;
        }
    }

    std::cout << "Total records found for borough " << borough << ": " << manhattanCount << std::endl;
    if (!found)
    {
        std::cout << "No records found for borough: " << borough << std::endl;
    }
}

int main()
{
    CrashRecord records[MAX_RECORDS];                                                   // Array of CrashRecord objects
    std::string filePath = "/Users/shruthishetti/Desktop/Mini-1/MotorVehicleCrash.csv"; // Set your actual file path here

    int recordCount = 0;
    int startLine = 1; // Assuming first line is header

    // Process chunks
    for (int chunk = 0; chunk < 22; ++chunk)
    { // Total of 2150478 records, divided into 22 chunks of 100,000 each
        int chunkSize = (chunk == 21) ? 50478 : MAX_RECORDS;
        recordCount += parseCSVChunk(filePath, records, startLine, chunkSize);
        startLine += chunkSize;
        std::cout << "Processed " << chunkSize << " records in this chunk." << chunk << "---------------------------" << std::endl;
    }

    std::cout << "Total records read: " << recordCount << std::endl;

    // Search for "MANHATTAN" in the processed records
    searchByBorough("MANHATTAN", records, recordCount);

    return 0;
}