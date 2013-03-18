#ifndef POLICLINIC_HASH_H
#define POLICLINIC_HASH_H
#include "policlinic_structs.h"
#include <list>

/**
	Special hash, which contains information about patients.
	This class is a part of BigHash class.
*/
class SmallHash
{
	int h_func(reg_num num);                                        //computes hash value
public:
	bool add(pacient temp);                                         //adds new patient to hash( return true if succeess)
	void remove(pacient temp);                                      //removes patient from hash
	pacient * getID(reg_num num);                                   //returns pointer to pacient by his reg_num
	void searchFIO(const char * fio, std::list<pacient> & lst);     //searches for patient, result will be placed in list
	SmallHash(int n);
	~SmallHash();
private:
	std::list<pacient> ** mas;
	int size;
	int count;
};

/**
	Main hash class, which contains array of SmallHash.
	Hash function counted with reg_num.okrug
*/
class BigHash
{
	int h_func(reg_num temp);                                       //computes hash value
public:
	bool add(pacient temp);                                         //adds new patient to hash( return true if succeess)
	void remove(pacient temp);                                      //removes patient from hash
	pacient * getID(reg_num num);                                   //returns pointer to pacient by his reg_num
	void searchFio(const char * fio, std::list<pacient> & lst);     //searches for patient, result will be placed in list
	BigHash(int max_okrug, int sm_size);                            //constructs new Hash, where sm_size is size for SmallHash
	~BigHash();
	void readFromWinTXT(const char * name);                         //reads patients from file
	void clear();                                                   //clears hash
	size_t getSize();                                               //returns size of Hash
private:
	SmallHash ** mas;
	int size, s_size;
	size_t count;
};
#endif