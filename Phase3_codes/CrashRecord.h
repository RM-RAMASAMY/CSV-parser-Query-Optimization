#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <vector>
#include <string>
#include "RecTimeStamp.h"
#include "RecPlace.h"
#include "RecPeople.h"
#include "RecVehicle.h"
#include <omp.h>

using namespace std;

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

struct threadlocalcrashrecord
{
    TimeStamp times;
    Place places;
    People peoples;
    Vehicle vehicles;
    unsigned int collisionIDs;
};

class CrashRecord
{
private:
    vector<TimeStamp> times;
    vector<Place> places;
    vector<People> peoples;
    vector<Vehicle> vehicles;
    vector<unsigned int> collisionIDs;

public:
    int count = 0;
    CrashRecord()
    {
        collisionIDs.push_back(0);
    }
    void addCrashRecord(TimeStamp t, Place place, People people, Vehicle vehicle, unsigned int CollisionID)
    {
        times.push_back(t);
        places.push_back(place);
        peoples.push_back(people);
        vehicles.push_back(vehicle);
        collisionIDs.push_back(CollisionID);
        count++;
    }

    // function to print the distinct values of each vector upto 5 values

    unsigned int getBoroughCount(string &borough)
    {
        unsigned int recCount = 0;
        std::string searchBorough = trim(borough); // Trim for case-insensitive comparison
        int num_threads = omp_get_max_threads();   // Specify the number of threads you want to use

        omp_set_num_threads(num_threads); // Set the number of threads
#pragma omp parallel
        {
            unsigned int local_recCount = 0;

#pragma omp for nowait
            for (size_t i = 0; i < places.size(); ++i)
            {
                if (trim(places[i].getBorough()) == searchBorough)
                { // Compare using trimmed strings
                    local_recCount++;
                }
            }

            std::cout << local_recCount << " ";

#pragma omp critical
            {
                recCount += local_recCount; // Safely update global recCount
            }
        }

        std::cout << "Total records found for borough " << searchBorough << ": " << recCount << std::endl;
        if (recCount == 0)
        {
            std::cout << "No records found for borough: " << searchBorough << std::endl;
        }
        return recCount;
    }
};

#endif // RECORD_H