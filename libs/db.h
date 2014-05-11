#ifndef DB_H_
#define DB_H_

#define NEW_BOOKS "database/database.txt"
#define DATA "database/data.txt"

#include <vector>
#include "../parser/XML.h"
class User;
class Book;
class CLI;
class GUI;
class DB
{
	friend class CLI;
	friend class GUI;
	friend class MainWindow;
public:

	static DB* db();
	
	Book* find_book(string);
	User* find_user(string);
	string dump_db();
	static bool create_instance();
	void start_cli();
	int start_gui(int argc, char* argv[]);
	static void free_db();

	vector <Book*>& get_books() { return books; }
	vector <User*>& get_users() { return users; }

	User* user() { return current_user; }
	void save_to_disk(string = DATA);
	
private:
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
	
	CLI* cli;
	GUI* gui;
	User* current_user;
};

#endif
