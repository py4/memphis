#include "library.h"
#include "shelf.h"
#include <string>
#include <iostream>
using namespace std;

Library::~Library()
{
	cerr << "deleting library" << endl;
	
	for(int i = 0; i < shelves.size(); i++)
		delete shelves[i];

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


