#ifndef RecPlace_H
#define RecPlace_H

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "CrashRecord.h"

using namespace std;

vector<CrashRecord> &parse()
{
    std::ifstream file("../Motor_Vehicle.csv");

    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        static std::vector<CrashRecord> empty;
        return empty;
    }

    std::string line;
    int record_count = 0;
    std::vector<std::string> row;
}
#endif // RecPlace_H