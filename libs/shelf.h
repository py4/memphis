#ifndef SHELF_H_
#define SHELF_H_

#include <vector>
#include <string>
#include "db.h"

class Book;
class Node;
class Library;

class Shelf
{
	friend class DB;
	friend class CLI;
	friend class Library;
public:
	Shelf();
	Shelf(std::string);

	void add_book(std::string);
	void add_book(Book*);
	void add_book_from_xml(Node*);
	bool has_book(std::string);
	bool has_book(Book*);
	Book* find_book(std::string);
	void show_books();
	std::string get_name();
	vector<Book*> get_books() { return books; }
private:
	vector <Book*> books;
	std::string name;
	Node* shelf_node;
	Library* library;
};

#endif
