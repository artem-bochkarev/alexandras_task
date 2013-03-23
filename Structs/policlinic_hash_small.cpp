#include "policlinic_hash.h"
#include "policlinic_string_algo.h"
#include <algorithm>

int SmallHash::h_func(reg_num num)
{
	return (num.num % size);
}

bool SmallHash::add(pacient temp)
{
	int key = h_func(temp.number);
	if (mas[key] == NULL)
		mas[key] = new std::list<pacient>();
	std::list<pacient> * lst = mas[key];
	if (lst->empty())
	{
		lst->push_back(temp);
		++count;
		return true;
	}
	std::list<pacient>::iterator rezult = find(lst->begin(), lst->end(), temp);
	if (rezult == lst->end())
	{
		lst->push_back(temp);
		++count;
		return true;
	}else return false;
}

void SmallHash::remove(pacient temp)
{
	int key = h_func(temp.number);
	if (mas[key] == NULL)
		return;
	--count;
	std::list<pacient> * lst = mas[key];
	lst->remove(temp);
}

pacient * SmallHash::getID(reg_num num)
{
	int key = h_func(num);
	if (mas[key] == NULL)
		return NULL;
	std::list<pacient> * lst = mas[key];
	std::list<pacient>::iterator lst_iter = lst->begin();
	for (;lst_iter != lst->end(); ++lst_iter)
		if ((lst_iter->number.okrug == num.okrug)&&(lst_iter->number.num == num.num))
			return &(*lst_iter);
	return NULL;
}

void SmallHash::searchFIO(const char * fio, std::list<pacient> & lst)
{
	for (int i=0; i<size; ++i)
	{
		if (mas[i] != NULL)
		{
			std::list<pacient> * t_lst = mas[i];
			std::list<pacient>::iterator lst_iter= t_lst->begin();
			for (;lst_iter != t_lst->end(); ++lst_iter)
			{
				if (search(&fio[0], &(lst_iter->fio[0])) == 0)
					lst.push_back(*lst_iter);
			}
		}
	}
}

SmallHash::SmallHash(int n)
	:count(0), size(n)
{
	mas = new std::list<pacient> * [n];
	for (int i=0; i<size; ++i)
		mas[i] = NULL;
}

SmallHash::~SmallHash()
{
	for (int i=0; i<size; ++i)
		if (mas[i] != NULL)
			delete mas[i];
	delete mas;
}

std::list<int> SmallHash::getNumbers()
{
    std::list<int> result;
    for ( int i=0; i<size; ++i )
    {
        if ( mas[i] != NULL )
        {
            std::list<pacient>::iterator it = mas[i]->begin();
            for ( ;it!=mas[i]->end(); ++it)
                result.push_back( it->number.num );
        }
    }
    return result;
}