#include "policlinic_list.h"
#include "policlinic_string_algo.h"
#include <string.h>

myList::myList()
	:first(NULL), count(0){}
	
void myList::add(direction dir)
{
	Node * newNode = new Node();
	newNode->data = dir;
	if (count != 0)
	{
		newNode->next = first;
		newNode->prev = first->prev;
		first->prev = newNode;
		newNode->prev->next = newNode;
	}else
	{
		first = newNode;
		first->next = first;
		first->prev = first;
	}
	++count;
}

myList::iterator myList::begin()
{
	return iterator(first);
}

myList::iterator myList::end()
{
	return iterator(first);
}

void myList::remove(direction dir)
{
	Node * temp = search(dir);
	remove(temp);
}

void myList::remove(iterator & it)
{
	iterator temp(it);
	++it;
	remove(temp.temp);
	if (size() == 0)
		it.temp = NULL;
}

void myList::readFromTxt(const char * str)
{
	FILE * file = fopen(str, "rt");
	char s[51];
	fgets(s, 50, file);
	int n;
	sscanf(s, "%i", &n);
	direction dir;
	for (int i=0; i<n; ++i)
	{
		fgets(dir.fio, 50, file);
		win1251toCP866(dir.fio);
		fgets(s, 50, file);
		char s1[3];
		char s2[9];
		sscanf(s, "%2s %8s", s1, s2);
		sscanf(s1, "%i", &dir.number.okrug);
		sscanf(s2, "%i", &dir.number.num);
		fgets(dir.date, 20, file);
		win1251toCP866(dir.date);
		fgets(dir.time, 10, file);
		win1251toCP866(dir.time);
		dir.fio[strlen(dir.fio)-1] = 0;
		dir.time[strlen(dir.time)-1] = 0;
		dir.date[strlen(dir.date)-1] = 0;
		add(dir);
	}
	fclose(file);
}

myList::~myList()
{
	Node * temp;
	if (first != NULL)
		if (first->prev != NULL)
			first->prev->next = NULL;
	while (first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
}

void myList::clear()
{
	Node * temp;
	if (first != NULL)
		if (first->prev != NULL)
			first->prev->next = NULL;
	while (first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
	first = NULL;
	count = 0;
}

size_t myList::size()
{
	return count;
}

myList::Node * myList::search(direction dir)
{
	if (first == NULL)
		return NULL;
	Node * temp = first;
	do
	{
		if (temp->data == dir)
			return temp;
		temp = temp->next;
	}while (temp != first);
}

void myList::remove (Node * temp)
{
	if (temp != NULL)
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		if (first == temp)
			first = temp->next;
		if (count == 1)
			first = NULL;
		delete temp;
		--count;
	}
}

void myList::searchPacient(pacient pac, std::list<direction> & dirs)
{
	iterator it = begin();
	do
	{
		if (it->number == pac.number)
			dirs.push_back(*it);
		++it;
	}while (it != end());
}

void myList::searchDoctor(doctor doc, std::list<direction> & dirs)
{
	iterator it = begin();
	do
	{
		if (strcmp(it->fio, doc.fio) == 0)
			dirs.push_back(*it);
		++it;
	}while (it != end());
}