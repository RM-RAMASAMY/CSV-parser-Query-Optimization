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
    unsigned int getBoroughCount(string &searchBorough)
    {
        unsigned int recCount = 0;
        int I = omp_get_num_threads();
#pragma omp target teams distribute parallel for default(none) shared(I)
        for (size_t i = 0; i < places.size(); ++i)
        {
            if (trim(places[i].getBorough()) == trim(searchBorough))
            {
#pragma omp critical
                {
                    recCount++;
                }
            }
        }
        return recCount;
    }
};

#endif // RECORD_H