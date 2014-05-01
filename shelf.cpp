#include "shelf.h"
#include <string>
#include <iostream>

using namespace std;

Shelf::Shelf()
{
}

Shelf::Shelf(string name)
{
	this->name = name;
}

void Shelf::add_book(string name)
{
	Book* book = DB::db()->find_book(name);
	if(book != NULL)
		books.push_back(book);
	else
		cerr << "[shelf][add_book] book not found!" << endl;
}
