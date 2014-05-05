#ifndef SHELF_H_
#define SHELF_H_

#include <vector>
#include <string>
#include "db.h"

class Book;
class Node;

class Shelf
{
	friend class DB;
	friend class API;
	friend class Library;
public:
	Shelf();
	Shelf(std::string);

	void add_book(std::string);
	void add_book(Book*);
	void add_book_from_xml(Node*);
	bool has_book(std::string);
private:
	vector <Book*> books;
	std::string name;
	Node* shelf_node;
};

#endif
