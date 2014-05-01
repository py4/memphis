#include "book.h"
using namespace std;

Book::Book(map <string,string> & info)
{
	name = info["publisher"];
	author = info["author"];
	publisher = info["publisher"];
	year = info["year"];
}
