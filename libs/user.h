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
	friend class CLI;
	friend class GUI;
public:
	User(string, string);
	User();
	~User();
	bool is_in_library(Book*);
	bool does_follow(User*);
	
private:
	void like_book(Book*);
	void follow(User*);
	void add_log(std::string);
	void show_logs();
	Library* library;
	std::vector <User*> followings;
	std::vector <User*> followers;
	std::vector <Log*>  activity_logs;
	
	std::string username;
	std::string password;

	Node* user_node;
	Node* followings_node;
	Node* followers_node;
	Node* logs_node;
};

#endif
