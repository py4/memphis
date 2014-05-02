#include "db.h"
#include "user.h"
#include "book.h"
#include "library.h"
#include "shelf.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

DB* DB::instance = 0;

DB::DB()
{
	xml.load(DATA);
	xml.parse();
}

DB* DB::db()
{
	return DB::instance;
}

bool DB::create_instance()
{
	if(!instance)
	{
		instance = new DB;
		instance->populate();
		return true;
	}
	return false;
}

void DB::free_db()
{
	delete instance;
}

DB::~DB()
{
	cerr << "database destructor" << endl;
	for(int i = 0; i < users.size(); i++)
		delete users[i];
	for(int i = 0; i < books.size(); i++)
		delete books[i];
}

void DB::populate_books()
{
	/* TODO: exception of file not found */

	ifstream book_db;
	string line;
	map <string,string> book_info;
	
	book_db.open(DATABASE);
	
	while(getline(book_db,line))
	{
		book_info = parse_book(line);
		books.push_back(new Book(book_info));
	}
}

Book* DB::find_book(string name)
{
	for(int i = 0; i < books.size(); i++)
	{
		if(books[i]->name == name)
			return books[i];
	}
	return NULL;
}

User* DB::find_user(string username)
{
	for(int i = 0; i < users.size(); i++)
		if(users[i]->username == username)
			return users[i];
	return NULL;
}
Book* DB::find_or_create_book(string name)
{

	Book* book = find_book(name);
	if(book != NULL)
		return book;
	
	cerr << "bug in input" << endl;
	map<string,string> book_info;
	book_info["name"] = name;
	books.push_back(new Book(book_info));
}

void DB::configure_shelves(User* c_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size();j++)
	{

		Shelf* shelf = c_user->library->add_shelf((*nodes[j])["name"]);

		for(int k = 0; k < nodes[j]->children.size(); k++)
			shelf->add_book(nodes[j]->children[k]->value);
	}
}

void DB::configure_activity_logs(User* c_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size(); j++)
	{
		string name = nodes[j]->get_child_node("username")->value;
		string message = nodes[j]->get_child_node("message")->value;
		c_user->activity_logs.push_back(new Log(name, message));
	}
}

void DB::configure_stared_books(User* c_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size(); j++)
	{
		Book* book = find_book(nodes[j]->value);
		if(book != NULL)
			c_user->stared_books.push_back(book);
		else
			cerr << "[db][populate_users] book not found" << endl;
	}
}



void DB::populate_users()
{
	ifstream users_db(USERS);
	string line;
	User* c_user = NULL;

	map <string, vector <string> > friends;

	for(int i = 0; i < xml["users"]->children.size();i++)
	{
		Node* user_node = xml["users"]->children[i];
		c_user = new User;
		c_user->username = user_node->get_child_node("username")->value;
		c_user->password = user_node->get_child_node("password")->value;
		
		configure_shelves(c_user, user_node->get_child_node("shelves")->children);
		configure_activity_logs(c_user, user_node->get_child_node("ActivityLogs")->children);
		configure_stared_books(c_user, user_node->get_child_node("favorites")->children);
		for(int j = 0; j < user_node->get_child_node("friends")->children.size(); j++)
			friends[c_user->username].push_back(user_node->get_child_node("friends")->children[j]->value);

		users.push_back(c_user);
	}

	map <string, vector<string> >::iterator i;
	for(i = friends.begin(); i != friends.end(); i++)
	{
		User* user = find_user(i->first);
		for(int j = 0; j < i->second.size(); j++)
		{
			User* user_friend = find_user(i->second[j]);
			if(user_friend != NULL)
				user->friends.push_back(user_friend);
			else
				cerr << "[db populator] user friend not found" << endl;
		}
	}
}

void DB::populate()
{
	populate_books();
	populate_users();
}

string DB::dump_db()
{
	return xml.dump();
}
