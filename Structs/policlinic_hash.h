#ifndef POLICLINIC_HASH_H
#define POLICLINIC_HASH_H
#define _CRT_SECURE_NO_WARNINGS
#include "policlinic_structs.h"
#include <list>

class SmallHash;

/**
	Main hash class, which contains array of SmallHash.
	Hash function counted with reg_num.okrug
*/
class Hash
{
public:
    Hash(int max_okrug, int sm_size);                               //constructs new Hash, where sm_size is size for SmallHash
	~Hash();

	bool add(pacient temp);                                         //adds new patient to hash( return true if succeess)
	void remove(pacient temp);                                      //removes patient from hash
	const pacient * getID(reg_num num) const;                       //returns pointer to pacient by his reg_num
	
    void searchFio(const char * fio, std::list<pacient> & lst);     //searches for patient, result will be placed in list
	void showAll(std::list<pacient> & lst);                         //searches for patient, result will be placed in list
	
	void readTextFile   (const char * name);                        //reads patients from file
    void readBinaryFile (const char * name);                        //reads patients from file
    void writeBinaryFile(const char * name);                        //writes patients to file
	
    void clear();                                                   //clears hash
	size_t size();                                                  //returns number of elements in Hash
    
    std::list<int> getAreas() const;                                //returns list of not empty areas
    std::list<int> getNumbers(int area) const;                      //returns list of numbers by area
private:
    int h_func(reg_num temp) const;                                 //computes hash value
	SmallHash ** mas;
	int m_size, s_size;
	size_t count;
};

/**
	Special hash, which contains information about patients.
	This class is a part of Hash class.
*/
class SmallHash
{
	int h_func(reg_num num);                                        //computes hash value
public:
	bool add(pacient temp);                                         //adds new patient to hash( return true if succeess)
	void remove(pacient temp);                                      //removes patient from hash
	pacient * getID(reg_num num);                                   //returns pointer to pacient by his reg_num
	void searchFIO(const char * fio, std::list<pacient> & lst);     //searches for patient, result will be placed in list
    std::list<int> getNumbers();
	SmallHash(int n);
	~SmallHash();
private:
	std::list<pacient> ** mas;
	int size;
	int count;
};

#endif