#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

int main() {
    // Open the CSV file for reading
    std::ifstream file("../Motor_Vehicle.csv");

    auto start = std::chrono::high_resolution_clock::now();

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    int record_count = 0;
    std::vector<std::string> row;

    // Read file line-by-line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;

        // Read each value separated by commas
        // while (std::getline(ss, value, '\0')) {
        //     row.push_back(value);
        // }
        row.push_back(line);
        // Process each row (you can choose to store or print the row)
        record_count++;
        if (record_count % 100000 == 0) { // Print progress every 100k rows
            std::cout << "Processed " << record_count << " records." << std::endl;
        }

        // Example: Process the row (you can store it or do something else)
        // Just printing the first column for illustration
        // std::cout << row[0] << std::endl;

        // Optional: Clear the row to free memory
        // row.clear();
    }
    std::cout << "Total records processed: " << row.size()<< std::endl;
    row.clear();
    row.shrink_to_fit();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

    file.close();
    return 0;
}
