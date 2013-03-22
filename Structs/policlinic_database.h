#pragma once

#include "policlinic_structs.h"
#include "policlinic_list.h"
#include "policlinic_hash.h"
#include "policlinic_tree.h"

#include <string>

class PoliclinicDatabase
{
public:
    PoliclinicDatabase();

    BigHash& getPatients();
    Tree& getDoctors();
    myList& getDirections();

    const pacient* getPatientByDirection( direction& ) const;
    const doctor*  getDoctorByDirection ( direction& ) const;
    void setDatabase( const char * );
    void load();
    void save();
private:
    BigHash patients;
    Tree doctors;
    myList directions;
    mutable doctor tmp;
    std::string fileName;
};