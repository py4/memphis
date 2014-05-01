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

void DB::populate_users()
{
	ifstream users_db(USERS);
	string line;
	User* current_user = NULL;
	while(getline(users_db,line))
	{
		if(line == "<users>" or line == "</users>")
			continue;
		if(line == "<user>")
		{
			current_user = new User;
			while(true)
			{
				getline(users_db,line); //username

				if(line == "</user>")
					break;
				
				current_user->username = get_value_of_tag(line);

				getline(users_db,line); //password
				current_user->password = get_value_of_tag(line);

				getline(users_db,line); //shelves

				while(true)
				{
					getline(users_db,line);

					if(line == "</shelves>")
						break;
					
					string shelf_name = get_shelf_name(line);
					if(shelf_name.length() > 0)
					{
						current_user->library->add_shelf(shelf_name);
						while(true)
						{
							getline(users_db,line); //book
							if(line == "</shelf>")
								break;
							current_user->library->shelves.back()->add_book(get_value_of_tag(line));
						}
					}
					else
						cerr << "shelf_name length bug" << endl;
				}

				getline(users_db,line);
				if(line == "<friends>")
				{
					while(true)
					{
						getline(users_db,line);
						if(line == "</friends>")
							break;

						User* new_friend = find_user(get_value_of_tag(line));
						if(new_friend != NULL)
							current_user->friends.push_back(new_friend);
						else
							cerr << "[db populator] username not found" << endl;
					}
				}

				getline(users_db,line);
				if(line == "<ActivityLogs>")
				{
					while(true)
					{
						getline(users_db,line);
						//if(line == "</ActivityLogs>")
					}
				}
				while(true)
				{
					//getline(
				}
				
			}
			continue;
		}
	}
}

void DB::populate()
{
	populate_books();
}
