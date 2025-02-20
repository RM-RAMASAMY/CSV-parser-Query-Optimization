#ifndef RecPlace_H
#define RecPlace_H

#include <iostream>
#include <string.h>

using namespace std;

class Place
{
private:
    string borough;
    string off_st_name;
    string on_st_name;
    string cross_st_name;
    string zip;
    string latitude;
    string longitude;
    string location;

public:
    Place()
    {
        borough = "";
        off_st_name = "";
        on_st_name = "";
        cross_st_name = "";
        zip = "";
        latitude = "";
        longitude = "";
        location = "";
    };

    Place(const string &b, const string &off, const string &on, const string &cross, const string &z,
          const string &lat, const string &lon, const string &loc)
    {
        borough = b;
        off_st_name = off;
        on_st_name = on;
        cross_st_name = cross;
        zip = z;
        latitude = lat;
        longitude = lon;
        location = loc;
    }

    string getBorough() { return borough; }
    string getOffStName() { return off_st_name; }
    string getOnStName() { return on_st_name; }
    string getCrossStName() { return cross_st_name; }
    string getZip() { return zip; }
    string getLatitude() { return latitude; }
    string getLongitude() { return longitude; }
    string getLoc() { return location; }
};
#endif // RecPlace_H