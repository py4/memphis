#include "user.h"
#include "library.h"
#include "../parser/node.h"
#include <iostream>
using namespace std;
User::User()
{
	library = new Library;
	user_node = NULL;
	followings_node = NULL;
	followers_node = NULL;
	logs_node = NULL;
}

User::User(string u, string p)
{
	username = u;
	password = p;
	library = new Library;
	user_node = NULL;
	followings_node = NULL;
	followers_node = NULL;
	logs_node = NULL;
}

User::~User()
{
	delete library;
	for(int i = 0; i < activity_logs.size(); i++)
		delete activity_logs[i];

	activity_logs.clear();
	followings.clear();
	followers.clear();
}

bool User::is_in_library(Book* book)
{
	return library->is_in_library(book);
}

void User::follow(User* user)
{
	followings.push_back(user);
	followings_node->add_node("user",user->username);

	user->followers.push_back(this);
	user->followers_node->add_node("user",this->username);
}

bool User::does_follow(User* user)
{
	for(int i = 0; i < followings.size(); i++)
		if(followings[i] == user)
			return true;
	return false;
}

void User::add_log(string message)
{
	cerr << "followers size:  " << followers.size() << endl;
	for(int i = 0; i < followers.size(); i++)
	{
		cerr << followers[i] << endl;
		followers[i]->activity_logs.push_back(new Log(username,message));
		Node* log_node = followers[i]->logs_node->add_node("log");
		log_node->add_node("username",username);
		log_node->add_node("message",message);
	}
}

void User::show_logs()
{
	for(int i = 0; i < activity_logs.size(); i++)
		cout << activity_logs[i]->username << " " << activity_logs[i]->message << endl;
	activity_logs.clear();
	logs_node->delete_children();
}

const vector<User*>& User::get_followings() const
{
	return followings;
}

const vector<User*>& User::get_followers() const
{
	return followers;
}

const vector<Log*>& User::get_activity_logs() const
{
	return activity_logs;
}

Library* User::get_library()
{
	return library;
}
	
