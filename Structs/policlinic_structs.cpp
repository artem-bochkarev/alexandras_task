#include "policlinic_structs.h"
#include <string.h>
#include <stdio.h>

bool operator == (reg_num const & p1, reg_num const & p2)
{
	return ((p1.num == p2.num)&&(p1.okrug == p2.okrug));
}

bool operator == (pacient const & p1, pacient const & p2)
{
	return (p1.number == p2.number);
}

bool operator == (doctor const & d1, doctor const & d2)
{
	if ((strcmp(d1.fio, d2.fio) == 0)&&(d1.cabinet == d2.cabinet))
		return true;
	else
		return false;
}

bool operator != (doctor const & d1, doctor const & d2)
{
	return (!(d1 == d2));
}

bool operator == (direction const & d1, direction const & d2)
{
	return ((d1.number == d2.number)&&(strcmp(d1.fio, d2.fio)==0));
}

bool operator != (direction const & d1, direction const & d2)
{
	return (!(d1 == d2));
}

bool operator < (direction const & d1, direction const & d2)
{
	return (strcmp(d1.fio, d2.fio) < 0);
}

bool operator >= (direction const & d1, direction const & d2)
{
	return (strcmp(d1.fio, d2.fio) >= 0);
}