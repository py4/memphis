#ifndef API_H_
#define API_H_

#include "db.h"

class API
{
	
public:
	void register(string,string);
	void login();
	void add_book(string);
	void show_book(string);
	void add_shelf(string);
	void add_to_shelf(string,string);
	void like(string);
	void show_books(string);
	void show_all_books();
	void show_favorites();
	void follow(string);
	void show_updates();
	void update_database();
	void logout();
	
private:
	is_logged_in();
	
};

#endif
