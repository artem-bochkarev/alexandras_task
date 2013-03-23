#include "policlinic_hash.h"
#include "policlinic_string_algo.h"
#include <stdio.h>
#include <string.h>

int BigHash::h_func(reg_num temp) const
{
	return ((int)temp.okrug)%m_size;
}

bool BigHash::add(pacient temp)
{
	int key = h_func(temp.number);
	if (mas[key] == NULL)
		mas[key] = new SmallHash(s_size);
	if (mas[key]->add(temp))
	{
		++count;
		return true;
	}else
		return false;
}

void BigHash::remove(pacient temp)
{
	int key = h_func(temp.number);
	if (mas[key] != NULL)
		mas[key]->remove(temp);
	return;
}

const pacient * BigHash::getID(reg_num num) const
{
	int key = h_func(num);
	if (mas[key] == NULL)
		return NULL;
	return mas[num.okrug]->getID(num);
}

void BigHash::searchFio(const char * fio, std::list<pacient> & lst)
{
	for (int i=0; i<m_size; ++i)
		if (mas[i] != NULL)
		{
			mas[i]->searchFIO(fio, lst);
		}
}

void BigHash::showAll(std::list<pacient> & lst)
{
	for (int i=0; i<m_size; ++i)
		if (mas[i] != NULL)
		{
			mas[i]->searchFIO("", lst);
		}
}

BigHash::BigHash(int max_okrug, int sm_size)
{
	count = 0;
	mas = new SmallHash * [max_okrug];
	m_size = max_okrug;
	s_size = sm_size;
	for (int i=0; i<m_size; ++i)
		mas[i] = NULL;
	m_size = max_okrug;
}

BigHash::~BigHash()
{
	for (int i=0; i<m_size; ++i)
		if (mas[i] != NULL)
			delete mas[i];
	delete mas;
}

void BigHash::readFromWinTXT(const char * name)
{
	FILE * file = fopen(name, "rt");
	char s[51];
	fgets(&s[0], 50, file);
	int n;
	sscanf(&s[0], "%i", &n);
	pacient pac;
	for (int i=0; i<n; ++i)
	{
		fgets(&pac.fio[0], 50, file);
		win1251toCP866(&pac.fio[0]);
		fgets(&s[0], 50, file);
		char s1[3];
		char s2[9];
		sscanf(s, "%2s-%8s",&s1[0],&s2[0]);
		sscanf(s1, "%i", &pac.number.okrug);
		sscanf(s2, "%i", &pac.number.num);
		fgets(&s[0], 50, file);
		sscanf(s, "%i",&pac.birth);
		fgets(&pac.addres[0], 50, file);
		win1251toCP866(&pac.addres[0]);
		fgets(&pac.work[0], 50, file);
		win1251toCP866(&pac.work[0]);
		pac.work[strlen((char *)&pac.work)-1] = 0;
		pac.addres[strlen((char *)&pac.addres)-1] = 0;
		pac.fio[strlen((char *)&pac.fio)-1] = 0;

		add(pac);
	}
	fclose(file);
}

void BigHash::clear()
{
	for (int i=0; i<m_size; ++i)
		if (mas[i] != NULL)
		{
			delete mas[i];
			mas[i] = NULL;
		}
	count = 0;
}

size_t BigHash::size()
{
	return count;
}

std::list<int> BigHash::getAreas() const
{
    std::list<int> result;
    for (int i=0; i<m_size; ++i)
		if (mas[i] != NULL)
            result.push_back(i);
    return result;
}

std::list<int> BigHash::getNumbers(int index) const
{
    std::list<int> result;
	if (mas[index] != NULL)
    {
        return mas[index]->getNumbers();
    }
    return result;
}