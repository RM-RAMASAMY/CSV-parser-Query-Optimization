#ifndef TimeStamp_H
#define TimeStamp_H

#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class TimeStamp
{
private:
    string crashtime;
    string crashdate;
    int crashtime_min;
    int crashtime_hour;
    int crashdate_day;
    int crashdate_month;
    int crashdate_year;

public:
    TimeStamp()
    {
        crashtime = "00:00";
        crashdate = "01/01/2000";
        crashtime_min = 0;
        crashtime_hour = 0;
        crashdate_day = 1;
        crashdate_month = 1;
        crashdate_year = 2000;
    }
    TimeStamp(const string &mytime, const string &date)
    {
        crashtime = mytime;
        crashdate = date;
        int colon = mytime.find(':');
        crashtime_min = stoi(mytime.substr(0, colon));
        crashtime_hour = stoi(mytime.substr(colon + 1));
        crashdate_day = stoi(date.substr(0, 2));
        crashdate_month = stoi(date.substr(3, 2));
        crashdate_year = stoi(date.substr(6, 4));
    }
    int getYear() { return crashdate_year; }
    int getMonth() { return crashdate_month; }
    int getDay() { return crashdate_day; }
    int getHour() { return crashtime_hour; }
    int getMinute() { return crashtime_min; }
    string gettime() { return crashtime; }
    string getDate() { return crashdate; }
};
#endif // TimeStamp_H