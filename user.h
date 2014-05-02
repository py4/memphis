#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include "log.h"

class Library;
class Stared;
class Book;

class User
{
	friend class DB;
	
public:
	User();
	~User();
private:
	Library* library;
	std::vector <User*> friends;
	std::vector <Book*> stared_books;
	std::vector <Log*>  activity_logs;

	std::string username;
	std::string password;
};

#endif
