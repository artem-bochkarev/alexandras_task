#ifndef MY_TREE_H
#define MY_TREE_H

#include "policlinic_structs.h"
#include <list>
#include <stdio.h>
#include "../Tools/Logger.h"

class Tree
{
	struct Node
	{
		Node * left;
		Node * right;
		doctor data;
		int height;
		Node();
		Node(doctor D);
	};
public:
    Tree(Tools::Logger* log);
	~Tree();
	void clear();                                                           //clears all information
	void add(doctor doc);                                                   //adds doctor
	void remove(doctor doc);                                                //removes info about doctor
	void printBalances();                                                   //prints avl coefficients( for debug purposes )
	bool readTextFile(char const * name);                                       //reads doctors from text file
	bool readBinaryFile(char const * name);                                     //reads doctors info from special file
	bool writeBinaryFile(char const * name);                                    //writes doctors info to file
	void showAll(std::list<doctor> & spisok) const;                         //puts all doctors to list
	void changeData(doctor oldDoc, doctor newDoc);                          //makes changes in doctors info
	void searchDolg(const char* sample, std::list<doctor> & spisok) const;                //searches for doctors by his profession
	doctor searchFIO(doctor doc) const;                                           //searches for doctor by his FIO
	doctor searchFIO(const char*) const;                                          //searches for doctor by his FIO
	size_t size() const;
private:
	void lpkDolg(const char* sample, std::list<doctor> & spisok, Node * a) const; //function for search
	void lpk(std::list<doctor> & spisok, Node * a) const;                         //function for show
	void klpBal(Node * a);                                                  //function for rebalance
	void destroy(Node * a);                                                 //function for delete
	void write(FILE * file, Node * a);                                      //function for write
	Node * search(const char * nSample, Node * a) const;                                //function for search
	int height(Node * a);                                                   //function for balance
	void balance(Node * a, Node * prev);                                    //balances Node
	void add(doctor Doc, Node * a, Node * prev);                            //adds node
	void remove (doctor Doc, Node * a, Node * prev);                        //removes node
	Node * smalLeft(Node * a);                                              //turns for balance:
	Node * smalRight(Node * a);
	Node * bigLeft(Node * a);
	Node * bigRight(Node * a);
private:
    Tree();
	Node * root;
	size_t count;
    Tools::Logger* logger;
};

#endif
