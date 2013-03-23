#include "policlinic_database.h"
#include <fstream>
#include <set>

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
    tmp = doctors.searchFIO( dir.fio );
    if ( tmp.fio[0] == 0 )
        return 0;
    else return &tmp;
}

const pacient* PoliclinicDatabase::getPatientByDirection(direction & dir) const
{
    return patients.getID( dir.number );
}

void PoliclinicDatabase::setDatabase( std::string& dir, std::string& name )
{
    directoryName = dir;
    if ( directoryName[directoryName.size()-1] != '/' )
        directoryName += '/';
    fileName = name;
}

void PoliclinicDatabase::load()
{
    if ( fileName != "" )
    {
        std::ifstream ifs((directoryName + fileName).c_str());
        if ( ifs.is_open() )
        {
            std::string docI, docFileName, patI, patFileName, dirI, dirFileName;
            ifs >> docI >> docFileName >> patI >> patFileName >> dirI >> dirFileName;
            docFileName = directoryName + docFileName;
            dirFileName = directoryName + dirFileName;
            patFileName = directoryName + patFileName;
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
}

void PoliclinicDatabase::save()
{
}

std::list<std::string> PoliclinicDatabase::getDoctorsSpecialities() const
{
    std::list<doctor> spisok;
    doctors.showAll( spisok );
    std::list<doctor>::iterator iter = spisok.begin();
    std::set<std::string> set;
    for ( ;iter!=spisok.end(); ++iter)
    {
        set.insert( std::string(iter->dolgnost) );
    }
    std::list<std::string> result;
    std::set<std::string>::iterator it = set.begin();
    for ( ;it!=set.end(); ++it)
    {
        result.push_back(*it);
    }
    return result;
}
std::list<int> PoliclinicDatabase::getAreas() const
{
    return patients.getAreas();
}

std::list<int> PoliclinicDatabase::getNumbers( int area ) const
{
    return patients.getNumbers( area );
}
