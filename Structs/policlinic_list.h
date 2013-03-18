#ifndef POLIClINIC_LIST_H
#define POLICLINIC_LIST_H
#include "policlinic_structs.h"
#include <stdio.h>
#include <list>

class myList
{
	/**
		This class provides interface for working with referrals.
		It is cyclic double-linked list.
	*/
	struct Node
	{
		/**
			Special class for realization of List.
		*/
		direction data;   //refferal data
		Node * next;      //pointer to next Node
		Node * prev;      //pointer to previous Node
	};
public:
	class iterator
	{
		/**
			This class provides interface for navigation in List.
		*/
		friend class myList;
		public:
			iterator operator++();                       //returns iterator to next element
			iterator operator++(int);                    //returns iterator to next element
			iterator operator--();                       //returns iterator to previous element
			iterator operator--(int);                    //returns iterator to previous element
			bool operator==(iterator const & it) const;  //returns true if iterators points to one element
			bool operator!=(iterator const & it) const;  //returns true if iterators doesn't point to one element
			direction operator*();                       //returns referral placed in current element
			direction * operator->();                    //equal to *referral.
			iterator();
			iterator(iterator const & it);
			iterator(Node * n);
			void swap(iterator & it);
		private:
			Node * temp;
	};
	myList();
	void add(direction dir);                             //adds referral to List
	iterator begin();                                    //returns iterator to first element
	iterator end();                                      //returns iterator to last element(be carefull it is syclic list, (begin()==end()))
	void remove(direction dir);                          //removes referral if it exists
	void remove (iterator & it);                         //removes refferals by iterator
	void readFromTxt(const char * str);                  //read referrals from text file
	~myList();
	void clear();                                        //clears List
	size_t size();                                       //return number of referrals in List
	void searchPacient(pacient pac, std::list<direction> & dirs);  //searches for referrals for specific patient
	void searchDoctor(doctor doc, std::list<direction> & dirs);    //searches for referrals for specific patient
private:
	Node * first;
	size_t count;
private:
	Node * search(direction dir);         //private method for search
	void remove (Node * temp);            //private method for remove
};

void swap(myList::iterator & it1, myList::iterator & it2);   //swaps elements in List
void sort(myList::iterator begin, myList::iterator end);     //sorts elements in List

#endif