#include <iostream>
#include "libs/db.h"
#include "parser/XML.h"
#include "interface/CLI/CLI.h"
#include "interface/GUI/GUI.h"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 1 and (string(argv[1]) != "--cli") and (string(argv[1]) != "--gui"))
	{
		cerr << "undefined parameters" << endl;
		return 0;
	}
	DB::create_instance();
	if(argc == 1)
		DB::db()->start_cli();
	else if(string(argv[1]) == "--cli")
		DB::db()->start_cli();
	else if(string(argv[1]) == "--gui")
		return DB::db()->start_gui(argc,argv);

	DB::free_db();
	return 0;	
}
