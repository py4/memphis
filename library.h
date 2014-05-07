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
	bool is_in_starred(Book*);
	Book* find_book(std::string);
	void star_book(Book*);
private:
	std::vector <Shelf*> shelves;
	std::vector <Book*> stared_books;
	Node* shelves_node;
	Node* stared_node;
};
#endif
