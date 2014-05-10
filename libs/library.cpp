#include "library.h"
#include "shelf.h"
#include <string>
#include <iostream>
#include "book.h"

using namespace std;

Library::~Library()
{
	cerr << "deleting library" << endl;
	
	for(int i = 0; i < shelves.size(); i++)
		delete shelves[i];
	stared_books.clear();
	shelves.clear();
}

Shelf* Library::add_shelf(string name)
{
	shelves.push_back(new Shelf(name));
		
	if(shelves_node == NULL)
		cerr << "[BUG] shelves_node should not be NULL" << endl;
	
	Node* shelf_node = shelves_node->add_node("shelf");
	shelf_node->set_attribute("name",name);
	shelves.back()->shelf_node = shelf_node;

	return shelves.back();
}

Shelf* Library::add_shelf_from_xml(Node* shelf_node)
{
	shelves.push_back(new Shelf(shelf_node->operator[]("name")));
	if(shelves_node == NULL)
		cerr << "[BUG] shelves_node should not be NULL" << endl;

	shelves.back()->shelf_node = shelf_node;

	return shelves.back();
}

Shelf* Library::operator[](string name)
{
	for(int i = 0; i < shelves.size(); i++)
		if(shelves[i]->name == name)
			return shelves[i];
	return NULL;
}

bool Library::add_book(string book_name, string shelf_name)
{
	Shelf* shelf = operator[](shelf_name);
	if(shelf->has_book(book_name))
		return false;
	else
	{
		operator[](shelf_name)->add_book(book_name);
		return true;
	}
}

bool Library::is_in_library(Book* book)
{
	for(int i = 0;i < shelves.size(); i++)
		if(shelves[i]->has_book(book))
			return true;
	return false;
}

bool Library::is_in_library(string name)
{
	for(int i = 0;i < shelves.size(); i++)
		if(shelves[i]->has_book(name))
			return true;
	return false;
}

bool Library::is_in_starred(Book* book)
{
	for(int i = 0; i < stared_books.size(); i++)
		if(stared_books[i] == book)
			return true;
	return false;
}

bool Library::is_in_starred(string name)
{
	for(int i = 0; i < stared_books.size(); i++)
		if(stared_books[i]->get_name() == name)
			return true;
	return false;
}

Shelf* Library::get_shelf(string name)
{
	for(int i = 0; i < shelves.size(); i++)
		if(shelves[i]->name == name)
			return shelves[i];
	return NULL;
}

Book* Library::find_book(string name)
{
	Book* book = NULL;
	for(int i = 0; i < shelves.size(); i++)
		if((book = shelves[i]->find_book(name)) != NULL)
			return book;
	return book;
}

void Library::star_book(Book* book)
{
	stared_books.push_back(book);
	stared_node->add_node("book",book->name);
}

void Library::show_all_books()
{
	Shelf* default_shelf = get_shelf("default");
	default_shelf->show_books();
}

void Library::show_favorites()
{
	for(int i = 0; i < stared_books.size(); i++)
	{
		stared_books[i]->show_info();
		cout << "---------------" << endl;
	}
}

vector <Shelf*>& Library::get_shelves()
{
	return shelves;
}

vector <Book*>& Library::get_stared_books()
{
	return stared_books;
}
