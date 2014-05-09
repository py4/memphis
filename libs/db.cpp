#include "db.h"
#include "user.h"
#include "book.h"
#include "library.h"
#include "shelf.h"
#include <iostream>
#include <fstream>
#include <map>
#include "../interface/CLI/CLI.h"
#include "../interface/GUI/GUI.h"

using namespace std;

DB* DB::instance = 0;

void DB::start_cli()
{
	if(cli == NULL)
		cli = new CLI;
	cli->start();
}

int DB::start_gui(int argc, char* argv[])
{
	if(gui == NULL)
		gui = new GUI;
	return gui->start(argc,argv);
}
DB::DB()
{
	cli = NULL;
	
	if(xml.load(DATA))
		xml.parse();
	
	if(xml["books"] == NULL)
	{
		cerr << "there is no books tag in the xml..." << endl;
		xml["root"]->add_node("books");
		cerr << "added the books tag to the xml..." << endl;
	}
	if(xml["users"] == NULL)
	{
		cerr << "there is no users tag in the xml..." << endl;
		xml["root"]->add_node("users");
		cerr << "added the users tag to the xml..." << endl;
	}
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
	for(unsigned int i = 0; i < users.size(); i++)
		delete users[i];
	for(unsigned int i = 0; i < books.size(); i++)
		delete books[i];
	delete cli;
}

/*void DB::populate_books()
{
	ifstream book_db;
	string line;
	map <string,string> book_info;
	
	book_db.open(DATABASE);
	
	while(getline(book_db,line))
	{
		book_info = parse_book(line);
		books.push_back(new Book(book_info));
	}
	}*/

Book* DB::find_book(string name)
{
	for(unsigned int i = 0; i < books.size(); i++)
	{
		if(books[i]->name == name)
			return books[i];
	}
	return NULL;
}

User* DB::find_user(string username)
{
	for(unsigned int i = 0; i < users.size(); i++)
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

	return books.back();
}

void DB::configure_shelves(User* c_user, vector<Node*>& nodes)
{
	for(unsigned int j = 0; j < nodes.size();j++)
	{
		
		Shelf* shelf = c_user->library->add_shelf_from_xml(nodes[j]);
		shelf->library = c_user->library;
		shelf->shelf_node = nodes[j];
		
		for(unsigned int k = 0; k < nodes[j]->children.size(); k++)
			shelf->add_book_from_xml(nodes[j]->children[k]);
	}
}

void DB::configure_activity_logs(User* c_user, vector<Node*>& nodes)
{
	for(unsigned int j = 0; j < nodes.size(); j++)
	{
		string name = nodes[j]->get_child_node("username")->value;
		string message = nodes[j]->get_child_node("message")->value;
		c_user->activity_logs.push_back(new Log(name, message));
	}
}

void DB::configure_stared_books(User* c_user, vector<Node*>& nodes)
{
	for(unsigned int j = 0; j < nodes.size(); j++)
	{
		Book* book = find_book(nodes[j]->value);
		if(book != NULL)
			c_user->library->stared_books.push_back(book);
		else
			cerr << "[db][populate_users] book not found" << endl;
	}
}

void DB::populate_users()
{
	if(xml["users"] == NULL)
	{
		cerr << "no user in the data..." << endl;
		return;
	}

	string line;
	User* c_user = NULL;

	map <string, vector <string> > followings;
	map <string, vector <string> > followers;
	for(unsigned int i = 0; i < xml["users"]->children.size();i++)
	{
		Node* user_node = xml["users"]->children[i];
		c_user = new User;
		c_user->username = user_node->get_child_node("username")->value;
		c_user->password = user_node->get_child_node("password")->value;

		c_user->user_node = user_node;
		c_user->logs_node = user_node->get_child_node("ActivityLogs");
		c_user->followings_node = user_node->get_child_node("followings");
		c_user->followers_node = user_node->get_child_node("followers");
		c_user->library->shelves_node = user_node->get_child_node("shelves");
		c_user->library->stared_node = user_node->get_child_node("favorites");
		c_user->library->user = c_user;
		
		configure_shelves(c_user, user_node->get_child_node("shelves")->children);
		configure_activity_logs(c_user, user_node->get_child_node("ActivityLogs")->children);
		configure_stared_books(c_user, user_node->get_child_node("favorites")->children);

		vector<Node*>::iterator it = c_user->followings_node->children.begin();
		vector<Node*>::iterator end = c_user->followings_node->children.end();
		for(; it != end; it++)
		{
			User* user_following = find_user((*it)->value);
			c_user->followings.push_back(user_following); // if it is NULL then we have a bug
		}

		it = c_user->followers_node->children.begin();
		end = c_user->followers_node->children.end();
		for(; it != end; it++)
		{
			User* user_follower = find_user((*it)->value);
			c_user->followers.push_back(user_follower);
		}
		users.push_back(c_user);
	}
}

void DB::populate_books()
{
	map<string,string> info;
	if(xml["books"] == NULL)
	{
		cerr << "no db history found" << endl;
		return;
	}
	for(unsigned int i = 0; i < xml["books"]->children.size(); i++)
	{
		Node* book_node = xml["books"]->children[i];
		info["name"] = book_node->get_child_node("name")->value;
		info["author"] = book_node->get_child_node("author")->value;
		info["publisher"] = book_node->get_child_node("publisher")->value;
		info["year"] = book_node->get_child_node("year")->value;
		books.push_back(new Book(info));
	}
	info.clear();
}

void DB::populate()
{
	//load_new_books();
	populate_books();
	populate_users();
}

string DB::dump_db()
{
	return xml.dump();
}

void DB::load_new_books()
{
	ifstream book_db;
	string line;
	map <string,string> book_info;

	cerr << "new books:  " << NEW_BOOKS << endl;
	book_db.open(NEW_BOOKS);
	cerr << "book db:  " << book_db << endl;
	if(!book_db)
	{
		cerr << "new books file not found..." << endl;
		return;
	}
	while(getline(book_db,line))
	{
		book_info = parse_book(line);
		books.push_back(new Book(book_info));
		add_book_to_xml(books.back());
	}
}

void DB::add_book_to_xml(Book* book)
{
	if(xml["books"] == NULL)
	{
		cerr << "bug1" << endl;
		return;
	}
	Node* new_node = xml["books"]->add_node("book");
	new_node->add_node("name",book->name);
	new_node->add_node("publisher",book->publisher);
	new_node->add_node("author",book->author);
	new_node->add_node("year",book->year);
}

void DB::save_to_disk(string file_name)
{
	xml.save_to_disk(file_name);
}

void DB::add_user(User* user)
{
	users.push_back(user);
	Node* user_node = xml["users"]->add_node("user");
	user->user_node = user_node;
	
	user_node->add_node("username",user->username);
	user_node->add_node("password",user->password);

	Node* shelves_node = user_node->add_node("shelves");
	user->library->shelves_node = shelves_node;
	user->library->user = user;
	
	Node* followings_node = user_node->add_node("followings");
	Node* followers_node = user_node->add_node("followers");
	Node* logs_node = user_node->add_node("ActivityLogs");
	Node* stared_node = user_node->add_node("favorites");

	user->followings_node = followings_node;
	user->followers_node = followers_node;
	user->logs_node = logs_node;
	user->library->stared_node = stared_node;

	Node* shelf_node = user_node->get_child_node("shelves")->add_node("shelf");
	shelf_node->set_attribute("name","default");
	user->library->add_shelf("default");
}
	
