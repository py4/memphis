#include "user.h"
#include "library.h"

User::User()
{
	library = new Library;
}

User::User(string u, string p)
{
	library = new Library;
	username = u;
	password = p;
}

User::~User()
{
	delete library;
	for(int i = 0; i < activity_logs.size(); i++)
		delete activity_logs[i];

	activity_logs.clear();
	stared_books.clear();
	friends.clear();
}
