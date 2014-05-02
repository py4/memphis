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
	populate();
}

DB* DB::db()
{
	if(!instance)
		instance = new DB;
	return instance;
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
		if(books[i]->name == name)
			return books[i];
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

void DB::configure_shelves(User* current_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size();j++)
	{
		Shelf* shelf = current_user->library->add_shelf((*nodes[j])["name"]);

		for(int k = 0; k < nodes[j]->children.size(); k++)
			shelf->add_book(nodes[j]->children[k]->value);
	}
}

void DB::configure_activity_logs(User* current_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size(); j++)
		current_user->activity_logs.push_back(new Log(nodes[j]->get_child_node("username")->value, nodes[j]->get_child_node("message")->value));
}

void DB::configure_stared_books(User* current_user, vector<Node*>& nodes)
{
	for(int j = 0; j < nodes.size(); j++)
	{
		Book* book = find_book(nodes[j]->value);
		if(book != NULL)
			current_user->stared_books.push_back(book);
		else
			cerr << "[db][populate_users] book not found" << endl;
	}
}



void DB::populate_users()
{
	ifstream users_db(USERS);
	string line;
	User* current_user = NULL;

	map <string, vector <string> > friends;
	
	for(int i = 0; i < xml["users"]->children.size();i++)
	{
		Node* user_node = xml["users"]->children[i];
		current_user = new User;
		current_user->username = user_node->get_child_node("username")->value;
		current_user->password = user_node->get_child_node("password")->value;
		
		configure_shelves(current_user, user_node->get_child_node("shelves")->children);
		configure_activity_logs(current_user, user_node->get_child_node("ActivityLogs")->children);
		configure_stared_books(current_user, user_node->get_child_node("favorites")->children);
		
		for(int j = 0; j < user_node->get_child_node("friends")->children.size(); j++)
		{
			friends[current_user->username].push_back(user_node->get_child_node("friends")->children[j]->value);
			/*User* user_friend = find_user(user_node.get_node("friends")->children[j].value);
			if(user_friend != NULL)
			current_user->friends.push_back(user);*/
		}

		users.push_back(current_user);
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
