#pragma once

#include "policlinic_structs.h"
#include "policlinic_list.h"
#include "policlinic_hash.h"
#include "policlinic_tree.h"

#include <string>
#include <list>

#include "../Tools/Logger.h"

class PoliclinicDatabase
{
public:
    PoliclinicDatabase(Tools::Logger&);

    BigHash& getPatients();
    Tree& getDoctors();
    myList& getDirections();

    const pacient* getPatientByDirection( direction& ) const;
    const doctor*  getDoctorByDirection ( direction& ) const;
    void setDatabase( std::string&, std::string& );
    std::list<std::string> getDoctorsSpecialities() const;
    std::list<int> getAreas() const;
    std::list<int> getNumbers( int area ) const;
    void load();
    void save();
private:
    BigHash patients;
    Tree doctors;
    myList directions;
    mutable doctor tmp;
    std::string fileName;
    std::string directoryName;

    Tools::Logger& logger;
};