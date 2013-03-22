#include "policlinic_database.h"
#include <fstream>

PoliclinicDatabase::PoliclinicDatabase()
:patients(3, 2) {}

myList& PoliclinicDatabase::getDirections()
{
    return directions;
}

Tree& PoliclinicDatabase::getDoctors()
{
    return doctors;
}

BigHash& PoliclinicDatabase::getPatients()
{
    return patients;
}

const doctor* PoliclinicDatabase::getDoctorByDirection(direction & dir) const
{
    tmp = doctors.searchFIO( (char*)dir.fio[0] );
    if ( tmp.fio[0] == 0 )
        return 0;
    else return &tmp;
}

const pacient* PoliclinicDatabase::getPatientByDirection(direction & dir) const
{
    return patients.getID( dir.number );
}

void PoliclinicDatabase::setDatabase( const char* file )
{
    fileName = file;
}

void PoliclinicDatabase::load()
{
    if ( fileName != "" )
    {
        std::ifstream ifs(fileName.c_str());
        std::string docI, docFileName, patI, patFileName, dirI, dirFileName;
        ifs >> docI >> docFileName >> patI >> patFileName >> dirI >> dirFileName;
        if ( docI == "txt" )
            doctors.readFromTXT( docFileName.c_str() );
        else
            doctors.readFromFile( docFileName.c_str() );

        if ( patI == "txt" )
            patients.readFromWinTXT( patFileName.c_str() );

        if ( dirI == "txt" )
            directions.readFromTxt( dirFileName.c_str() );
    }
}

void PoliclinicDatabase::save()
{
}
