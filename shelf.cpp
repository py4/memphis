#include "shelf.h"
#include <string>
#include <iostream>
#include "book.h"

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
	{
		books.push_back(book);
		shelf_node->add_node("book",name);
	}
	else
		cerr << "[shelf][add_book] book not found!" << endl;
}

void Shelf::add_book(Book* book)
{
	if(book == NULL)
	{
		cerr << "so killer bug" << endl;
		return;
	}

	books.push_back(book);
	shelf_node->add_node("book",book->name);
}

void Shelf::add_book_from_xml(Node* book_node)
{
	Book* book = DB::db()->find_book(book_node->get_value());
	if(book != NULL)
		books.push_back(book);
	else
		cerr << "[shelf][add_book] book not found!" << endl;
}

bool Shelf::has_book(string book_name)
{
	for(int i = 0; i < books.size(); i++)
	{
		if(books[i]->name == book_name)
			return true;
	}
	return false;
}

bool Shelf::has_book(Book* book)
{
	for(int i = 0; i < books.size(); i++)
		if(books[i] == book)
			return true;
	return false;
}

Book* Shelf::find_book(string book_name)
{
	for(int i = 0; i < books.size(); i++)
	{
		if(books[i]->name == book_name)
			return books[i];
	}
	return NULL;
}
