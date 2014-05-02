#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <vector>
#include <string>

class Shelf;

class Library
{
	friend class DB;
public:
	Shelf* add_shelf(std::string);
	~Library();
private:
	std::vector <Shelf*> shelves;
};
#endif
