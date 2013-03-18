#include "policlinic_list.h"

myList::iterator::iterator()
	:temp(NULL) {}
	
myList::iterator::iterator(iterator const & it)
	:temp(it.temp) {}
	
myList::iterator::iterator(Node * n)
	:temp(n) {}

myList::iterator myList::iterator::operator++()
{
	if (temp != NULL)
		temp = temp->next;
	return *this;
}
			
myList::iterator myList::iterator::operator++(int)
{
	iterator t(*this);
	if (temp != NULL)
		temp = temp->next;
	return t;
}

myList::iterator myList::iterator::operator--()
{
	if (temp != NULL)
		temp = temp->prev;
	return *this;
}

myList::iterator myList::iterator::operator--(int)
{
	iterator t(*this);
	if (temp != NULL)
		temp = temp->prev;
	return t;
}

bool myList::iterator::operator==(iterator const & it) const
{
	if (it.temp == temp)
	{
		return true;
	}else
		return false;
}

bool myList::iterator::operator!=(iterator const & it) const
{
	return !(it==*this);
}

direction myList::iterator::operator*()
{
	if (temp != NULL)
		return temp->data;
	return direction();
}

direction * myList::iterator::operator->()
{
	if (temp == NULL)
		return NULL;
	return &(temp->data);
}

void myList::iterator::swap(iterator & it)
{
	direction t = it.temp->data;
	it.temp->data = temp->data;
	temp->data = t;
}

void swap(myList::iterator & it1, myList::iterator & it2)
{
	it1.swap(it2);
}

void sort(myList::iterator begin, myList::iterator end)
{
	--end;
	direction med = *end;
	myList::iterator left = begin;
	myList::iterator right = end;
	--right;
	while (left != right)
	{
		while ((*left < med)&&(left != right))
			++left;
		while ((*right >= med)&&(left != right))
			--right;
		if (left != right)
		{
			swap(left, right);
			++left;
			if (left!=right)
				--right;
		}
	}
	if (*right < med)
	{
		++right;
	}
	swap(right, end);
	left = right;
	--left;
	if ((begin != left)&&(begin != right))
		sort(begin, right);
	left = right;
	++right;
	if ((left != end)&&(right != end))
		sort(right, ++end);
}