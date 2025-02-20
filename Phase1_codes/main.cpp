#include <iostream>
#include <vector>
#include <string>
#include "RecTimeStamp.h"
#include "RecPlace.h"
#include "RecPeople.h"
#include "RecVehicle.h"
#include "CrashRecord.h"
#include "RecReader.h"
#include "search.h"
#include <chrono>
int main()
{
     auto start1 = std::chrono::high_resolution_clock::now();
     // Path to the CSV file
     std::string filename = "../../../Motor_Vehicle.csv";

     // Read the CSV file into a vector of Record objects
     std::vector<CrashRecord> records = readCSV(filename);
     auto stop1 = std::chrono::high_resolution_clock::now();
     auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
     cout << "Time taken by csv reader function: "
          << duration1.count() << " microseconds" << endl;

     // Print the number of records read
     std::cout << "Number of records read: " << records.size() << std::endl;

     auto start2 = std::chrono::high_resolution_clock::now();
     // hardcoding the borough name for performance testing
     string borough = "BROOKLYN";
     searchByBorough(borough, records);
     auto stop2 = std::chrono::high_resolution_clock::now();
     auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
     cout << "Time taken by search function: "
          << duration2.count() << " microseconds" << endl;
     return 0;
}