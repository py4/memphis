#ifndef API_H_
#define API_H_

#include "db.h"
#include "responder/responder.h"
#include <string>

class API
{

public:
	API();
	void start();

private:
	void sign_up();
	void sign_in();
	void add_book();
	void show_book();
	void add_shelf();
	void add_to_shelf();
	void like();
	void show_books(string);
	void show_all_books();
	void show_favorites();
	void follow(string);
	void show_updates();
	void update_database();
	void logout();
	void add_user_node(User*);

	std::string command;
	map<string,string> params;

	//helpers...
	void ensure_user();
	void ensure_no_user();

	User* current_user;
};

#endif
