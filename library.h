#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <vector>
#include <string>
class Shelf;
class Node;

class Library
{

	friend class DB;
public:
	Library() : shelves_node(NULL) {}
	Shelf* add_shelf(std::string);
	Shelf* add_shelf_from_xml(Node* shelf_node);
	
	~Library();
	Shelf* operator[](std::string);

	bool add_book(std::string,std::string = "default");
private:
	std::vector <Shelf*> shelves;
	Node* shelves_node;
};
#endif
