#ifndef USER_H_
#define USER_H_

#include <vector>

class Library;
class Stared;
class Log;

class User
{
	
private:
	Library* library;
	std::vector <User*> friends;
	std::vector <Book*> stared_books;
	std::vector <Log*>  activity_logs;
};

#endif
