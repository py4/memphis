#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include "log.h"

class Library;
class Stared;
class Book;
class Node;

class User
{
	friend class DB;
	friend class API;
public:
	User(string, string);
	User();
	~User();
	
private:
	Library* library;
	std::vector <User*> friends;
	std::vector <Book*> stared_books;
	std::vector <Log*>  activity_logs;

	std::string username;
	std::string password;

	Node* user_node;
};

#endif
