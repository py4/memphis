#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <map>
class Book
{
	friend class DB;
	friend class API;
	friend class Shelf;
	friend class Library;
public:
	Book();
	Book(std::map<std::string,std::string>&);
	void show_info();
private:
	std::string name;
	std::string author;
	std::string publisher;
	std::string year;
};

#endif
