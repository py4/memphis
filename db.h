#ifndef DB_H_
#define DB_H_

#define NEW_BOOKS "database/database.txt"
#define DATA "database/data.txt"

#include <vector>
#include "parser/XML.h"
class User;
class Book;
class API;

class DB
{
	friend class API;
public:

	static DB* db();
	
	Book* find_book(string);
	User* find_user(string);
	string dump_db();
	static bool create_instance();
	void start_api();
	static void free_db();
private:
	void save_to_disk(string = DATA);
	void load_new_books();
	void create_schema();
	void populate_books();
	void populate_users();
	void populate();	
	Book* find_or_create_book(string);

	void configure_shelves(User*, vector<Node*>&);
	void configure_activity_logs(User*, vector<Node*>&);
	void configure_stared_books(User*, vector<Node*> &);

	void add_book_to_xml(Book*);
	void add_user(User*);

	DB();
  DB(DB const&);
	~DB();
  void operator=(DB const&);

  static DB* instance;
	XML xml;
	std::vector <User*> users;
	std::vector <Book*> books;
	
	API* api;
};

#endif
