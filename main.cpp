#include <iostream>
#include "db.h"
#include "parser/XML.h"
using namespace std;

int main()
{
	DB::create_instance();
	DB::free_db();
	return 0;
}
