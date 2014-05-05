#include "API.h"
#include "user.h"
#include "library.h"
#include "book.h"

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
			if(params["command"] == "quit")
				break;
			
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
	if(current_user != NULL)
		throw RespondTo::Failure::already_logged_in();
}
