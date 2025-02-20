#ifndef RecVehicle_H
#define RecVehicle_H

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Vehicle
{
private:
    string typeCode[5];
    string ContFact[5];

public:
    Vehicle()
    {
        for (int i = 0; i < 5; i++)
        {
            typeCode[i] = "";
            ContFact[i] = "";
        }
    }
    Vehicle(const vector<string> &typeCode, const vector<string> &ContFact)
    {
        for (int i = 0; i < 5; i++)
        {
            this->typeCode[i] = typeCode[i];
            this->ContFact[i] = ContFact[i];
        }
    }
    string *getTypeCode() { return typeCode; }
    string *getContFact() { return ContFact; }
};
#endif // RecVehicle_H