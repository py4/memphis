#include "API.h"
#include "user.h"
#include "library.h"
#include "book.h"

using namespace std;

API::API()
{
	current_user = NULL;
}

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
			cerr << error << endl;
			continue;
		}

		try {
			
			if(params["command"] == "register")
				sign_up();
			if(params["command"] == "login")
				sign_in();
			if(params["command"] == "add_book")
				add_book();
			if(params["command"] == "dump")
					cout << DB::db()->dump_db() << endl;
			if(params["command"] == "update_database") //TODO: permission checking
				DB::db()->load_new_books();
			
			if(params["command"] == "quit")
			{
				DB::db()->save_to_disk();
				break;
			}
			
		} catch (string error) {
			cerr << error << endl;
			continue;
		}
	}
}

void API::sign_up()
{
	ensure_no_user();
	
	User* user = DB::db()->find_user(params["username"]);
	if(user != NULL)
		throw RespondTo::Failure::in_use();
	
	user = new User(params["username"], params["password"]);
	cerr << "user:  " << user << endl;
	DB::db()->add_user(user);
	current_user = user;

	cout << RespondTo::Success::ok_signup() << endl;
}

void API::sign_in()
{
	ensure_no_user();
	
	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
		throw RespondTo::Failure::user_not_found();
	if(user->password != params["password"])
		throw RespondTo::Failure::wrong_credentials();

	current_user = user;

	cout << RespondTo::Success::ok_login() << endl;
}

void API::add_book()
{
	ensure_user();

	cerr << "book_name:  " << params["name"] << endl;
	Book* book = DB::db()->find_book(params["name"]);
	if(book == NULL)
		throw RespondTo::Failure::book_not_found();
	else
	{
		if(current_user->library->add_book(book->name))
			cout << RespondTo::Success::book_added() << endl;
		else
			throw RespondTo::Failure::have_book();
	}
}

void API::ensure_user()
{
	if(current_user == NULL)
		throw RespondTo::Failure::access_denied();
}

void API::ensure_no_user()
{
	cerr << "fucking current_user:  " << current_user << endl;
	if(current_user != NULL)
		throw RespondTo::Failure::already_logged_in();
}
