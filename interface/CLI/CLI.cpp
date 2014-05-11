#include "CLI.h"
#include "../libs/user.h"
#include "../libs/library.h"
#include "../libs/book.h"
#include "../libs/shelf.h"
#include "../logger/logger.h"
#include <string>
#include "../../libs/db.h"

using namespace std;

CLI::CLI()
{
	DB::db()->current_user = NULL;
}

void CLI::start()
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
			{
				sign_up();
				continue;
			}
			else if(params["command"] == "login")
			{
				sign_in();
				continue;
			}

			ensure_user();			
			if(params["command"] == "quit")
			{
				if(!DB::db()->current_user->is_admin())
				{
					cerr << RespondTo::Failure::access_denied() << endl;
					continue;
				}
				DB::db()->save_to_disk();
				break;
			}
			else if(params["command"] == "logout")
			{
				DB::db()->current_user = NULL;
				cout << RespondTo::Success::ok_logout() << endl;
				continue;
			}
			else if(params["command"] == "add_book")
				add_book();
			else if(params["command"] == "dump")
				cout << DB::db()->dump_db() << endl;
			else if(params["command"] == "show_book")
				show_book();
			else if(params["command"] == "add_shelf")
				add_shelf();
			else if(params["command"] == "add_to_shelf")
				add_to_shelf();
			else if(params["command"] == "like")
				like();
			else if(params["command"] == "show_books")
				show_books();
		 			else if(params["command"] == "show_all_books")
				show_all_books();
			else if(params["command"] == "show_favorites")
				show_favorites();
			else if(params["command"] == "follow")
				follow();
			else if(params["command"] == "show_updates")
				show_updates();
			else if(params["command"] == "update_database")
			{
				if(!DB::db()->current_user->is_admin())
				{
					cerr << RespondTo::Failure::access_denied() << endl;
					continue;
				}
				DB::db()->load_new_books();
				cout << RespondTo::Success::updated() << endl;
			}
			else {
				cout << "undefined command" << endl;
			}
			
		} catch (string error) {
			cerr << error << endl;
			continue;
		}
	}
}

void CLI::sign_up()
{
	ensure_no_user();

	if(params["username"] == "" or params["password"] == "")
		throw RespondTo::Failure::bad_input();

	User* user = DB::db()->find_user(params["username"]);
	if(user != NULL)
		throw RespondTo::Failure::in_use();
	
	user = new User(params["username"], params["password"]);
	DB::db()->add_user(user);
	DB::db()->current_user = user;

	cout << RespondTo::Success::ok_signup() << endl;
}

void CLI::sign_in()
{
	ensure_no_user();

	if(params["username"] == "" or params["password"] == "")
		throw RespondTo::Failure::bad_input();
	
	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
		throw RespondTo::Failure::user_not_found();
	if(user->password != params["password"])
		throw RespondTo::Failure::wrong_credentials();

	DB::db()->current_user = user;

	cout << RespondTo::Success::ok_login() << endl;
}

void CLI::add_book()
{
	if(params["name"] == "")
		throw RespondTo::Failure::bad_input();

	Book* book = DB::db()->find_book(params["name"]);
	if(book == NULL)
		throw RespondTo::Failure::book_not_found();
	else
	{
		if(DB::db()->current_user->library->add_book(book->name))
		{
			DB::db()->current_user->add_log(Logger::added_to_library(book->name));
			cout << RespondTo::Success::book_added() << endl;
		}
		else
			throw RespondTo::Failure::have_book();
	}
}

void CLI::show_book()
{
	if(params["name"] == "")
		throw RespondTo::Failure::bad_input();

	Book* book = DB::db()->find_book(params["name"]);
	if(book == NULL)
		throw RespondTo::Failure::book_not_found();

	book->show_info();
	if(DB::db()->current_user->library->is_in_starred(book))
		cout << "you've starred it" << endl;
	if(DB::db()->current_user->is_in_library(book))
		cout << "it's in your library" << endl;
}

void CLI::add_shelf()
{
	if(params["shelf_name"] == "")
		throw RespondTo::Failure::bad_input();

	const Shelf* found_shelf = DB::db()->current_user->library->get_shelf(params["shelf_name"]);
	if(found_shelf != NULL)
		throw RespondTo::Failure::shelf_already_exists();

	DB::db()->current_user->library->add_shelf(params["shelf_name"]);
	cout << RespondTo::Success::shelf_added() << endl;
}

//TODO: checking friendships
//TODO: checking public private
void CLI::add_to_shelf()
{
	if(params["shelf_name"] == "" or params["book_name"] == "")
		throw RespondTo::Failure::bad_input();

	Shelf* found_shelf = DB::db()->current_user->library->get_shelf(params["shelf_name"]);
	string book_name = params["book_name"];
	
	if(found_shelf == NULL)
		throw RespondTo::Failure::shelf_not_found();

	if(!DB::db()->current_user->library->is_in_library(book_name))
		throw RespondTo::Failure::book_not_in_library();
	else if(found_shelf->has_book(book_name))
		throw RespondTo::Failure::book_is_in_shelf();
	else
	{
		found_shelf->add_book(book_name);
		DB::db()->current_user->add_log(Logger::added_to_shelf(book_name,found_shelf->name));
	}

	cout << RespondTo::Success::book_added_to_shelf() << endl;
}

void CLI::like()
{
	if(params["name"] == "")
		throw RespondTo::Failure::bad_input();

	Book* found_book = DB::db()->current_user->library->find_book(params["name"]);
	if(found_book == NULL)
		throw RespondTo::Failure::book_not_in_library();
	if(DB::db()->current_user->library->is_in_starred(found_book))
		throw RespondTo::Failure::is_in_stared();
	
	DB::db()->current_user->library->star_book(found_book);
	DB::db()->current_user->add_log(Logger::liked(found_book->name));
	cout << RespondTo::Success::liked() << endl;
}

void CLI::show_books()
{
	if(params["shelf_name"] == "")
		throw RespondTo::Failure::bad_input();

	Shelf* found_shelf = DB::db()->current_user->library->get_shelf(params["shelf_name"]);
	if(found_shelf == NULL)
		throw RespondTo::Failure::shelf_not_found();
	found_shelf->show_books();
}

void CLI::show_all_books()
{
	DB::db()->current_user->library->show_all_books();
}

void CLI::show_favorites()
{
	DB::db()->current_user->library->show_favorites();
}

void CLI::follow()
{
	if(params["username"] == "")
		throw RespondTo::Failure::bad_input();

	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
		throw RespondTo::Failure::user_not_found();
	if(DB::db()->current_user->does_follow(user))
		throw RespondTo::Failure::already_following();
	DB::db()->current_user->follow(user);
	cout << RespondTo::Success::followed() << endl;
}

void CLI::show_updates()
{
	DB::db()->current_user->show_logs();
}

void CLI::ensure_user()
{
	if(DB::db()->current_user == NULL)
		throw RespondTo::Failure::access_denied();
}

void CLI::ensure_no_user()
{
	if(DB::db()->current_user != NULL)
		throw RespondTo::Failure::already_logged_in();
}
