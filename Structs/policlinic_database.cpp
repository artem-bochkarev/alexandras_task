#include "policlinic_database.h"
#include <fstream>
#include <set>

PoliclinicDatabase::PoliclinicDatabase(Tools::Logger& logger)
:patients(3, 2), logger(logger), modified(false), haveFileNames(false) {}

myList& PoliclinicDatabase::getDirections()
{
    return directions;
}

Tree& PoliclinicDatabase::getDoctors()
{
    return doctors;
}

Hash& PoliclinicDatabase::getPatients()
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

void PoliclinicDatabase::fillFileNames()
{
    if ( fileName != "" )
    {
        std::ifstream ifs((directoryName + fileName).c_str());
        if ( ifs.is_open() )
        {
            ifs >> docI >> docFileName >> patI >> patFileName >> dirI >> dirFileName;
            docFileName = directoryName + docFileName;
            dirFileName = directoryName + dirFileName;
            patFileName = directoryName + patFileName;
            haveFileNames = true;
        }
    }
}

void PoliclinicDatabase::load()
{
    fillFileNames();
    logger << "Loading doctors...";
    if ( docI == "txt" )
        doctors.readTextFile( docFileName.c_str() );
    else
        doctors.readBinaryFile( docFileName.c_str() );

    logger << "OK\n";
    logger << "Loading patients...";
    if ( patI == "txt" )
        patients.readTextFile( patFileName.c_str() );
    else
        patients.readBinaryFile( patFileName.c_str() );
    logger << "OK\n";

    logger << "Loading directions...";
    if ( dirI == "txt" )
        directions.readTextFile( dirFileName.c_str() );
    else
        directions.readBinaryFile( dirFileName.c_str() );
    logger << "OK\n";
}

void PoliclinicDatabase::save()
{
    fillFileNames();
    if ( haveFileNames )
    {
        logger << "Saving doctors...";
        if ( docI != "txt" )
            doctors.writeBinaryFile( docFileName.c_str() );

        logger << "OK\n";
        logger << "Saving patients...";
        if ( patI != "txt" )
            patients.writeBinaryFile( patFileName.c_str() );
        logger << "OK\n";

        logger << "Saving directions...";
        if ( dirI != "txt" )
            directions.writeBinaryFile( dirFileName.c_str() );
        logger << "OK\n";
    }
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
