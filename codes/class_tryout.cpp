#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class CrashReport
{
private:
    std::string crash_time;
    std::string borough;
    std::string zip_code;
    double latitude;
    double longitude;
    std::string location;
    std::string on_street_name;
    std::string cross_street_name;
    std::string off_street_name;
    int num_persons_injured;
    int num_persons_killed;
    int num_pedestrians_injured;
    int num_pedestrians_killed;
    int num_cyclist_injured;
    int num_cyclist_killed;
    int num_motorist_injured;
    int num_motorist_killed;
    std::vector<std::string> contributing_factors;
    std::vector<std::string> vehicle_types;

public:
    // Constructor
    CrashReport(
        std::string crash_time, std::string borough, std::string zip_code,
        double latitude, double longitude, std::string location,
        std::string on_street_name, std::string cross_street_name, std::string off_street_name,
        int num_persons_injured, int num_persons_killed, int num_pedestrians_injured,
        int num_pedestrians_killed, int num_cyclist_injured, int num_cyclist_killed,
        int num_motorist_injured, int num_motorist_killed,
        std::vector<std::string> contributing_factors, std::vector<std::string> vehicle_types)
        : crash_time(crash_time), borough(borough), zip_code(zip_code), latitude(latitude), longitude(longitude),
          location(location), on_street_name(on_street_name), cross_street_name(cross_street_name), off_street_name(off_street_name),
          num_persons_injured(num_persons_injured), num_persons_killed(num_persons_killed),
          num_pedestrians_injured(num_pedestrians_injured), num_pedestrians_killed(num_pedestrians_killed),
          num_cyclist_injured(num_cyclist_injured), num_cyclist_killed(num_cyclist_killed),
          num_motorist_injured(num_motorist_injured), num_motorist_killed(num_motorist_killed),
          contributing_factors(contributing_factors), vehicle_types(vehicle_types) {}

    // Accessors
    std::string getCrashTime() const { return crash_time; }
    std::string getBorough() const { return borough; }
    std::string getLocation() const { return location; }

    void displayReport() const
    {
        std::cout << "Crash Time: " << crash_time << "\n"
                  << "Borough: " << borough << "\n"
                  << "Location: " << location << "\n"
                  << "Persons Injured: " << num_persons_injured << "\n"
                  << "Persons Killed: " << num_persons_killed << "\n"
                  << "Contributing Factors: ";
        for (const auto &factor : contributing_factors)
        {
            std::cout << factor << " ";
        }
        std::cout << "\n";
    }
};

class CrashDataParser
{
public:
    static CrashReport parseData(const std::string &data)
    {
        std::istringstream stream(data);
        std::string field;

        // Example: Simulate parsing fields (you would typically split the input string)
        std::string crash_time = "2:39";
        std::string borough = "BROOKLYN";
        std::string zip_code = "11208";
        double latitude = 40.67;
        double longitude = -73.87;
        std::string location = "(40.667202, -73.8665)";
        std::string on_street_name = "WHITESTONE EXPRESSWAY";
        std::string cross_street_name = "20 AVENUE";
        std::string off_street_name = "1211 LORING AVENUE";
        int num_persons_injured = 2;
        int num_persons_killed = 0;
        int num_pedestrians_injured = 0;
        int num_pedestrians_killed = 0;
        int num_cyclist_injured = 0;
        int num_cyclist_killed = 0;
        int num_motorist_injured = 2;
        int num_motorist_killed = 0;
        std::vector<std::string> contributing_factors = {"Aggressive Driving/Road Rage", "Unspecified", "Unspecified", "Unspecified", "Unspecified"};
        std::vector<std::string> vehicle_types = {"Sedan", "Sedan", "Sedan", "Station Wagon/SUV", "Station Wagon/SUV"};

        return CrashReport(
            crash_time, borough, zip_code, latitude, longitude, location,
            on_street_name, cross_street_name, off_street_name,
            num_persons_injured, num_persons_killed, num_pedestrians_injured, num_pedestrians_killed,
            num_cyclist_injured, num_cyclist_killed, num_motorist_injured, num_motorist_killed,
            contributing_factors, vehicle_types);
    }
};

class CrashReportFacade
{
private:
    std::vector<CrashReport> reports;

public:
    void loadData(const std::vector<std::string> &dataRows)
    {
        for (const auto &row : dataRows)
        {
            reports.push_back(CrashDataParser::parseData(row));
        }
    }

    void displayAllReports() const
    {
        for (const auto &report : reports)
        {
            report.displayReport();
            std::cout << "------------------------\n";
        }
    }
};

int main()
{
    // Simulating data rows
    std::vector<std::string> dataRows = {"Sample Data Row 1", "Sample Data Row 2"};

    // Using the Facade
    CrashReportFacade facade;
    facade.loadData(dataRows);
    facade.displayAllReports();

    return 0;
}
