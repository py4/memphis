#ifndef DB_H_
#define DB_H_

#define DATABASE "database.txt"
#define USERS "users.txt"
#define DATA "data.txt"

#include <vector>
#include "parser/XML.h"
class User;
class Book;

class DB
{
public:

	static DB* db();
	static void free_db();
	
	Book* find_book(string);
	User* find_user(string);
	string dump_db();
	static bool create_instance();
	
private:
	void populate_books();
	void populate_users();
	void populate();	
	Book* find_or_create_book(string);

	void configure_shelves(User*, vector<Node*>&);
	void configure_activity_logs(User*, vector<Node*>&);
	void configure_stared_books(User*, vector<Node*> &);

	DB();
  DB(DB const&);
	~DB();
  void operator=(DB const&);

  static DB* instance;
	XML xml;
	std::vector <User*> users;
	std::vector <Book*> books;

	User* current_user;
};

#endif
