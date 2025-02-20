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

// separate function to display the records
void displayRec(vector<CrashRecord> records)
{
    for (size_t i = 0; i < records.size(); ++i)
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
}

#endif // RECORD_H