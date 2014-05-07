#include "book.h"
#include <iostream>
using namespace std;

Book::Book(map <string,string> & info)
{
	name = info["name"];
	author = info["author"];
	publisher = info["publisher"];
	year = info["year"];
}

void Book::show_info()
{
	cout << "name:  " << name << endl;
	cout << "author:  " << author << endl;
	cout << "publisher:  " << publisher << endl;
	cout << "year:  " << year << endl;
}
