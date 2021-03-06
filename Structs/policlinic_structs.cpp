#include "policlinic_structs.h"
#include <string.h>
#include <stdio.h>

bool operator == (reg_num const & p1, reg_num const & p2)
{
	return ((p1.num == p2.num)&&(p1.okrug == p2.okrug));
}

bool operator != (reg_num const & p1, reg_num const & p2)
{
	return !(p1 == p2);
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

doctor empty_doctor()
{
    doctor doc;
    doc.cabinet = 0;
    doc.dolgnost[0] = 0;
    doc.priem[0] = 0;
    doc.fio[0] = 0;
    return doc;
}

pacient empty_patient()
{
    pacient pac;
    pac.addres[0] = 0;
    pac.birth = 0;
    pac.fio[0] = 0;
    pac.work[0] = 0;
    pac.number.num = 0;
    pac.number.okrug = 0;
    return pac;
}