#include "library.h"
#include "shelf.h"
#include <string>
#include <iostream>
using namespace std;

Library::~Library()
{
	cerr << "deleting library" << endl;
	
	for(int i = 0; i < shelves.size(); i++)
		delete shelves[i];
}
void Library::add_shelf(string name)
{
	shelves.push_back(new Shelf(name));
}


