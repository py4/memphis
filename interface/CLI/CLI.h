#ifndef CLI_H_
#define CLI_H_

#include "../libs/db.h"
#include "../responder/responder.h"
#include <string>

class CLI
{

public:
	CLI();
	void start();

private:
	void sign_up();
	void sign_in();
	void add_book();
	void show_book();
	void add_shelf();
	void add_to_shelf();
	void like();
	void show_books();
	void show_all_books();
	void show_favorites();
	void follow();
	void show_updates();
	void update_database();
	void logout();
	void add_user_node(User*);

	std::string command;
	map<string,string> params;

	//helpers...
	void ensure_user();
	void ensure_no_user();
};

#endif
