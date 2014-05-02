#include <iostream>
#include "db.h"
#include "parser/XML.h"

using namespace std;

int main()
{
	if(DB::db())
		cout << "yes" << endl;
	//cout << get_shelf_name("<shel f name=\"this is a test name\">salam</shelf>");
	map<string,string> result = get_attributes("<salam>");
	//XML xml;
	//xml.load("data.txt");
	//xml.parse();
	//cout << xml["friends"] << endl;
	DB::free_db();
	return 0;
}
