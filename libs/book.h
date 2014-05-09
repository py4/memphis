#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <map>
class Book
{
	friend class DB;
	friend class CLI;
	friend class Shelf;
	friend class Library;
public:
	Book();
	Book(std::map<std::string,std::string>&);
	void show_info();
	std::string get_name() { return name; }
	std::string get_author() { return author; }
	std::string get_publisher() { return publisher; }
	std::string get_year() { return year; }
private:
	std::string name;
	std::string author;
	std::string publisher;
	std::string year;
};

#endif
