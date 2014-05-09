#include <iostream>
#include "libs/db.h"
#include "parser/XML.h"
#include "interface/CLI/CLI.h"
#include "interface/GUI/GUI.h"
using namespace std;

int main(int argc, char* argv[])
{
	DB::create_instance();
	//DB::db()->start_cli();
	//QApplication app(argc,argv);
	
	return DB::db()->start_gui(argc,argv);
	//return app.exec();



//DB::free_db();
	//return 0;
}
