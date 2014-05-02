#include <iostream>
#include "db.h"
#include "parser/XML.h"

using namespace std;

int main()
{
	//if(DB::db())
	//cout << "yes" << endl;
	map<string,string> result = get_attributes("<salam>");
	DB::create_instance();
	cout << DB::db()->dump_db() << endl;
	DB::free_db();
	return 0;
}
