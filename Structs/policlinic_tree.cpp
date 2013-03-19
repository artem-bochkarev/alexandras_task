#include "policlinic_tree.h"
#include "policlinic_string_algo.h"
#include <string.h>
#include <algorithm>
#include <fstream>


Tree::Node::Node()
	:left(0),right(0),height(1) {}

Tree::Node::Node(doctor D)
	:left(0),right(0),height(1),data(D) {}
	
Tree::Tree()
	:count(0), root(NULL){}

Tree::~Tree()
{
	destroy(root);
}

void Tree::clear()
{
	destroy(root);
	count = 0;
	root = NULL;
}

void Tree::add(doctor doc)
{
	add(doc, root, NULL);
}

void Tree::remove(doctor doc)
{
	remove(doc, root, NULL);
}

void Tree::printBalances()
{
	printf("current KLP balances - ");
	klpBal(root);
	printf("\n");
}

bool Tree::readFromTXT(char const * name)
{
	FILE * file = fopen(name, "rt");
	int n;
	char s[20];
	fgets(&s[0], 20, file);
	sscanf(s, "%i", &n);
	printf("%i", n);
	doctor doc;
	for (int i=1; i<=n; ++i)
	{
		if (fgets((char *)&doc.fio, 50, file) == NULL)
			return false;
		//printf("%s", doc.fio);
		fgets((char *)&doc.dolgnost, 50, file);
		fgets(&s[0], 20, file);
		sscanf(s, "%i", &doc.cabinet);
		fgets((char *)&doc.priem, 50, file);
        fgets(&s[0], 20, file); // empty string
		
		doc.priem[strlen((char *)&doc.priem)-1] = 0;
		doc.dolgnost[strlen((char *)&doc.dolgnost)-1] = 0;
		doc.fio[strlen((char *)&doc.fio)-1] = 0;
		add(doc);
		//printBalances();
	}
	fclose(file);
	return true;
}

bool Tree::readFromFile(char const * name)
{
	FILE * file = fopen(name, "rb");
	size_t k;
	fread(&k, sizeof(size_t), 1, file);
	for (size_t i=0; i<k; ++i)
	{
		doctor temp;
		fread(&temp, sizeof(temp), 1, file);
		add(temp);
	}
	fclose(file);
	return true;
}

bool Tree::writeToFile(char const * name)
{
	FILE * file = fopen(name, "wb");
	fwrite(&count, sizeof(size_t), 1, file);
	write(file, root);
	fclose(file);
	return true;
}

void Tree::showAll(std::list<doctor> & spisok)
{
	if (root != NULL)
	{
		lpk(spisok, root);
	}
}

void Tree::changeData(doctor oldDoc, doctor newDoc)
{
	int len = strlen(oldDoc.fio);
	char * nSample = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nSample, oldDoc.fio);
	toLowCaseCP866(nSample);
	removeDoubleWhiteSpaces(nSample);
	Node * temp = search(nSample, root);
	if (my_strcmp(nSample, newDoc.fio)==0)
		temp->data = newDoc;
	else
	{
		remove(oldDoc, root, NULL);
		add(newDoc, root, NULL);
	}
	free(nSample);
}

void Tree::searchDolg(doctor doc, std::list<doctor> & spisok)
{
	lpkDolg(doc, spisok, root);
}

doctor Tree::searchFIO(doctor doc)
{
	int len = strlen(doc.fio);
	char * nSample = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nSample, doc.fio);
	Node * t = search(nSample, root);
	free(nSample);
	if (t == NULL)
		return doc;
	else
		return t->data;
}

void Tree::lpkDolg(doctor d, std::list<doctor> & spisok, Node * a)
{
	if (a != NULL)
	{
		lpkDolg(d, spisok, a->left);
		if (::search(&d.dolgnost[0], &a->data.dolgnost[0]) == 0)
			spisok.push_back(a->data);
		lpkDolg(d, spisok, a->right);
	}
}

void Tree::lpk(std::list<doctor> & spisok, Node * a)
{
	if (a != NULL)
	{
		lpk(spisok, a->left);
		spisok.push_front(a->data);
		lpk(spisok, a->right);
	}
}

void Tree::klpBal(Node * a)
{
	if (a != NULL)
	{
		printf("%i ", (height(a->right)-height(a->left)));
		klpBal(a->left);
		klpBal(a->right);
	}
}

void Tree::destroy(Node * a)
{
	if (a != NULL)
	{
		destroy(a->left);
		destroy(a->right);
		delete a;
	}
}

void Tree::write(FILE * file, Node * a)
{
	if (a != NULL)
	{
		fwrite(&a->data, sizeof(doctor), 1, file);
		write(file, a->left);
		write(file, a->right);
	}
}

Tree::Node * Tree::search(char * nSample, Node * a)
{
	if (a == NULL) 
		return NULL;
	
	int len = strlen(a->data.fio);
	char * nStr = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nStr, a->data.fio);
	Node * answ;
	
	if (my_strcmp(nSample, nStr) == 0)
		answ = a;
	else if (my_strcmp(nSample, nStr) < 0)
		answ = search(nSample, a->left);
	else
		answ = search(nSample, a->right);
	free(nStr);
	return answ;
}

int Tree::height(Node * a)
{
	if (a == NULL)
		return 0;
	else
		return a->height;
}

void Tree::balance(Node * a, Node * prev)
{
	a->height = std::max(height(a->left), height(a->right));
	Node * left = a->left;
	Node * right = a->right;
	Node ** who = &root;
	if (prev != NULL)
	{
		if (prev->left == a)
			who = &(prev->left);
		else
			who = &(prev->right);
	}
	if ((height(left) - height(right)) >= 2)
	{
		int lrh = height(left->right);
		int llh = height(left->left);
		if (lrh <= llh)
			*who = smalRight(a);
		else
			*who = bigRight(a);
	}else if ((height(right) - height(left)) >= 2)
	{
		int rlh = height(right->left);
		int rrh = height(right->right);
		if (rlh <= rrh)
			*who = smalLeft(a);
		else
			*who = bigLeft(a);
	}else
	{
		//no balance needed.
	}
	return;
}

void Tree::add(doctor Doc, Node * a, Node * prev)
{
	if (a == NULL)
	{
		root = new Node(Doc);
		++count;
		return;
	}

	if (my_strcmp(Doc.fio, a->data.fio) == 0)
		return;
	if (my_strcmp(Doc.fio, a->data.fio) < 0)
	{
		if (a->left != NULL)
			add(Doc, a->left, a);
		else
		{
			a->left = new Node(Doc);
			if (a->height == 1)
				a->height = 2;
			++count;
			return; 
		}
	}else
	{
		if (a->right != NULL)
			add(Doc, a->right, a);
		else
		{
			a->right = new Node(Doc);
			if (a->height == 1)
				a->height = 2;
			++count;
			return;
		}
	}
	balance(a, prev);
	return;
}

void Tree::remove(doctor Doc, Node * a, Node * prev)
{
	if (a == NULL)
		return;
	if (my_strcmp(Doc.fio, a->data.fio) < 0)
	{
		if (a->left != NULL)
			remove(Doc, a->left, a);
		else
			return; 
	}else if (my_strcmp(Doc.fio, a->data.fio) > 0)
	{
		if (a->right != NULL)
			remove(Doc, a->right, a);
		else
			return;
	}else
	{
		//continue.
	}
	if (my_strcmp(Doc.fio, a->data.fio) == 0)
	{
		if (a->left == NULL)
		{
			if (prev != NULL)
			{
				if (prev->right == a)
					prev->right = a->right;
				else 
					prev->left = a->right;
			}else
				root = a->right;
			--count;
			delete a;
			return;
		}else
		{
			Node * temp = a->left;
			Node * rez = temp;
			if (temp->right == NULL)
			{
				rez = temp;
			}
			else
			{
				while (temp->right->right != NULL)
					temp = temp->right;
				rez = temp->right;
			}
			if (prev != NULL)
			{
				if (prev->right == a)
						prev->right = rez;
					else 
						prev->left = rez;
			}else 
				root = rez;
			
			if (rez != temp)
			{
				rez->right = a->right;
				temp->right = rez->left;
				rez->left = a->left;
			}else
				rez->right = a->right;
			--count;
			delete a;
			balance(rez, prev);
			return;
		}
	}
	balance(a, prev);
	return;
}

Tree::Node * Tree::smalLeft(Node * a)
{
	Node * b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = std::max(height(a->left), height(a->right)) + 1;
	b->height = std::max(a->height, height(b->right)) + 1;
	return b;
}

Tree::Node * Tree::smalRight(Node * a)
{
	Node * b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = std::max(height(a->left), height(a->right)) + 1;
	b->height = std::max(a->height, height(b->left)) + 1;
	return b;
}

Tree::Node * Tree::bigLeft(Node * a)
{
	Node * b = a->right;
	Node * c = b->left;
	a->right = c->left;
	b->left = c->right;
	c->left = a;
	c->right = b;
	a->height = std::max(height(a->left), height(a->right)) + 1;
	b->height = std::max(height(b->left), height(b->right)) + 1;
	c->height = std::max(a->height, b->height);
	return c;
}

Tree::Node * Tree::bigRight(Node * a)
{
	Node * b = a->left;
	Node * c = b->right;
	b->right = c->left;
	a->left = c->right;
	c->left = b;
	c->right = a;
	a->height = std::max(height(a->left), height(a->right)) + 1;
	b->height = std::max(height(b->left), height(b->right)) + 1;
	c->height = std::max(a->height, b->height);
	return c;
}

int Tree::size() const
{
    return count;
}