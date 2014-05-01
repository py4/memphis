#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <map>
class Book
{
	friend class DB;
public:
	Book();
	Book(std::map<std::string,std::string>&);
private:
	std::string name;
	std::string author;
	std::string publisher;
	std::string year;
};

#endif
