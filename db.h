#ifndef DB_H_
#define DB_H_

#define DATABASE "database.txt"
#define USERS "users.txt"

#include <vector>
#include "parser/parser.h"

class User;
class Book;

class DB
{
public:

	static DB* db();
	static void free_db();
	
	Book* find_book(string);
	User* find_user(string);
	
private:
	void populate_books();
	void populate_users();
	void populate();
	std::vector <User*> users;
	std::vector <Book*> books;

	Book* find_or_create_book(string);

  static DB* instance;
	DB();
  DB(DB const&);              // Don't Implement.
	~DB();
  void operator=(DB const&); // Don't implement
};

#endif
