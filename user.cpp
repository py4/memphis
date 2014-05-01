#include "user.h"
#include "library.h"

User::User()
{
	library = new Library;
}

User::~User()
{
	delete library;
}
