#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <vector>
#include <string>
class Shelf;
class Node;
class Book;

class Library
{

	friend class DB;
public:
	Library() : shelves_node(NULL) {}
	Shelf* add_shelf(std::string);
	Shelf* add_shelf_from_xml(Node*);
	Shelf* get_shelf(std::string);
	~Library();
	Shelf* operator[](std::string);
	bool add_book(std::string,std::string = "default");
	bool is_in_library(Book*);
	bool is_in_library(std::string);
private:
	std::vector <Shelf*> shelves;
	Node* shelves_node;
};
#endif
