#ifndef RecPeople_H
#define RecPeople_H

#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class People
{
private:
    int per_inj = 0;
    int per_dead = 0;
    int ped_inj = 0;
    int ped_dead = 0;
    int cyc_inj = 0;
    int cyc_dead = 0;
    int mot_inj = 0;
    int mot_dead = 0;

public:
    People() {};

    People(const int &per_inj, const int &per_dead, const int &ped_inj, const int &ped_dead, const int &cyc_inj,
           const int &cyc_dead, const int &mot_inj, const int &mot_dead)
    {
        this->per_inj = per_inj;
        this->per_dead = per_dead;
        this->ped_inj = ped_inj;
        this->ped_dead = ped_dead;
        this->cyc_inj = cyc_inj;
        this->cyc_dead = cyc_dead;
        this->mot_inj = mot_inj;
        this->mot_dead = mot_dead;
    }

    int get_per_inj() const { return per_inj; }
    int get_per_dead() const { return per_dead; }
    int get_ped_inj() const { return ped_inj; }
    int get_ped_dead() const { return ped_dead; }
    int get_cyc_inj() const { return cyc_inj; }
    int get_cyc_dead() const { return cyc_dead; }
    int get_mot_inj() const { return mot_inj; }
    int get_mot_dead() const { return mot_dead; }
};
#endif // RecPeople_H