#include "user.h"
#include "library.h"
#include "node.h"

User::User()
{
	library = new Library;
	user_node = NULL;
	friends_node = NULL;
	logs_node = NULL;
}

User::User(string u, string p)
{
	library = new Library;
	username = u;
	password = p;
	user_node = NULL;
	friends_node = NULL;
	logs_node = NULL;
}

User::~User()
{
	delete library;
	for(int i = 0; i < activity_logs.size(); i++)
		delete activity_logs[i];

	activity_logs.clear();
	friends.clear();
}

bool User::is_in_library(Book* book)
{
	return library->is_in_library(book);
}

void User::follow(User* user)
{
	friends.push_back(user);
	friends_node->add_node("user",user->username);
}

bool User::does_follow(User* user)
{
	for(int i = 0; i < friends.size(); i++)
		if(friends[i] == user)
			return true;
	return false;
}
	
