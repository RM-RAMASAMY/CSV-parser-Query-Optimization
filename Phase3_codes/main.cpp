#ifndef RECORD_SEARCH_H
#define RECORD_SEARCH_H

#include <string>
#include <vector>

class RecordSearch
{
public:
    virtual ~RecordSearch() = default;
    virtual bool search(const std::string &criteria) const = 0;
};

class BrooklynSearch : public RecordSearch
{
public:
    bool search(const std::string &criteria) const override;
};

class ManhattanSearch : public RecordSearch
{
public:
    bool search(const std::string &criteria) const override;
};

// Add more subclasses for other boroughs as needed

#endif // RECORD_SEARCH_H

#include "record_search.h"
#include <iostream>

bool BrooklynSearch::search(const std::string &criteria) const
{
    // Implement search logic for Brooklyn
    std::cout << "Searching in Brooklyn for criteria: " << criteria << std::endl;
    // Example logic: return true if criteria matches some condition
    return criteria == "BROOKLYN";
}

bool ManhattanSearch::search(const std::string &criteria) const
{
    // Implement search logic for Manhattan
    std::cout << "Searching in Manhattan for criteria: " << criteria << std::endl;
    // Example logic: return true if criteria matches some condition
    return criteria == "MANHATTAN";
}

// Implement search logic for other boroughs as needed#include "record_search.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<RecordSearch>> searchers;
    searchers.push_back(std::make_unique<BrooklynSearch>());
    searchers.push_back(std::make_unique<ManhattanSearch>());
    // Add more searchers for other boroughs as needed

    std::string criteria;
    std::cout << "Enter search criteria: ";
    std::cin >> criteria;

    for (const auto &searcher : searchers)
    {
        if (searcher->search(criteria))
        {
            std::cout << "Record found for criteria: " << criteria << std::endl;
            break;
        }
    }

    return 0;
}