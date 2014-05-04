#include <iostream>
#include "db.h"
#include "parser/XML.h"
#include "API.h"
using namespace std;

int main()
{
	DB::create_instance();
	API api;
	api.start();
	DB::free_db();
	return 0;
}
