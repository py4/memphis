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

bool User::is_in_starred(Book* book)
{
	for(int i = 0; i < stared_books.size(); i++)
		if(stared_books[i] == book)
			return true;
	return false;
}

bool User::is_in_library(Book* book)
{
	return library->is_in_library(book);
}
