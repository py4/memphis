#include "db.h"
#include "user.h"
#include "book.h"
#include "library.h"
#include "shelf.h"
#include <iostream>
#include <fstream>
#include <map>
#include "API.h"

using namespace std;

DB* DB::instance = 0;

void DB::start_api()
{
	if(api == NULL)
		api = new API;
	api->start();
}
DB::DB()
{
	api = NULL;
	
	if(xml.load(DATA))
	{
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
	else
		cerr << "data not found..." << endl;
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
	delete api;
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
		//Shelf* shelf = c_user->library->add_shelf((*nodes[j])["name"]);
		
		Shelf* shelf = c_user->library->add_shelf_from_xml(nodes[j]);
		shelf->shelf_node = nodes[j];
		
		for(int k = 0; k < nodes[j]->children.size(); k++)
			shelf->add_book_from_xml(nodes[j]->children[k]);
			//shelf->add_book(nodes[j]->children[k]->value);
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
	if(xml["users"] == NULL)
	{
		cerr << "no user in the data..." << endl;
		return;
	}

	string line;
	User* c_user = NULL;

	map <string, vector <string> > friends;

	for(int i = 0; i < xml["users"]->children.size();i++)
	{
		Node* user_node = xml["users"]->children[i];
		c_user = new User;
		c_user->username = user_node->get_child_node("username")->value;
		c_user->password = user_node->get_child_node("password")->value;
		c_user->user_node = user_node;
		c_user->library->shelves_node = user_node->get_child_node("shelves");
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

void DB::populate_books()
{
	map<string,string> info;
	if(xml["books"] == NULL)
	{
		cerr << "bug2" << endl;
		return;
	}
	for(int i = 0; i < xml["books"]->children.size(); i++)
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
	
	book_db.open(NEW_BOOKS);
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
	
	user_node->add_node("friends");
	user_node->add_node("ActivityLogs");
	user_node->add_node("favorites");

	Node* shelf_node = user_node->get_child_node("shelves")->add_node("shelf");
	shelf_node->set_attribute("name","default");
	
	DB::db()->save_to_disk();
}
	
