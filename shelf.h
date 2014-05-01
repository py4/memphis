#ifndef SHELF_H_
#define SHELF_H_

#include <vector>
#include <string>
#include "db.h"

class Book;

class Shelf
{
public:
	Shelf();
	Shelf(std::string);

	void add_book(std::string);
private:
	vector <Book*> books;
	std::string name;
};

#endif
