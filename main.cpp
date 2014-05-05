#include <iostream>
#include "db.h"
#include "parser/XML.h"
#include "API.h"
using namespace std;

int main()
{
	DB::create_instance();
	DB::db()->start_api();
	DB::free_db();
	return 0;
}
