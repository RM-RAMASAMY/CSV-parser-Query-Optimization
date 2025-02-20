#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <vector>
#include <string>
#include "RecTimeStamp.h"
#include "RecPlace.h"
#include "RecPeople.h"
#include "RecVehicle.h"

using namespace std;

class CrashRecord
{
private:
    TimeStamp t1;
    Place place;
    People people;
    Vehicle vehicle;
    unsigned int CollisionID;

public:
    CrashRecord()
    {
        CollisionID = 0;
    }
    CrashRecord(TimeStamp t, Place place, People people, Vehicle vehicle, unsigned int CollisionID)
    {
        this->t1 = t;
        this->place = place;
        this->people = people;
        this->vehicle = vehicle;
        this->CollisionID = CollisionID;
    }
    TimeStamp getTime() { return t1; }
    Place getPlace() { return place; }
    People getPeople() { return people; }
    Vehicle getVehicle() { return vehicle; }
    unsigned int getCollisionID() { return CollisionID; }
};

#endif // RECORD_H