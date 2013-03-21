#ifndef POLICLINIC_STRUCTS_H
#define POLICLINIC_STRUCTS_H
#include "policlinic_string_algo.h"

struct reg_num
{
	/**
		This struct keeps registration number of patient
	*/
	int num; //six digits number
	int okrug; //two digits number of region
};

struct pacient
{
	/**
		This struct keeps information about patient
	*/
	reg_num number;      //registration number
	char fio[51];        //name of patient
	int birth;           //year of birth
	char addres[51];     //addres of home
	char work[51];       //name of profession
};

struct doctor
{
	/**
		This struct keeps information about doctor
	*/
	char fio[51];        //name of doctor
	char dolgnost[51];   //job of doctor
	int cabinet;         //number of cabinet
	char priem[51];      //days of receiving
}; 

struct direction
{
	/**
		This struct keeps information about referrals
	*/
	reg_num number;      //registration number of patient
	char fio[51];        //name of the doctor
	char date[21];       //date of appointed day
	char time[11];       //appointed time
};


/**
	some functions for comparisons of structures
*/
bool operator == (reg_num const & p1, reg_num const & p2);
bool operator != (reg_num const & p1, reg_num const & p2);
bool operator == (pacient const & p1, pacient const & p2);
bool operator == (doctor const & d1, doctor const & d2);
bool operator != (doctor const & d1, doctor const & d2);
bool operator == (direction const & d1, direction const & d2);
bool operator != (direction const & d1, direction const & d2);
bool operator < (direction const & d1, direction const & d2);
bool operator >= (direction const & d1, direction const & d2);

#endif