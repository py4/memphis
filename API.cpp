#include "API.h"
#include "user.h"
using namespace std;

void API::start()
{
	string command_name;
	while(true)
	{
		cout << "> ";
		getline(cin,command);
		try {
			set_params(params,command);
		} catch (string error) {
			cerr << error;
			continue;
		}

		if(params["command"] == "register")
			sign_up();
	}
}

void API::sign_up()
{
	User* user = DB::db()->find_user(params["username"]);
	if(user != NULL)
		cerr << RespondTo::Failure::in_use();
	else
	{
		DB::db()->add_user(new User(params["username"], params["password"]));
		cerr << RespondTo::Success::ok_signup();
	}
}
